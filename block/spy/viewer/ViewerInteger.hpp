
#ifndef VIEWERINTEGER_HPP
#define VIEWERINTEGER_HPP
//!
//! \file ViewerInteger.hpp
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

#include <QSpinBox>
#include <QPushButton>
#include <ViewerIProperty.hpp>

//!
//! To display and modify integers
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ViewerInteger : public ViewerIProperty
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    ViewerInteger(quint8 propid, bool readonly, QWidget* parent=0);

    //!
    //! Integer getter
    //!
    long getInteger()
    {
        return _box.value();
    }

    //!
    //! Integer setter
    //!
    void setInterger(long integer)
    {
        _valid = false;
        _setButton.setText("OK");
        _box.setValue(integer);
    }

public slots:

    //! To apply the choice of the user
    void apply();

protected:

    //! True if the value has changed
    bool _valid;

    //! Box to display the value
    QSpinBox _box;

    //! Button to set the 
    QPushButton _setButton;

};

#endif // VIEWERINTEGER_HPP
