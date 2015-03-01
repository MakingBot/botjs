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
//! The Spy Block provides a way to get and modify block properties and data
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyBlock : public GuiBlock
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit SpyBlock(const QString& name = QString("spy"));

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("spy"); }

    //! FROM BotBlock
    virtual bool connectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    //! FROM BotBlock
    virtual bool disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master);

    // ========================================================================
    // => Property spied block

    //!
    //! Weak pointer on the spied block
    //!
    QWeakPointer<BotBlock> weakSpiedBlock()
	{
    	return _spiedBlock;
	}

signals:

	//!
    //! Emitted when the spied block has changed
    //!
	void spiedBlockChanged();

public slots:

protected:

    //! Spied
    //! Pointer on the spied block
    QWeakPointer<BotBlock> _spiedBlock;

};

#endif // SPYBLOCK_HPP
