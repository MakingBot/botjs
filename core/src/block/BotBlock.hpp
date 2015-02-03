#ifndef BOTBLOCK_HPP
#define BOTBLOCK_HPP

#include <QVariant>
#include <iostream>
#include <QMetaType>

#include <BotEngine.hpp>
#include <IProperty.hpp>

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

    Q_PROPERTY(int          blockNbSons             READ getBlockNumberOfSons                                    )
    Q_PROPERTY(int          blockNbConn             READ getBlockNumberOfConnections                                    )

public:

    // === === === GLOBAL === === ===

    //! Define block different roles
    enum BlockRole { BlockCore, BlockData, BlockSpy, BlockCom, BlockUi } ;

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
            case BlockCore: return QString("Core");    break;
            case BlockData: return QString("Data");    break;
            case BlockSpy : return QString("Spy");     break;
            case BlockCom : return QString("Com");     break;
            case BlockUi  : return QString("Ui");      break;
            default       : return QString("Unknown"); break;
        }
    }

    // === === === BLOCK === === ===

    //!
    //! Default constructor
    //!
    explicit BotBlock(const QString& name = QString(), QObject* parent = 0)
        : QObject(parent), _bname(name)
    { }

    //!
    //! Initialize block, each block has it own init process
    //!
    virtual void blockInit(QSharedPointer<BotEngine> js_engine)
    {
        _jsEngine = js_engine;
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

    //! Block sons number getter
    virtual int getBlockNumberOfSons() const { return _sons.size(); }

    //!
    //! Append a son to the list
    //!
    virtual void appendSon(QSharedPointer<BotBlock> son) { if( _sons.indexOf(son) == -1 ) { _sons << son; } }

public slots:

    //!
    //! To connect the block to others
    //!
    virtual bool connect(BotBlock* block, bool master=true)
    {
        // Basic checks
        if(!block)        { std::cerr << "-- BotBlock::connectBlock => null ptr"                    << std::endl; return false; }
        if(block == this) { std::cerr << "-- BotBlock::connectBlock => unable to connect to itself" << std::endl; return false; }
        
        // This block ask for a connection
        if(master)
        {
            if(!block->connect(this, false))
            {
                return false;
            }
        }
        // Other block ask for a connection
        // Default behaviour : accept
        _connections << block->getBlockWeakFromThis();
        return true;
    }

    //!
    //! Create a block as a child of this one
    //!
    virtual void create(const QString& btypename, const QString& varname)
    {
        // Check if the name already exist 
        if(this->property(varname.toStdString().c_str()).isValid())
        {
            QString error = "Name already given";
            throw std::runtime_error(error.toStdString());
        }
        
        // Create block from the JsEngine
        QSharedPointer<BotBlock> block = _jsEngine->createBlock(btypename, varname);
        
        // Set this as the block parent
        // block->setBlockParent(this);
        
        // Add block to this childs
        // this->appendChild(block);

        // Make the block accessible from js
        this->setProperty(varname.toStdString().c_str(), _jsEngine->engine()->newQObject(block.data()).toVariant());
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
    
    //! Pointer on the javascript engine
    QSharedPointer<BotEngine> _jsEngine;

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
