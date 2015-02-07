#ifndef BOTENGINE_HPP
#define BOTENGINE_HPP

#include <QObject>
#include <QLibrary>
#include <QWeakPointer>
#include <QSharedPointer>

#include <QJSEngine>
#include <QJSValueIterator>

class BotBlock;

//!
//! BotEngine provide an interface to use the javascript engine from Qt
//!
class BotEngine : public QObject
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit BotEngine(QObject *parent = 0);

    //! Block lib directory getter
    const QString& getBlockLibDirectory() { return _blockLibDirectory; }

    //! Block lib directory getter
    void setBlockLibDirectory(const QString& block_dir) { _blockLibDirectory = block_dir; }

    //! Block lib directory getter
    const QString& getBlockLogDirectory() { return _blockLogDirectory; }

    //! Block lib directory getter
    void setBlockLogDirectory(const QString& block_dir) { _blockLogDirectory = block_dir; }


    //!
    //! Create a new block from a shared library
    //!
    QSharedPointer<BotBlock> createBlock(const QString& btypename, const QString& varname);

    //!
    //! Resolve creation block function in the lib
    //!
    QSharedPointer<BotBlock> resolveBlockLibCreation(QSharedPointer<QLibrary> lib, const QString& btypename, const QString& varname);

    //!
    //! Js evaluation of the program inside the given ScriptFile
    //! \param script_path
    //!
    void evalScriptFile(const QString& script_path);

    //!
    //! Js Evaluation
    //! \param program
    //!
    QJSValue eval(const QString& program) { return _jsEngine->evaluate(program); }

    //!
    //! Get javascript global object
    //!
    QJSValue go() { return _jsEngine->globalObject(); }

    //!
    //! JsEngine getter
    //!
    QSharedPointer<QJSEngine> engine() { return _jsEngine; }

    //! To create the big block
    void createCoreBlock();

    //! Core block getter
    QSharedPointer<BotBlock> getCoreBlock() { return _coreBlock; }

    //! Return the name of the available blocks
    QStringList availableBlockNames();

    //! Return the list of all father chain
    //! It represents every blocks of the system
    QStringList getAllFatherChains();

protected:
    //! Block lib directory
    QString _blockLibDirectory;

    //! Block log directory
    QString _blockLogDirectory;

    //! JavaScript engine
    QSharedPointer<QJSEngine> _jsEngine;

    //! Pointer on the global parent block
    QSharedPointer<BotBlock> _coreBlock;
    
    //! Track block library already loaded
    QMap<QString, QSharedPointer<QLibrary>> _blockLib;
};

#endif // BOTENGINE_HPP
