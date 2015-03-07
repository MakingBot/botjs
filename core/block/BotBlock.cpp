//!
//! \file BotBlock.cpp
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

// Static declaration
BotEngine BotBlock::JsEngine;

// Static declaration
quint32 BotBlock::BlockCounter;

// Static declaration
QMap<quint32, QSharedPointer<BotBlock> > BotBlock::BlockMap;

/* ============================================================================
 *
 * */
void BotBlock::GenerateIdNumber(QSharedPointer<BotBlock> block)
{
	// Set Id number
	block->setBlockIdNumber(BlockCounter);

	// Track pointer
	BlockMap[BlockCounter] = block;

	// Increment counter
	BlockCounter++;
}

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> BotBlock::IdNumberToBlock(quint32 id)
{
	return BlockMap[id];
}

/* ============================================================================
 *
 * */
QString BotBlock::JsString(const QString& string)
{
    return QString("'") + string + QString("'");
}
