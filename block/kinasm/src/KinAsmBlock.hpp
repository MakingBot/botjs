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

//!
//! A body assembly
//!
class KinAsmBlock : public BotBlock
{
    Q_OBJECT

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

    //! Assembly structure getter 
    AsmStruct structure() const { return _structure; }

    //! Assembly structure setter
    void setStructure(AsmStruct stru)
    {
        // Set
        _structure = stru;

        // Alert BotJs
        emit blockiPropertyValuesChanged();
    }

protected:

    //! Assembly structure
    AsmStruct _structure;

};

#endif // KINASMBLOCK_HPP

