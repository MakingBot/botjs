//!
//! \file ViewerRealList.cpp
//!
// Copyright 2015 MakingBot
// This file is part of BotJs.
//
// BotJs is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BotJs is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BotJs.  If not, see <http://www.gnu.org/licenses/>.

#include <ViewerRealList.hpp>
#include <QHBoxLayout>

/* ============================================================================
 *
 * */
ViewerRealList::ViewerRealList(QWidget* parent)
    : QWidget(parent)
{
    new QHBoxLayout(this);
}

/* ============================================================================
 *
 * */
void ViewerRealList::updateStructure()
{
    // Clear old structure
    _boxs.clear();

    // Create the new structure
    for(int i=0 ; i<_model.size() ; i++)
    {
        // Create a box for the index
        QSharedPointer<QDoubleSpinBox> box( new QDoubleSpinBox() );
        
        // Set large range
        box->setRange(-0xFFFFFFF , 0xFFFFFFF);

        // Connections
        connect(box.data(), SIGNAL(valueChanged(double)), this, SLOT(onValueChange(double)));

        // Add it in the line
        ((QHBoxLayout*)layout())->addWidget( box.data() );

        // Add the box in the management list
        _boxs << box;
    }
}

/* ============================================================================
 *
 * */
void ViewerRealList::updateValues()
{
    for(int i=0 ; i<_model.size() ; i++)
    {
        _boxs.at(i)->setValue ( _model.at(i) );
    }
}

/* ============================================================================
 *
 * */
void ViewerRealList::onValueChange(double d)
{
    int index = 0;

    // Get sender
    QObject* sender = QObject::sender();
    if(!sender) { return; }

    // Go through boxes
    foreach(QSharedPointer<QDoubleSpinBox> box, _boxs)
    {
        // Check if this box is the sender
        if(box.data() != sender)
        {
            index++;
            continue;
        }

        // Set the new value
        _model[index] = box->value();

        break;
    }

    // Alert BotJs
    emit listModified(_model);
}
