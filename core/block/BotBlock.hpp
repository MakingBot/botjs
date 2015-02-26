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
//! Log macro
//!
#define BLOCK_LOG(msg)  			\
if(blockLog() || blockTalk())  		\
{ 									\
	_logBuffer << msg << LogEnder();  \
}

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
    
    Q_PROPERTY(QString      blockName               READ blockName           MEMBER _bname   CONSTANT    	)
    Q_PROPERTY(float        blockVersion            READ blockVersion                                    	)
    Q_PROPERTY(QString      blockTypename           READ blockTypeName                                   	)
    Q_PROPERTY(BlockRole    blockRole               READ blockRole                                       	)

    Q_PROPERTY(int          blockNbSons             READ blockNbSons                               			)
   // Q_PROPERTY(int          blockNbConn             READ getBlockNumberOfConnections                        )

    Q_PROPERTY(bool         log               		READ blockLog       	WRITE setBlockLog     			)
    Q_PROPERTY(bool         talk              		READ blockTalk      	WRITE setBlockTalk    			)

public:

	//!
    //! Define different block roles
	//!
    enum BlockRole { BlockCore, BlockData, BlockSpy, BlockCom, BlockUi } ;

    // ========================================================================
    // => Block basic information

    //!
    //! Block version getter
    //!
    virtual float     blockVersion   () const = 0;

    //!
    //! Block role getter
    //!
    virtual BlockRole blockRole      () const = 0;

    //!
    //! Block type name getter
    //!
    virtual QString   blockTypeName  () const = 0;

    //!
    //! Block name getter
    //!
    const   QString   blockName      () const { return _bname; }

    // ========================================================================
    // => Block pointer management

    //!
    //! Function that create and configure a safe block pointer
    //! The shared has to be stored by the father block, else this block will be deleted
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
    //! Default constructor
    //!
    explicit BotBlock(const QString& name = QString(), QObject* parent = 0)
        : QObject(parent)
        , _bname(name)
    	, _idNumber(BlockCounter++)
        , _logBuffer(BotBlock::JsEngine.getBlockLogDirectory() + QDir::separator() + _bname + QString(".log"), this)
    { }

    //!
    //! Initialize block, each block has it own init process
    //!
    virtual void blockInit()
    {
        // Set the log buffer id with the id chain
    	_logBuffer.setId( blockIdChain() );

        // Register type BotBlock*
        if( ! QMetaType::isRegistered(QMetaType::type("BotBlock*")) ) { qRegisterMetaType<BotBlock*>("BotBlock*"); }
    }

    //!
    //! Return a weak pointer on this block
    //!
    QWeakPointer<BotBlock>   toBlockWeakPointer           	()
    {
        return _wThis;
    }

    //!
    //! Return a shared pointer on this block
    //!
    QSharedPointer<BotBlock> toBlockSharedPointer         	()
    {
        return _wThis.toStrongRef();
    }

    //!
    //! Convert this BotBlock pointer to a specialized block pointer
    //! Specialized means that B_TYPE is a derived class of BotBlock
    //!
    template<typename B_TYPE>
    B_TYPE*                  toSpecializedPointer           ()
    {
        return toSpecializedSharedPointer<B_TYPE>().data();
    }

    //!
    //! Convert this BotBlock pointer to a specialized block shared pointer
    //! Specialized means that B_TYPE is a derived class of BotBlock
    //!
    template<typename B_TYPE>
    QSharedPointer<B_TYPE>   toSpecializedSharedPointer     ()
    {
        return qSharedPointerObjectCast<B_TYPE, BotBlock>( toBlockSharedPointer() );
    }

    // ========================================================================
    // => Block father and block sons

    //!
    //! Block father weak pointer getter
    //!
    QWeakPointer<BotBlock> blockFatherWeakPointer()
    {
    	return _father;
    }

    //!
	//! Block father shared pointer getter
	//!
	QWeakPointer<BotBlock> blockFatherSharedPointer()
	{
		return _father.toStrongRef();
	}

    //!
    //! Block father setter from a block pointer
    //!
    void setBlockFather(BotBlock* father)
    {
    	setBlockFather(father->toBlockWeakPointer());
    }

    //!
    //! Block father setter from a block weak pointer
    //!
    void setBlockFather(QWeakPointer<BotBlock> father)
    {
    	_father = father;
    	updateIdChain();
    }

    //!
    //! Block son getter by name
    //!
    QSharedPointer<BotBlock> blockSonSharedPointer(const QString& name)
    {
    	if( _sons.find(name) != _sons.end() )
    	{
    		return _sons[name];
    	}
        return QSharedPointer<BotBlock>(0);
    }

    //! Block sons getter
    const QMap<QString, QSharedPointer<BotBlock> >& blockSons() const
    {
    	return _sons;
    }

    //!
    //! Append a son to this block
    //!
    virtual void appendBlockSon(QSharedPointer<BotBlock> son)
    {
    	const QString name = son->blockName();
    	if( _sons.find(name) == _sons.end() )
		{
    		_sons[name] = son;
		}
    }

    //!
    //! Block sons number getter
    //!
    int blockNbSons() const
    {
    	return _sons.size();
    }

    //!
    //! Easy way to get this information
    //!
    bool blockHasSons() const
    {
    	if( blockNbSons() > 0 )
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }

    //!
    //! Return son block pointers that have the compatible type
    //!
    void blockSelectedSons(QList<QSharedPointer<BotBlock> >& sons, const QStringList& types)
    {
        // Clear the list
        sons.clear();

        QMapIterator<QString, QSharedPointer<BotBlock> > i(_sons);
        while (i.hasNext())
        {
            i.next();
            if( types.indexOf( i.value()->blockTypeName() ) != -1 )
            {
                sons << i.value();
            }
        }
    }

    //!
    //! Return id chains of son blocks that have the compatible type
    //!
    void blockSelectedSonChains(QStringList& chains, const QStringList& types)
    {
        // Clear the list
        chains.clear();

        // Get selected sons
        QList<QSharedPointer<BotBlock> > sons;
        blockSelectedSons(sons, types);

        // Fil the chain
        foreach(QSharedPointer<BotBlock> son, sons)
        {
            chains << son->blockIdChain();
        }
    }

    //!
    //! Provide the id chains of each sons of this block
    //!
    void blockAllSonChains(QStringList& chains)
    {
        // Clear the list
        chains.clear();
        QMapIterator<QString, QSharedPointer<BotBlock> > i(_sons);
        while (i.hasNext())
        {
            i.next();
            chains << i.value()->blockIdChain();
        }
    }


    // ========================================================================
    // => Block identification

    //!
    //! ID Chain getter
    //!
	const QString& blockIdChain() const
	{
		return _idChain;
	}

	//!
	//! Update ID Chain
	//!
    void updateIdChain()
    {
    	// Clear the chain
    	_idChain.clear();

    	// Initialize
    	_idChain = blockName();

    	// Get the father
        QSharedPointer<BotBlock> next = blockFatherSharedPointer();
        while(next)
        {
        	// Prepare parent piece of chain
        	QString chain = next->blockName() + '.';
        	_idChain.insert(0, chain);

        	// Get next parent
        	next = blockFatherSharedPointer();
        }
    }

    //!
    //! Return the pointer on the block defined by the id chain
    //!
    static QSharedPointer<BotBlock> IdChainToBlockPointer(const QString& chain)
    {
        // Split the chain
        QStringList chainstr = chain.split(".");

        // Chain must have block
        if(chainstr.isEmpty()) { }

        // The chain must start with the core block
        if(chainstr.first().compare("core") != 0) { }
        chainstr.removeFirst();

        // Pointer on core
        QSharedPointer<BotBlock> ptr = BotBlock::JsEngine.getCoreBlock();

        // Find the end pointer
        foreach(QString str, chainstr)
        {
        	QSharedPointer<BotBlock> son = ptr->blockSonSharedPointer(str);
            if(son) { ptr = son; }
        }
        return ptr;
    }

    //!
    //! ID Number getter
    //!
    quint32 blockIdNumber() const
    {
    	return _idNumber;
    }

    //!
    //! ID Number setter
    //!
	void setBlockIdNumber(quint32 id)
	{
		_idNumber = id;
	}

    // ========================================================================
    // => Block connections

	//!
    //! Connections number getter
    //!
	int blockNbConnections() const
    {
    	return _connections.size();
    }

    // ========================================================================
    // => Block log and talk

	//!
    //! Log enable getter
    //!
    bool blockLog()
    {
    	return _logBuffer.logEnable();
    }

    //!
    //! Log enable setter
    //!
    void setBlockLog(bool e)
    {
    	_logBuffer.setLogEnable(e);
    }

	//!
    //! Talk enable getter
    //!
    bool blockTalk()
    {
    	return _logBuffer.talkEnable();
    }

    //!
    //! Talk enable setter
    //!
    void setBlockTalk(bool e)
    {
    	_logBuffer.setTalkEnable(e);
    }



    // ========================================================================
    // => Block architecture parameters

    //!
    //! Block size getter
    //!
    const QSize& blockSize()
    {
        return _bsize;
    }

    //!
    //! Block size setter
    //!
    void setBlockSize(const QSize& size)
    {
        _bsize = size;
    }

    //!
    //! Block position getter
    //!
    const QPointF& blockPosition()
    {
        return _bposition;
    }

    //!
    //! Block position setter
    //!
    void setBlockPosition(const QPointF& pos)
    {
        _bposition = pos;
    }



    // ========================================================================
    // => Block static members

    //! JavaScript engine used by the application
    static BotEngine JsEngine;

    //! Number of block created since the beginning of the session
    static quint32 BlockCounter;

    //! Map to get a direct access to every block created
    static QMap<quint32, QSharedPointer<BotBlock> > BlockMap;

    //! Generate a Id number for the block
    static void GenerateIdNumber(QSharedPointer<BotBlock> block);

    //! To get a block with its Id number
    static QSharedPointer<BotBlock> IdNumberToBlock(quint32 id);

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



