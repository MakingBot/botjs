#include <QDir>
#include <QFile>
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
    // If the block type has not been loaded yet
    if( _blockLib.find(btypename) == _blockLib.end() )
    {
        // Build lib path
        QString lib_path = _blockLibDirectory + QDir::separator() + btypename;

        // Load module
        QSharedPointer<QLibrary> lib_block(new QLibrary(lib_path));
        if( ! lib_block->load() )
        {
            // Build error string
            QString error = QString("- Cannot load block '") + btypename + QString("': ") + lib_block->errorString();

            // Error
            throw std::runtime_error(error.toStdString());
        }
        
        // Save lib pointer
        _blockLib[btypename] = lib_block;
    }
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
    // Initialize and return the block
    block->blockInit(_wThis.toStrongRef());
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
        QString error = "The js script (" + script_path + ") does not exist";
        std::runtime_error(error.toStdString());
    }

    // Open the file
    if(!script_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString error = "The js script (" + script_path + ") cannot be opened";
        std::runtime_error(error.toStdString());
    }

    // Read the program
    QString program(script_file.readAll());

    // Evaluate the program
    QJSValue result = eval(program);

    std::cout << result.toString().toStdString() << std::endl;
}

/* ============================================================================
 *
 * */
void BotEngine::createBigBlock()
{
    // Create core block
    _bigBlock = BotBlock::CreateBlock<CoreBlock>("core");

    // Init block
    _bigBlock->blockInit(_wThis.toStrongRef());

    // Create a qt js object
    QJSValue js_val = _jsEngine->newQObject(_bigBlock.data());

    // Link it to the js engine
    go().setProperty(_bigBlock->getBlockName(), js_val);
}

/* ============================================================================
 *
 * */
QStringList BotEngine::availableBlockNames()
{
    QStringList names;

    return names;
}

