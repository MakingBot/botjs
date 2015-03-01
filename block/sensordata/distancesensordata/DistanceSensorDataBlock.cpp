//!
//! \file DistanceSensorDataBlock.cpp
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

#include <DistanceSensorDataBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(DistanceSensorDataBlock)


/* ============================================================================
 *
 * */
bool DistanceSensorDataBlock::connectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{

	// End
	return BotBlock::connectionHook(weakblock, master);
}

/* ============================================================================
 *
 * */
bool DistanceSensorDataBlock::disconnectionHook(QWeakPointer<BotBlock> weakblock, bool master)
{

	// End
	return BotBlock::disconnectionHook(weakblock, master);
}
