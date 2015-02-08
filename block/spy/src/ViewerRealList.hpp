#ifndef VIEWERREALLIST_HPP
#define VIEWERREALLIST_HPP
//!
//! \file ViewerRealList.hpp
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

#include <QList>
#include <QtGlobal>
#include <QDoubleSpinBox>

//!
//! To display and modify list of real
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ViewerRealList : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit ViewerRealList(QWidget* parent=0);
    
    //! The data model getter
    const QList<qreal>& list() const { return _model; }
    
    //! The data model setter
    void setList(const QList<qreal>& list)
    {
        _model = list;

        if( _boxs.size() != list.size() )
        {
            updateStructure();    
        }
        
        updateValues();
    }

signals:

    //! When a element of the list is modified
    void listModified(QList<qreal>& list);

public slots:

    //! To update the widget values
    void updateStructure();

    //! To update the widget values
    void updateValues();

    //! When the value has changed
    void onValueChange(double);

protected:
    //! The data model
    QList<qreal> _model;

    // To display
    QList<QSharedPointer<QDoubleSpinBox> > _boxs;
};

#endif // VIEWERREALLIST_HPP
