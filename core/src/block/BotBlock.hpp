#ifndef BOTBLOCK_HPP
#define BOTBLOCK_HPP
//!
//! \file BotBlock.hpp
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

#include <QVariant>
#include <QMetaType>

#include <BotEngine.hpp>
#include <IProperty.hpp>
#include <LogBuffer.hpp>

//!
//! The BotBlock is the main component of the BotJs modular architecture. 
//! BotBlock is the master interface of all blocks.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class BotBlock : public QObject
{
    Q_OBJECT
    Q_ENUMS(BlockRole)
    
    Q_PROPERTY(QString      blockName               READ getBlockName           MEMBER _bname   CONSTANT    )
    Q_PROPERTY(float        blockVersion            READ getBlockVersion                                    )
    Q_PROPERTY(QString      blockTypename           READ getBlockTypeName                                   )
    Q_PROPERTY(BlockRole    blockRole               READ getBlockRole                                       )

    Q_PROPERTY(int          blockNbSons             READ getBlockNumberOfSons                               )
    Q_PROPERTY(int          blockNbConn             READ getBlockNumberOfConnections                        )

    Q_PROPERTY(bool         logEnable               READ isBlockLogEnable       WRITE setBlockLogEnable     )
    Q_PROPERTY(bool         logTalking              READ isBlockLogTalking      WRITE setBlockLogTalking    )

public:

    // === === === GLOBAL === === ===

    //! Define block different roles
    enum BlockRole { BlockCore, BlockData, BlockSpy, BlockCom, BlockUi } ;

    //! JavaScript engine used by the application
    static BotEngine JsEngine;

    //!
    //! Function that create and configure a safe block pointer
    //! The shared has to be stored by the parent block, else this block will be deleted
    //!
    template<typename BLOCK_TYPE>
    static QSharedPointer<BotBlock> CreateBlock(const QString& name, QObject* parent = 0)
    {
        // Create the block
        BLOCK_TYPE* block = new BLOCK_TYPE(name, parent);

        // Create the shared pointer
        QSharedPointer<BotBlock> shared_ptr = qSharedPointerObjectCast<BotBlock, BLOCK_TYPE>( QSharedPointer<BLOCK_TYPE>(block) );
        
        // Save it as a weak pointer in this
        shared_ptr->_wThis = shared_ptr.toWeakRef();

        // Return shared in order that parent can save it
        return shared_ptr;
    }

    //!
    //! Convert this specialized block pointer to a BotBlock pointer
    //! Specialized means that BLOCK_TYPE is a derived class of BotBlock
    //!
    template<typename BLOCK_TYPE>
    BotBlock* toBlockPointer()
    {
        return toBlockSharedPointer<BLOCK_TYPE>().data();
    }

    //! to a specialized block shared pointer
    template<typename BLOCK_TYPE>
    QSharedPointer<BotBlock> toBlockSharedPointer()
    {
        return qSharedPointerObjectCast<BotBlock, BLOCK_TYPE>( getBlockSharedFromThis() );
    }

    //!
    //! Convert this BotBlock pointer to a specialized block pointer
    //! Specialized means that BLOCK_TYPE is a derived class of BotBlock
    //!
    template<typename BLOCK_TYPE>
    BLOCK_TYPE* toSpecializedPointer()
    {
        return toSpecializedSharedPointer<BLOCK_TYPE>().data();
    }

    //! to a specialized block shared pointer
    template<typename BLOCK_TYPE>
    QSharedPointer<BLOCK_TYPE> toSpecializedSharedPointer()
    {
        return qSharedPointerObjectCast<BLOCK_TYPE, BotBlock>( getBlockSharedFromThis() );
    }

    //!
    //! Each role is associated to a color
    //!
    static QString BlockRoleToColor(BlockRole role)
    {
        switch(role)
        {
            case BlockCore: return QString("#795548"); break; // BROWN 500
            case BlockData: return QString("#2196F3"); break; // BLEU  500
            case BlockSpy : return QString("#9C27B0"); break; // PURPLE 500
            case BlockCom : return QString("#009688"); break; // TEAL  500
            case BlockUi  : return QString("#4CAF50"); break; // GREEN 500
            default       : return QString("#424242"); break; // GREY  800
        }
    }
    
    //!
    //! Each role is associated to a name
    //!
    static QString BlockRoleToString(BlockRole role)
    {
        switch(role)
        {
            case BlockCore: return QString("core");    break;
            case BlockData: return QString("data");    break;
            case BlockSpy : return QString("spy");     break;
            case BlockCom : return QString("com");     break;
            case BlockUi  : return QString("ui");      break;
            default       : return QString("unknown"); break;
        }
    }

    // === === === BLOCK === === ===

    //!
    //! Default constructor
    //!
    explicit BotBlock(const QString& name = QString(), QObject* parent = 0)
        : QObject(parent)
        , _bname(name)
        , _log(BotBlock::JsEngine.getBlockLogDirectory() + QDir::separator() + _bname + QString(".log"), this)
    { }

    //!
    //! Initialize block, each block has it own init process
    //!
    virtual void blockInit()
    {
        // Set log buffer id
        _log.setId(getBlockFathersChain());

        // Register type BotBlock*
        if( ! QMetaType::isRegistered(QMetaType::type("BotBlock*")) ) { qRegisterMetaType<BotBlock*>("BotBlock*"); }
    }

    //! Block version getter
    virtual float getBlockVersion() const = 0;

    //! Block role getter
    virtual BlockRole getBlockRole() const = 0;

    //! Block type name getter
    virtual QString getBlockTypeName() const = 0;

    //! Block name getter
    const QString getBlockName() const { return _bname; }

    //! Shared pointer on this object
    QWeakPointer<BotBlock> getBlockWeakFromThis() { return _wThis; }
    
    //! Shared pointer on this object
    QSharedPointer<BotBlock> getBlockSharedFromThis() { return _wThis.toStrongRef(); }

    // === === === LOG BUFFER === === ===

    //! To start a log
    LogBuffer& beglog() { return _log; }

    //! To stop the log
    LogEnder endlog() { return LogEnder(); }

    //!  Enable setter
    void setBlockLogEnable(bool en)  { _log.setStateEnable(en); }
    
    //! Talking setter
    void setBlockLogTalking(bool en) { _log.setStateTalk(en); } 

    //! Return true if this log buffer is enable and log into its file
    bool isBlockLogEnable()  { return _log.isEnable(); } 

    //! Return true if this log buffer is talking and log into the std cout
    bool isBlockLogTalking() { return _log.isTalking(); }

    // === === === I-PROPERTIES === === ===

    //! Interactive properties getter
    const QMap<QString, IProperty>& iProperties() { return _iProperties; }

    //! To append an interactive property
    void appendBlockIProperty(const QString& pname, IProperty iprop)
    {
        if( _iProperties.find(pname) == _iProperties.end() )
        {
            _iProperties.insert(pname, iprop);
        }
    }
    
    // To remove an interactive property
    void removeBlockIProperty(const QString& pname)
    {
        _iProperties.remove(pname);
    }

    // === === === CONNECTIONS === === ===

    //! Connections number getter
    virtual int getBlockNumberOfConnections() const { return _connections.size(); }

    // === === === FATHER AND SONS === === ===

    //! Block father getter
    QWeakPointer<BotBlock> getBlockFather() { return _father; }

    //! Block father setter
    void setBlockFather(BotBlock* father) { _father = father->getBlockWeakFromThis(); }

    //! Block father setter
    void setBlockFather(QWeakPointer<BotBlock> father) { _father = father; }

    //! Block fathers chain
    //! the chain from core block until this block separated by '.'
    QString getBlockFathersChain()
    {
        QString ret;
        QWeakPointer<BotBlock> fw = getBlockFather();
        if( fw )
        {
            QSharedPointer<BotBlock> fs = fw.toStrongRef();
            ret += fs->getBlockFathersChain();
            ret += ".";
        }
        ret += getBlockName();
        return ret;
    }
    
    //! Return the pointer on the block defined by the fathers chain 
    BotBlock* getBlockFromFathersChain(const QString& chain)
    {
        // Split the chain
        QStringList chainstr = chain.split(".");
        
        // Chain must have block
        if(chainstr.isEmpty()) { }
        
        // The chain must start with the core block
        if(chainstr.first().compare("core") != 0) { }
        chainstr.removeFirst();
        
        // Pointer on core
        BotBlock* ptr = BotBlock::JsEngine.getCoreBlock().data();
        
        // Find the end pointer
        foreach(QString str, chainstr)
        {
            BotBlock* son = ptr->getBlockSon(str);
            if(son) { ptr = son; }
        }
        return ptr;
    }

    //! Block sons getter
    virtual const QList<QSharedPointer<BotBlock> >& getBlockSons() const { return _sons; }

    //! Provide the fathers chains of each sons of this block
    QStringList getBlockSonsChains()
    {
        QStringList chains;
        foreach(QSharedPointer<BotBlock> son, _sons)        
        {
            chains << son->getBlockFathersChain();
        }
        return chains;
    }

    //! Block son getter by name
    virtual BotBlock* getBlockSon(const QString& name)
    {
        foreach(QSharedPointer<BotBlock> son, _sons)
        {
            if(son->getBlockName().compare(name) == 0) { return son.data(); }
        }
        return 0;
    }

    //! Append a son to this block
    virtual void appendBlockSon(QSharedPointer<BotBlock> son) { if( _sons.indexOf(son) == -1 ) { _sons << son; } }

    //! Block sons number getter
    virtual int getBlockNumberOfSons() const { return _sons.size(); }

    //! Easy way to get this information
    virtual bool hasSons() const { if(getBlockNumberOfSons()>0) { return true; } else { return false; } }

public slots:

    //!
    //! To connect the block to others
    //!
    virtual bool connect(BotBlock* block, bool master=true)
    {
        // Basic checks
        if(!block)        { beglog() << "Connection to null block failure" << endlog(); return false; }
        if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }
        
        // This block ask for a connection
        if(master)
        {
            if(!block->connect(this, false))
            {
                // Log and return
                beglog() << "Connection to #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
                return false;
            }
        }
        // Other block ask for a connection
        // Default behaviour : accept
        _connections << block->getBlockWeakFromThis();

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log and return
        beglog() << "Connection to #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }

    //!
    //! Ask for deconnection
    //!
    virtual void disconnect(BotBlock* block, bool master=true)
    {
        // Basic checks
        if(!block)        { beglog() << "Disconnection from null block failure" << endlog(); return ; }
        if(block == this) { beglog() << "Disconnection from itself refused"     << endlog(); return ; }
        
        // This block ask for a disconnection
        if(master)
        {
            block->disconnect(this, false);
        }

        // Delete pointer from connection
        _connections.removeAll(block->getBlockWeakFromThis());

        // Alert BotJs
        emit blockfPropertyValuesChanged();

        // Log
        beglog() << "Disconnection from #" << block->getBlockFathersChain() << "#" << endlog();
    }

    //!
    //! To delete all connections
    //!
    virtual void disconnectAll()
    {
        foreach(QWeakPointer<BotBlock> co, _connections)
        {
            QSharedPointer<BotBlock> coshared = co.toStrongRef();
            if(coshared)
            {
                this->disconnect(coshared.data());
            }
        }
    }

    //!
    //! Create a block as a child of this one
    //!
    virtual BotBlock* create(const QString& btypename, const QString& varname)
    {
        // Check if the name already exist 
        if(BotBlock::JsEngine.go().property(varname).toVariant().isValid())
        {
            beglog() << "Create block #" << btypename << "# failure: this name is already used" << endlog();
            return 0;
        }

        // Create block from the JsEngine
        QSharedPointer<BotBlock> block = BotBlock::JsEngine.createBlock(btypename, varname);

        // Set this as the block parent
        block->setBlockFather(this);
        
        // Add block to this son
        this->appendBlockSon(block);

        // Log
        beglog() << "Create block #" << block->getBlockName() << "#" << endlog();
     
        // return
        return block.data();
    }

signals:

    //! Emit when fixe property values has been modified
    void blockfPropertyValuesChanged();
    
    //! Emit when interactive property values has been modified
    void blockiPropertyValuesChanged();
    
    //! Emit when interactive property structure has been modified
    void blockiPropertyStructureChanged();

protected:

    // === === === BLOCK === === ===
    
    //! Block name
    //! Block variable name in the javascript global object
    const QString _bname;

    //! Smart pointer on this block
    QWeakPointer<BotBlock> _wThis;

    // === === === LOG BUFFER === === ===
    
    //! Block log buffer
    LogBuffer _log;

    // === === === I-PROPERTIES === === ===

    //! Interactives properties
    QMap<QString, IProperty> _iProperties;

    // === === === CONNECTIONS === === ===

    //! Connections
    QList<QWeakPointer<BotBlock> > _connections;

    // === === === FATHER AND SONS === === ===

    //! Father
    //! Father that have the ownership of this object
    QWeakPointer<BotBlock> _father;
    
    //! Sons
    //! When the father is killed, sons are automatically killed (funny isn't it?)
    QList<QSharedPointer<BotBlock> > _sons;
    
};

//! Define that allow to define the interface of the shared lib
#define EXPORT_BLOCK(__blocktype__) extern "C"              \
{                                                           \
Q_DECL_EXPORT QSharedPointer<BotBlock> CreateBlock(const QString& name)   \
{                                                           \
    return BotBlock::CreateBlock<__blocktype__>(name);      \
}                                                           \
}

#endif // BOTBLOCK_HPP