public slots:

	// ========================================================================
	// => Block pointer management

	//!
	//! Create a block as a child of this one
	//!
	virtual BotBlock* create(const QString& btypename, const QString& varname)
	{
		// Check if the name already exist
		if(BotBlock::JsEngine.go().property(varname).toVariant().isValid())
		{
			BLOCK_LOG("Create block #" << btypename << "# failure: this name is already used");
			return 0;
		}

		// Create block from the JsEngine
		QSharedPointer<BotBlock> block = BotBlock::JsEngine.createBlock(btypename, varname);

		// Set this as the block parent
		block->setBlockFather(this);

		// Add block to this son
		appendBlockSon(block);

		// Log
		BLOCK_LOG("Create block #" << block->blockName() << "#" << " [ID:" << block->blockIdNumber() << "]");

		// return
		return block.data();
	}

	// ========================================================================
	// => Block connections

    //!
    //! To connect the block to others
    //!
    bool connect(BotBlock* block, bool master=true)
    {
        // Basic checks
        if(!block)        { BLOCK_LOG("Connection to null block failure"); return false; }
        //if(block == this) { beglog() << "Connection to itself refused"     << endlog(); return false; }
        
        // This block ask for a connection
        if(master)
        {
            if(!block->connect(this, false))
            {
                // Log and return
                //beglog() << "Connection to #" << block->getBlockFathersChain() << "# failure: connection return refused" << endlog();
                return false;
            }
        }
        // Other block ask for a connection
        // Default behavior : accept
       // _connections << block->toBlockWeakPointer();

        // Alert BotJs
        //emit blockfPropertyValuesChanged();

        // Log and return
        //beglog() << "Connection to #" << block->getBlockFathersChain() << "#" << endlog();
        return true;
    }

    //!
    //! Ask for reconnection
    //!
    virtual void disconnect(BotBlock* block, bool master=true)
    {
        // Basic checks
        //if(!block)        { beglog() << "Disconnection from null block failure" << endlog(); return ; }
        //if(block == this) { beglog() << "Disconnection from itself refused"     << endlog(); return ; }
        
        // This block ask for a disconnection
        if(master)
        {
            block->disconnect(this, false);
        }

        // Delete pointer from connection
       // _connections.removeAll(block->toBlockWeakPointer());

        // Alert BotJs
        //emit blockfPropertyValuesChanged();

        // Log
       //beglog() << "Disconnection from #" << block->getBlockFathersChain() << "#" << endlog();
    }

    //!
    //! To delete all connections
    //!
    virtual void disconnectAll()
    {
//        foreach(QWeakPointer<BotBlock> co, _connections)
//        {
//            QSharedPointer<BotBlock> coshared = co.toStrongRef();
//            if(coshared)
//            {
//                this->disconnect(coshared.data());
//            }
//        }
    }

