#ifndef KINASMBLOCK_HPP
#define KINASMBLOCK_HPP
//!
//! \file KinAsmBlock.hpp
//!
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


#include <QRealList.hpp>
#include <JointBlock.hpp>
#include <PhysicBlock.hpp>

//!
//! A body assembly
//!
class KinAsmBlock : public PhysicBlock
{
    Q_OBJECT
	Q_ENUMS(AsmStruct)

    Q_PROPERTY(AsmStruct structure   READ structure        WRITE setStructure     MEMBER _structure   )
    Q_PROPERTY(QString   root        READ rootToChain        WRITE setRootFromChain       )

//    Q_PROPERTY(QRealList jointConfig READ jointConfig      WRITE setJointConfig   MEMBER _jointConfig )


public:
    //! Define block different roles
    enum AsmStruct { AsmTree, AsmChain } ;

    //!
    //! Default constructor
    //!
    explicit KinAsmBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : PhysicBlock(name, parent), _structure(AsmChain)
    {
        // TYPE 
        QMap<QString, int> struct_enum;
        struct_enum["Tree" ] = AsmTree ;
        struct_enum["Chain"] = AsmChain;
        appendBlockIProperty("structure" , IProperty(IProperty::IPTypeEnum, true, struct_enum));

        // ROOT
        appendBlockIProperty("root" , IProperty(IProperty::IPTypeSonBlock, QStringList( {"joint"} ) ));
    }

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BlockData; }

    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("kinasm"); }

    // === MEMBER STRUCTURE ===

    //! Assembly structure getter 
    AsmStruct structure() const { return _structure; }

    //! Assembly structure setter
    void setStructure(AsmStruct structure)
    {
        // Set
        _structure = structure;

        // Alert BotJs
        emit blockiPropertyValuesChanged();
    }

    // === MEMBER ROOT ===



    void setRootSharedPtr(QSharedPointer<JointBlock> root)
    {
    	// Set property
    	_root = root;

    	// Update slaves
    	updatePhysicSlaves();

    	// Alert BotJs
    	emit blockiPropertyValuesChanged();
    }


    //! Provide the BotBlock pointer of the root joint
    BotBlock* getBlockPtrRoot() { return qobject_cast<BotBlock*>( _root.data() ); }

    QString rootToChain() { if(_root) return _root->getBlockFathersChain(); else return QString("NONE"); }

    void setRootFromChain(QString& chain)
    {
    	BotBlock* chainptr = BotBlock::getBlockFromFathersChain(chain);
    	if(chainptr)
    	{
    		_root = chainptr->toSpecializedSharedPointer<JointBlock>();
    	}
    }

    //! Set the BotBlock pointer of the root joint
    void setBlockPtrRoot(BotBlock* block)
    {
        // Get and check
        QSharedPointer<JointBlock> r = block->toSpecializedSharedPointer<JointBlock>();
        if(! r) { return; }

        // Set
         _root  = r;

        // Alert BotJs
        emit blockiPropertyValuesChanged();
    }

    // === MEMBER JOINT CONFIG ===

    //! Joint config getter
    const QRealList& jointConfig() const { return _jointConfig; }

    //! Joint config setter
    void setJointConfig(const QRealList& li) { _jointConfig = li; }


public slots:

	//! FROM BotBlock
	virtual BotBlock* create(const QString& btypename, const QString& varname);

	// ========================================================================
	// => PhysicBlock redefinition: updaters

	//! FROM PhysicBlock
	virtual void updatePhysicSlaves();

protected:

    //! Assembly structure
    AsmStruct _structure;

    //! Assembly root, begin of the structure
    QSharedPointer<JointBlock> _root;

    //! Assembly connectors, ends of the structure
    QList<QSharedPointer<JointBlock> > _connectors;

    //! Joint Configuration
    QRealList _jointConfig;


};

#endif // KINASMBLOCK_HPP
