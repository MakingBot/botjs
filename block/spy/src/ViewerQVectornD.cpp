//!
//! \file ViewerQVectornD.cpp
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

#include <ViewerQVectornD.hpp>

#include <QHBoxLayout>

/* ============================================================================
 *
 * */
ViewerQVectornD::ViewerQVectornD(int n, QWidget* parent)
    : QWidget(parent), _n(n)
{
    // Check N
    if(_n < 2  || _n > 4)
    {
        throw std::runtime_error("N must be between 2 et 4");
    }

    new QHBoxLayout(this);

    // Create each box and its label
    for(int i=0 ; i<_n ; i++)
    {
        QString tag;
        switch(i)
        {
            case 0: tag = "X"; break;
            case 1: tag = "Y"; break;
            case 2: tag = "Z"; break;
            case 3: tag = "W"; break;
        }
        // Add the label
        QSharedPointer<QLabel> label( new QLabel(tag) );
        ((QHBoxLayout*)layout())->addWidget( label.data() );
        _labels << label;

        // Add the box
        QSharedPointer<QDoubleSpinBox> box( new QDoubleSpinBox() );
        box->setRange( -0xFFFFFFF, 0xFFFFFFF );
        connect( box.data(), SIGNAL(valueChanged(double)), this, SLOT(onValueChange(double)) );
        ((QHBoxLayout*)layout())->addWidget( box.data() );
        _boxs << box;
    }
}

/* ============================================================================
 *
 * */
void ViewerQVectornD::updateValues()
{
    switch(_n)
    {
        case 2:
            _boxs.at(0)->setValue ( _vec2.x() );
            _boxs.at(1)->setValue ( _vec2.y() );
            break;

        case 3:
            _boxs.at(0)->setValue ( _vec3.x() );
            _boxs.at(1)->setValue ( _vec3.y() );
            _boxs.at(2)->setValue ( _vec3.z() );
            break;

        case 4:
            _boxs.at(0)->setValue ( _vec4.x() );
            _boxs.at(1)->setValue ( _vec4.y() );
            _boxs.at(2)->setValue ( _vec4.z() );
            _boxs.at(3)->setValue ( _vec4.w() );
            break;
    }
}

/* ============================================================================
 *
 * */
void ViewerQVectornD::onValueChange(double d)
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
        break;
    }

    // Set the new value
    switch(_n)
    {
        case 2:
            switch(index)
            {
                case 0: _vec2.setX( d ); break;
                case 1: _vec2.setY( d ); break;
            }
            emit modelEdited(_vec2);
            break;

        case 3:
            switch(index)
            {
                case 0: _vec3.setX( d ); break;
                case 1: _vec3.setY( d ); break;
                case 2: _vec3.setZ( d ); break;
            }
            emit modelEdited(_vec3);
            break;

        case 4:
            switch(index)
            {
                case 0: _vec4.setX( d ); break;
                case 1: _vec4.setY( d ); break;
                case 2: _vec4.setZ( d ); break;
                case 3: _vec4.setW( d ); break;
            }
            emit modelEdited(_vec4);
            break;
    }
}

