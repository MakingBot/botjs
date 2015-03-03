
#ifndef SETBUTTON_HPP
#define SETBUTTON_HPP
//!
//! \file SetButton.hpp
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

#include <QPushButton>

//!
//! Button for interative properties viewer
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SetButton : public QPushButton
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    SetButton(QWidget* parent=0)
        : QPushButton(parent), _changed(false)
    {
        setText("ok");
    }

    //!
    //!
    //!
    bool hasChanged()
    {
        return _changed;
    }

    //!
    //!
    //!
    void change()
    {
        if( !_changed )
        {
            setText("READY TO UPDATE");
            _changed = true;
        }
    }

    //!
    //!
    //!
    void update()
    {
        if( _changed )
        {
            setText("ok");
            _changed = false;
        }
    }

protected:

    //! True when the data has changed
    bool _changed;

};

#endif // SETBUTTON_HPP



