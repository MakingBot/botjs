#ifndef SPYBLOCK_HPP
#define SPYBLOCK_HPP
//!
//! \file SpyBlock.hpp
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

#include <GuiBlock.hpp>
#include <SpyWidget.hpp>

//!
//! The Spy Block povide a way to get and modify block properties and data 
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyBlock : public GuiBlock
{
    Q_OBJECT

    Q_PROPERTY(QString spiedBlockName READ getSpiedBlockName                        )

public:

    //!
    //! Default constructor
    //!
    explicit SpyBlock(const QString& name = QString("spy"));

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("spy"); }




    //!
    //! Create the widget if it is not
    //!
    void createWidgetIfRequired()
    {
        if(!_widget) {
            _widget = QSharedPointer<SpyWidget>( new SpyWidget( qSharedPointerObjectCast<SpyBlock, BotBlock>(this->toBlockSharedPointer()) ) );
        }
    }



    //!
    //! Weak pointer on the spied block
    //!
    QWeakPointer<BotBlock> getWeakSpiedBlock() { return _spiedBlock; }

    //!
    //! Shared pointer on the spied block
    //!
    QSharedPointer<BotBlock> getSharedSpiedBlock()
    {
        if(_spiedBlock) { return _spiedBlock.toStrongRef();   }
        else            { return QSharedPointer<BotBlock>(0); }
    }

    //!
    //! Spied block name getter
    //!
    const QString getSpiedBlockName()
    {
        QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
        if(spied) { return spied->blockName(); } return QString();
    }

signals:

    //! Emitted when the spied block has changed
    void spiedBlockChanged();

public slots:

protected:

    //! Widget
    //! Widget for the view
    QSharedPointer<SpyWidget> _widget;

    //! Spied
    //! Pointer on the spied block
    QWeakPointer<BotBlock> _spiedBlock;

};

#endif // SPYBLOCK_HPP
