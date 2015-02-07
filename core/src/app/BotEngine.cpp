#include <QDir>
#include <QFile>
#include <QStack>
#include <BotBlock.hpp>
#include <BotEngine.hpp>
#include <QCoreApplication>
#include <CoreBlock.hpp>

#include <iostream>

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
        QString error = QString("- No 'CreateBlock' function found in the block '") + btypename + QString("': ") + lib->errorString();

        // Error
        throw std::runtime_error(error.toStdString());
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
void BotEngine::createCoreBlock()
{
    // Create core block
    _coreBlock = BotBlock::CreateBlock<CoreBlock>("core");
   
    // Init block
    _coreBlock->blockInit();
    
    // Create a qt js object
    QJSValue js_val = _jsEngine->newQObject(_coreBlock.data());
    
    // Link it to the js engine
    go().setProperty(_coreBlock->getBlockName(), js_val);
}

/* ============================================================================
 *
 * */
QStringList BotEngine::availableBlockNames()
{
    QStringList names;

    return names;
}

/* ============================================================================
 * TODO Create a cash system
 * */
QStringList BotEngine::getAllFatherChains()
{
    // Result chain
    QStringList chains;

    // Create stack and store the core block to start
    QStack<QSharedPointer<BotBlock> > blocks;
    blocks.push(_coreBlock); 

    // Block after block    
    while(!blocks.isEmpty())
    {
        // Get the current block
        QSharedPointer<BotBlock> block = blocks.pop();

        // Get its father chain
        chains << block->getBlockFathersChain();

        //! Add every son
        foreach(QSharedPointer<BotBlock> son, block->getBlockSons())
        {
            blocks.push(son);
        }
    }
    // Return
    return chains;
}