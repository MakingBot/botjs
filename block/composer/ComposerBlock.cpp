//!
//! \file ComposerBlock.cpp
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

#include <ComposerBlock.hpp>
#include <ComposerWidget.hpp>

/* ============================================================================
 *
 * */
EXPORT_BLOCK(ComposerBlock)

/* ============================================================================
 *
 * */
ComposerBlock::ComposerBlock(const QString& name)
    : GuiBlock(name)
{
    _widget = qSharedPointerObjectCast<QWidget, ComposerWidget>( QSharedPointer<ComposerWidget>( new ComposerWidget(this) ) );
}

/* ============================================================================
 *
 * */
void ComposerBlock::reset()
{
    qSharedPointerObjectCast<ComposerWidget, QWidget>( _widget )->reset();
}


/* ============================================================================
 *
 * */
void ComposerBlock::jsCfgEnablePhase(CoreCfg cfg, QTextStream& stream, QString& var_name)
{
    if( cfg == CoreCfg::CoreCfgDev )
    {
        GuiBlock::jsCfgEnablePhase(cfg, stream, var_name);
        
        // Apply a reset after the creation phase
        stream << var_name << ".reset();" << endl;
    }
}
