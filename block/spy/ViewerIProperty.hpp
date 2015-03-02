#ifndef VIEWERIPROPERTY_HPP
#define VIEWERIPROPERTY_HPP
//!
//! \file ViewerIProperty.hpp
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

#include <QWidget>

//!
//! Global interface for interactive property viewers
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ViewerIProperty : public QWidget
{

    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    ViewerIProperty(quint8 propid, bool readonly, QWidget* parent=0)
        : QWidget(parent), _propid(propid), _readOnly(readonly)
    { }

signals:

    //! Signal to the spy, which property has to be updated
    void newValueRequestedFor(quint8 propid);

protected:

    //! The ID of the property
    quint8 _propid;

    //! True if the widget cannot be change by the user
    bool _readOnly;

};


#endif // VIEWERIPROPERTY_HPP