signals:

	//! Signal
	//! Emitted when father or sons changed
	//!
    void blockFamilyChanged();

	//! Signal
	//! Emitted when connections has been appended or deleted
	//!
    void blockConnectionsChanged();

    //! Signal
    //! Emit when interactive property values has been modified
    //!
    void blockiPropertyValuesChanged();
    
    //! Signal
    //! Emit when interactive property structure has been modified
    //!
    void blockiPropertyStructureChanged();

protected:

    // ========================================================================
    // => Block basic information

    //! Block name
    //! Block variable name in the JavaScript global object
    const QString _bname;

    // ========================================================================
    // => Block pointer management

    //! Smart pointer on this block
    QWeakPointer<BotBlock> _wThis;

    // ========================================================================
    // => Block father and block sons

    //! Father
    //! Father that have the ownership of this object
    QWeakPointer<BotBlock> _father;

    //! Sons
    //! When the father is killed, sons are automatically killed (funny isn't it?)
    QMap<QString, QSharedPointer<BotBlock> > _sons;

    // ========================================================================
    // => Block identification

    //! ID Chain
    //! The id chain is a unique string id to define this block pointer
    //! It is composed of every father of this block separated with a dot
    QString _idChain;

    //! ID Number
    //! When a block is created, it get a unique global ID number
    quint32 _idNumber;

    // ========================================================================
    // => Block connections

    //! Connections
    QMap<QString, QWeakPointer<BotBlock> > _connections;

    // ========================================================================
    // => Block log and talk
    
    //! Block log buffer
    LogBuffer _logBuffer;

    // ========================================================================
    // => Block interactive properties

    //! Interactive properties
    QMap<QString, IProperty> _iProperties;

    // ========================================================================
    // => Block architecture parameters

    //! Size
    //! Size of the block in the architecture map
    QSize _bsize;

    //! Position
    //! Position of the block in the architecture map
    //! This position is relative the father position
    QPointF _bposition;

};

//!
//! Define that allow to define the interface of the shared lib
//!
//!
//! Define that allow to define the interface of the shared lib
//!
#define EXPORT_BLOCK(__blocktype__) extern "C"              \
{                                                           \
QSharedPointer<BotBlock> CreateBlock(const QString& name)   \
{                                                           \
    return BotBlock::CreateBlock<__blocktype__>(name);      \
}                                                           \
}


#endif // BOTBLOCK_HPP
