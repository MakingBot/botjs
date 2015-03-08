//!
//! \file BotEngine.cpp
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

#include <QFile>
#include <QStack>
#include <iostream>

#include <Type.hpp>
#include <BotEngine.hpp>
#include <CoreBlock.hpp>
#include <QCoreApplication>

//! Define the type of the creation function
typedef QSharedPointer<BotBlock> (*CreateBlock)(const QString&);

/* ============================================================================
 *
 * */
BotEngine::BotEngine(QObject *parent)
    : QObject(parent), _jsEngine(new QJSEngine())
{ }

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> BotEngine::createBlock(const QString& btypename, const QString& varname)
{
    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << "++ Start creation of the " << btypename.toStdString() << " block : #" << varname.toStdString() << "#" << std::endl;
    #endif

    // If the block type has not been loaded yet
    if( _blockLib.find(btypename) == _blockLib.end() )
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Block lib not loaded yet, start library loading !" << std::endl;
        #endif

        // Build lib path
        QString lib_path = _blockLibDirectory + QDir::separator() + btypename;

        // Load module
        QSharedPointer<QLibrary> lib_block(new QLibrary(lib_path));
        if( ! lib_block->load() )
        {
            std::cerr << "-- Cannot load block : " << lib_block->errorString().toStdString() << std::endl;
            return QSharedPointer<BotBlock>(0);
        }
        
        // Save lib pointer
        _blockLib[btypename] = lib_block;
    }

    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << "++ Block lib loaded start block creation !" << std::endl;
    #endif

    // Resolve lib symbol
    return resolveBlockLibCreation(_blockLib[btypename], btypename, varname);
}

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> BotEngine::resolveBlockLibCreation(QSharedPointer<QLibrary> lib, const QString& btypename, const QString& varname)
{
    // Resolve CreateBlock function
    QSharedPointer<BotBlock> block;

    // Resolve the block create function
    CreateBlock create_function = (CreateBlock) lib->resolve("CreateBlock");
    if (create_function)
    {
        // Request block creation
        block = create_function(varname);
    }
    else
    {
        // Build error string
        QString error = QString("-- No 'CreateBlock' function found in the block '") + btypename + QString("': ") + lib->errorString();
        std::cerr << error.toStdString() << std::endl;
    }

    // Check pointer
    if(!block)
    {
        std::cerr << "-- ??? Block created but pointer null ???" << std::endl;
        return QSharedPointer<BotBlock>(0);
    }

    // Initialize and return the block
    block->blockInit();
    return block;
}

/* ============================================================================
 *
 * */
void BotEngine::evalScriptFile(const QString &script_path)
{
    // Check script file
    QFile script_file(script_path);
    if(!script_file.exists())
    {
        std::cerr << "-- The Js script (" << script_path.toStdString() << + ") does not exist !" << std::endl;
        return;
    }

    // Open the file
    if(!script_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "-- The Js script (" << script_path.toStdString() << + ") cannot be opened !" << std::endl;
        return;
    }

    // Read program file
    QString program(script_file.readAll());

    // Close program file
    script_file.close();

    // Evaluate the program
    QJSValue result = eval(program);

    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << "++ Script end with : " << result.toString().toStdString() << std::endl;
    #endif
}

/* ============================================================================
 *
 * */
void BotEngine::updateBotCfg()
{
    qSharedPointerObjectCast<CoreBlock, BotBlock>(_coreBlock)->updateBotCfg();
}

/* ============================================================================
 *
 * */
void BotEngine::updateDevCfg()
{
    qSharedPointerObjectCast<CoreBlock, BotBlock>(_coreBlock)->updateDevCfg();
}

/* ============================================================================
 *
 * */
void BotEngine::createCoreBlock()
{
    // Create core block
    _coreBlock = BotBlock::CreateBlock<CoreBlock>("core");
   
    // Initialize block
    _coreBlock->blockInit();
    
    // Set this as the block parent
    _coreBlock->setBlockFather(0);

    // Set the log id
    _coreBlock->setLogId( "core" );

    // Create a qt js object
    QJSValue js_val = _jsEngine->newQObject(_coreBlock.data());
    
    // Link it to the js engine
    go().setProperty(_coreBlock->blockName(), js_val);

    // Add Type helper
    go().setProperty("Type", _jsEngine->newQObject(new Type()));
}

/* ============================================================================
 *
 * */
void BotEngine::availableBlockNames(QStringList& names)
{
    // Clear the list
    names.clear();

    // Find the directory where block lib are stored
    QDir blockDir(_blockLibDirectory);

    // Get the list of files in this directory
    QStringList filenames = blockDir.entryList (  QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );

    // Remove the lib and the .so
    QStringList blocknames;
    foreach(const QString& filename, filenames)
    {
        QByteArray array(filename.toStdString().c_str());
        // Remove the lib
        array.remove(0, 3);
        // Remove the .so
        array.remove(array.size()-3, 3);

        QString blockname(array);
        if(blockname.compare("composer") == 0)
        {
            continue;
        }

        blocknames << blockname;
    }
    
    // Append those names
    names << blocknames;
}

/* ============================================================================
 * TODO create cash system
 * */
void BotEngine::allIdChains(QStringList& chains)
{
    // Clear chains
    chains.clear();

    // Create stack and store the core block to start
    QStack<QSharedPointer<BotBlock> > blocks;
    blocks.push(_coreBlock);

    // Block after block
    while(!blocks.isEmpty())
    {
        // Get the current block
        QSharedPointer<BotBlock> block = blocks.pop();

        // Get its id chain
        chains << block->blockIdChain();

        // Add every son
        QMapIterator<QString, QSharedPointer<BotBlock> > son(block->blockSons());
        while(son.hasNext())
        {
            son.next();
            blocks.push(son.value());
        }
    }
}
