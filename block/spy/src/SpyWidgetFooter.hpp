#ifndef SPYWIDGETFOOTER_HPP
#define SPYWIDGETFOOTER_HPP
//!
//! \file SpyWidgetFooter.hpp
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
#include <BotBlock.hpp>

#include <QComboBox>
#include <QPushButton>

class SpyBlock;

//!
//! Footer of the spy widget
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidgetFooter : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit SpyWidgetFooter(QWeakPointer<SpyBlock> spy_block, QWidget *parent = 0);

    //!
    //! Pointer on the parent spy block
    //!
    QSharedPointer<SpyBlock> getSharedSpyBlock()
    {
        if(_spyblock) { return _spyblock.toStrongRef(); }
        else          { throw std::runtime_error("This widget need a parent spy block"); }
    }

public slots:

    //! When the spied change
    void onSpiedBlockChange();

    //! Update values of the widget with data from the spied block
    void updateValues();

    //! Update structure
    void updateStructure();
    
    //! Kill the spied block
    void killSpiedBlock();
    
    //! Create a son to the spied block
    void createSonOfSpiedBlock();

    //! When user change the spied block
    void onCBSpiedChange( const QString & text );

protected:
    //! Button to kill the spied block
    QPushButton _buttonKill;

    //! Button to create a son to the spied block
    QPushButton _buttonCreate;

    // Combobox to select an other spied block
    QComboBox   _cbSpiedBlock;

    //! Current selection of the combo box
    int _currentValidSelection;
    
    //! Parent block
    QWeakPointer<SpyBlock> _spyblock;
};

#endif // SPYWIDGETFOOTER_HPP
