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
CoreBlock::CoreBlock(const QString& name)
    : BotBlock(name)
    , _coreCfgMapper( (int*)&_cfg, { EnumPair(CoreCfgDev,"dev"), EnumPair(CoreCfgBot,"bot") } )
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
    
    //
    return block;
}


/* ============================================================================
 *
 * */
void CoreBlock::updateBotCfg()
{
    updateCfg(CoreCfgBot);
}

/* ============================================================================
 *
 * */
void CoreBlock::updateDevCfg()
{
    updateCfg(CoreCfgDev);
}

/* ============================================================================
 *
 * */
void CoreBlock::updateCfg(CoreCfg cfg)
{
    // Get the filepath
    QString filepath;
    switch(cfg)
    {
        case CoreCfgDev:
            filepath = BotBlock::JsEngine.getConfigDirectory() + QDir::separator() + QString("dev.js");
            break;

        case CoreCfgBot:
            filepath = BotBlock::JsEngine.getConfigDirectory() + QDir::separator() + QString("bot.js");
            break;

        default:
            // TODO log an error
            break;
    }

    // Create and open the file
    QFile file(filepath);
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        BLOCK_LOG("Unable to open the operatonal configuration file (" << filepath << ")");   
        return;
    }

    // Initialize a text stream
    QTextStream stream(&file);
    stream << "// =========================" << endl;

    // Append a little header
    switch(cfg)
    {
        case CoreCfgDev:
            stream << "// === Dev Configuration ===" << endl << endl;
            break;

        case CoreCfgBot:
            stream << "// === Bot Configuration ===" << endl << endl;
            break;

        default:
            // TODO log an error
            break;
    }

    // TODO append the date and the hour

    // Convert the architecture
    toJsCfg(cfg, stream);

    // End
    stream << "// === End of Script ===" << endl;

    // Close the file
    file.close();
}

/* ============================================================================
 *
 * */
void CoreBlock::toJsCfg(CoreCfg cfg, QTextStream& stream)
{
    // Declare strings
    QString str_creation  ;
    QString str_connection;
    QString str_enable    ;

    // Declare streams
    QTextStream stream_creation  (&str_creation  );
    QTextStream stream_connection(&str_connection);
    QTextStream stream_enable    (&str_enable    );

    stream_creation   << "// =====  Creation Phase  =====" << endl;
    stream_connection << "// ===== Connection Phase =====" << endl;
    stream_enable     << "// =====   Enable Phase   =====" << endl;

    QString var_name;

    // 
    for(quint32 id=0 ; id<BotBlock::BlockCounter ; id++)
    {
        // Get the block
        QSharedPointer<BotBlock> block = BotBlock::IdNumberToBlock(id);
 
        if( block )
        {
            // Creation phase
            block->jsCfgPhaseCreation   (cfg, stream_creation, var_name);
            stream_creation << endl;
        
            // Connection phase
            block->jsCfgConnectionPhase (cfg, stream_connection, var_name);
            stream_connection << endl;

            // Enable pahse
            block->jsCfgEnablePhase     (cfg, stream_enable, var_name);
            stream_enable << endl;
        }
    }

    // Concatenate streams
    stream << str_creation << str_connection << str_enable;
}
