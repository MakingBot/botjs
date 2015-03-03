//!
//! \file ViewerInteger.cpp
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

#include <ViewerInteger.hpp>
#include <QHBoxLayout>

/* ============================================================================
 *
 * */
ViewerInteger::ViewerInteger(quint8 propid, bool readonly, QWidget* parent)
    : ViewerIProperty(propid, readonly, parent)
{
    // Create the layout
    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget( &_box );
    
    // Manage the read only parameter
    _box.setReadOnly(readonly);
    connect(&_box, SIGNAL(valueChanged(int)), this, SLOT(onValueChange(int)));
    if(!readonly)
    {
        lay->addWidget( &_setButton );
        connect(&_setButton, SIGNAL(click()), this, SLOT(apply()));
    }

    // Box property
    _box.setSingleStep( 1 );
    _box.setRange( -0xFFFFFF , 0xFFFFFF );
}

/* ============================================================================
 *
 * */
void ViewerInteger::apply()
{
    if(_setButton.hasChanged())
    {
        emit newValueRequestedFor(_propid);
    }
}

/* ============================================================================
 *
 * */
void ViewerInteger::onValueChange(int value)
{
    _setButton.change();
}
