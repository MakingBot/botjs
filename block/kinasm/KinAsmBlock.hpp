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

#include <BotBlock.hpp>

#include <QRealList.hpp>
#include <JointBlock.hpp>

//!
//! A body assembly
//!
class KinAsmBlock : public BotBlock
{
    Q_OBJECT

    Q_PROPERTY(AsmStruct structure   READ structure        WRITE setStructure     MEMBER _structure   )

    Q_PROPERTY(BotBlock* root        READ getBlockPtrRoot  WRITE setBlockPtrRoot                      )

    Q_PROPERTY(QRealList jointConfig READ jointConfig      WRITE setJointConfig   MEMBER _jointConfig )


public:
    //! Define block different roles
    enum AsmStruct { AsmTree, AsmChain } ;

    //!
    //! Default constructor
    //!
    explicit KinAsmBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : BotBlock(name, parent)
    {
        // TYPE 
        QMap<QString, int> struct_enum;
        struct_enum["Tree" ] = AsmTree ;
        struct_enum["Chain"] = AsmChain;
        appendBlockIProperty("structure" , IProperty(IProperty::IPTypeEnum, true, struct_enum));
    }

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BlockData; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("kinasm"); }

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

    //! Provide the BotBlock pointer of the root joint
    BotBlock* getBlockPtrRoot() { return qobject_cast<BotBlock*>( _root.data() ); }

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