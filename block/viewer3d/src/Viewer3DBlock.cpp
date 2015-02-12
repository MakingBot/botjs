//!
//! \file Viewer3DBlock.cpp
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

#include <Viewer3DBlock.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(Viewer3DBlock)

/* ============================================================================
 *
 * */
Viewer3DBlock::Viewer3DBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent), _visible(false), _bgColor(240,240,240)
{
    appendBlockIProperty("visible"            , IProperty(IProperty::IPTypeBool, true ));

    appendBlockIProperty("vboUsedSize"        , IProperty(IProperty::IPTypeInt , false));
    appendBlockIProperty("nbOfRenderedObject" , IProperty(IProperty::IPTypeInt , false));
}


