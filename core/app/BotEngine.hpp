#ifndef BOTENGINE_HPP
#define BOTENGINE_HPP
//!
//! \file BotEngine.hpp
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

#include <QObject>
#include <QLibrary>
#include <QWeakPointer>
#include <QSharedPointer>

#include <QJSEngine>
#include <QJSValueIterator>

class BotBlock;

//!
//! BotEngine provide an interface to use the JavaScript engine from Qt
//!
class BotEngine : public QObject
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit BotEngine(QObject *parent = 0);

    //!
    //! Block library directory getter
    //!
    const QString& getBlockLibDirectory() { return _blockLibDirectory; }

    //!
    //! Block library directory getter
    //!
    void setBlockLibDirectory(const QString& block_dir) { _blockLibDirectory = block_dir; }

    //!
    //! Block log directory getter
    //!
    const QString& getBlockLogDirectory() { return _blockLogDirectory; }

    //!
    //! Block log directory getter
    //!
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
    //! Get JavaScript global object
    //!
    QJSValue go() { return _jsEngine->globalObject(); }

    //!
    //! JsEngine getter
    //!
    QSharedPointer<QJSEngine> engine() { return _jsEngine; }

    //!
    //! To create the core block
    //!
    void createCoreBlock();

    //!
    //! Core block getter
    //!
    QSharedPointer<BotBlock> getCoreBlock()
    {
    	return _coreBlock;
    }

    //!
    //! Return names of the available blocks
    //!
    void availableBlockNames(QStringList& names);

    //! Return the list of all id chains
    //! It represents every blocks of the system
    void allIdChains(QStringList& chains);

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
