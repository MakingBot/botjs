#ifndef SPYWIDGET_HPP
#define SPYWIDGET_HPP

//!
//! \file SpyWidget.hpp
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

#include <QLabel>
#include <QWidget>
#include <SpyWidgetBody.hpp>
#include <SpyWidgetHeader.hpp>
#include <SpyWidgetFooter.hpp>

class SpyBlock;

//!
//! Widget that display information from the block
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidget : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit SpyWidget(QWeakPointer<SpyBlock> spy_block, QWidget *parent = 0);

    //!
    //! Pointer on the parent spy block
    //!
    QSharedPointer<SpyBlock> getSharedSpyBlock()
    {
        if(_spyblock) { return _spyblock.toStrongRef();     }
        else          { throw std::runtime_error("This widget need a parent spy block"); }
        //return QSharedPointer<SpyBlock>();
    }
    
    //!
    //! Pointer on the spied block
    //!
    QSharedPointer<BotBlock> getSharedSpiedBlock();
    
public slots:
    //! When the spied change
    void onSpiedBlockChange();

    //! Update property structure
    void updateStructure();

    //! Update displayed values
    void updateValues();

    //! For line edit property widget
    void onLineTextEdited(const QString& text);

    //! For combobow that manage boolean switch
    void onComboBoxBool( int index );

protected:
    //! Parent block
    QWeakPointer<SpyBlock> _spyblock;

    //! Information header
    SpyWidgetHeader _header;

    //! Information body
    SpyWidgetBody     _body;

    //! Information footer
    SpyWidgetFooter _footer;

    //! FROM QWidget
    virtual void closeEvent(QCloseEvent* event);
};

#endif // SPYWIDGET_HPP
