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

/* ============================================================================
 *
 * */
void CoreBlock::toJsCfg(QTextStream& stream)
{

}

/* ============================================================================
 *
 * */
void CoreBlock::updateCfgOpe()
{
    // Operatonal configuration file path
    QString filepath = BotBlock::JsEngine.getConfigDirectory() + QDir::separator() + QString("ope.js");

    // Create and open the file
    QFile file(filepath);
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        BLOCK_LOG("Unable to open the operatonal configuration file (" << filepath << ")");   
        return;
    }

    // Initialize a text stream
    QTextStream stream(&file);
    
    // Append a little header
    stream << "// ================================" << endl;
    stream << "// === Operatonal Configuration ===" << endl;

    // TODO append the date and the hour

    // Convert the architecture
    toJsCfg(stream);

    // Close the file
    file.close();
}




