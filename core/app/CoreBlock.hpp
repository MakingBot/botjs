#ifndef COREBLOCK_HPP
#define COREBLOCK_HPP
//!
//! \file CoreBlock.hpp
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

#include <BotBlock.hpp>

//!
//! This block is the top parent of all blocks
//!
class CoreBlock : public BotBlock
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit CoreBlock(const QString& name = QString("core"), QObject* parent = 0);
    
    //! FROM BotBlock
    virtual void blockInit();

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockCore; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("core"); }

public slots:
    //! FROM BotBlock
    virtual BotBlock* create(const QString& btypename, const QString& varname);
};

#endif // COREBLOCK_HPP
