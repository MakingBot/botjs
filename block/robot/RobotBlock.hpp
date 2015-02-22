#ifndef ROBOTBLOCK_HPP
#define ROBOTBLOCK_HPP
//!
//! \file RobotBlock.hpp
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
#include <PhysicBlock.hpp>
#include <KinAsmBlock.hpp>

//!
//! Central data in robotic dev :-)
//! This block provide a main wrapper for the all robot structure
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class RobotBlock : public PhysicBlock
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName MEMBER _name )
    Q_PROPERTY(QString base READ baseToChain WRITE setBaseFromChain)

public:
    //!
    //! Default constructor
    //!
    explicit RobotBlock(const QString& name = QString("robot"), QObject *parent = 0)
        : PhysicBlock(name, parent), _name(name)
    {
        appendBlockIProperty("name", IProperty(IProperty::IPTypeString  , true));
        appendBlockIProperty("base", IProperty(IProperty::IPTypeSonBlock, QStringList( {"kinasm"} ) ));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("robot"); }

    //! FROM BotBlock
    virtual void selectBlockSons(QList<QSharedPointer<BotBlock> >& sons, const QStringList& types);

    // ========================================================================
    // => Property name

    //! Robot name getter
    const QString& name() const { return _name; }

    //! Robot name setter
    void setName(const QString& name)
    {
        _name = name;
        beglog() << "Change name for:" << name << endlog();
        emit blockiPropertyValuesChanged();
    }

    // ========================================================================
    // => Property base

    //! Base pointer getter
    BotBlock* base() { return _base.data(); }

    //! Base father chain
    QString baseToChain() { if(_base) return _base->getBlockFathersChain(); else return QString("NONE"); }

    //! Set the base from a father chain
    void setBaseFromChain(QString& chain)
    {
    	BotBlock* chainptr = BotBlock::getBlockFromFathersChain(chain);
    	if(chainptr)
    	{
    		_base = chainptr->toSpecializedSharedPointer<KinAsmBlock>();
    	}
    }

    //! Base pointer setter
    void setBase(BotBlock* base)
    {
    //     // Basic checks
        
    //     // Check the block is a body
        
    //     // If the block is a child of another robot, kidnap it
        
    //     // If the block is a part remove it from parts
        
    //     // set it as the base
    //     // _base = block->weakFromThis();
    }

    //! Base shared pointer getter
    // QSharedPointer<KinAsmBlock> sharedBase() { return _base; }


public slots:


    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master = true);

    //! FROM BotBlock
    virtual BotBlock* create(const QString& btypename, const QString& varname);

    // ========================================================================
    // => PhysicBlock redefinition: updater

    //! FROM PhysicBlock
    virtual void updatePhysicSlaves         ();

protected:

    //! Robot name
    QString _name;

    //! Robot base kinematic assembly
    QSharedPointer<KinAsmBlock> _base;

    //! Parts of the robot
    QList<QSharedPointer<KinAsmBlock> > _bodies;

};

#endif // ROBOTBLOCK_HPP
