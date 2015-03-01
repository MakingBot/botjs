//!
//! \file CoreBlock.cpp
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

#include <QApplication>
#include <CoreBlock.hpp>

/* ============================================================================
 *
 * */
CoreBlock::CoreBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent)
{ }

/* ============================================================================
 *
 * */
void CoreBlock::blockInit()
{
    BotBlock::blockInit();
    if( ! QMetaType::isRegistered(QMetaType::type("CoreBlock*")) ) { qRegisterMetaType<CoreBlock*>("CoreBlock*"); }
}

/* ============================================================================
 *
 * */
BotBlock* CoreBlock::create(const QString& btypename, const QString& varname)
{
    // Block creation
    BotBlock* block = BotBlock::create(btypename, varname);

    // Make the block accessible from js
    BotBlock::JsEngine.go().setProperty(varname.toStdString().c_str(), BotBlock::JsEngine.engine()->newQObject(block));
    
    return block;
}

