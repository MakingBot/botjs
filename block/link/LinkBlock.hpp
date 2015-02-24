#ifndef LINKBLOCK_HPP
#define LINKBLOCK_HPP
//!
//! \file LinkBlock.hpp
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

#include <QVector3D>
#include <QMatrix4x4>
#include <PhysicBlock.hpp>

class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class LinkBlock : public PhysicBlock
{
    Q_OBJECT

    // ========================================================================
    // => Property declaration

    Q_PROPERTY(qreal        length      READ length         WRITE setLength      )
    Q_PROPERTY(QVector3D    direction   READ direction      WRITE setDirection   )
    Q_PROPERTY(QVector3D    translation READ translation    WRITE setTranslation )

/*

*/

public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : PhysicBlock(name, parent), _rotation({0,0,0})
    {
        appendBlockIProperty("length"     , IProperty(IProperty::IPTypeReal    , true  ));
        appendBlockIProperty("direction"  , IProperty(IProperty::IPTypeVector3D, false ));
        appendBlockIProperty("translation", IProperty(IProperty::IPTypeVector3D, false ));

        appendBlockIProperty("transform"  , IProperty(IProperty::IPTypeMatrix44, false));

        // appendBlockIProperty("nameBase"   , IProperty(IProperty::IPTypeString, false));
        // appendBlockIProperty("nameEnd"    , IProperty(IProperty::IPTypeString, false));

        // First update
        updateLink();
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float blockVersion() const { return 1.0; }
  
    //! FROM BotBlock
    virtual QString blockTypeName() const { return QString("link"); }

    //! FROM BotBlock
    virtual int getBlockNumberOfConnections() const
    {
        int nb = BotBlock::getBlockNumberOfConnections();
        if( _injoint  ) { nb++; }
        if( _outjoint ) { nb++; }
        return nb;
    }

    // ========================================================================
    // => Property length

    //! Length getter
    qreal length() { return _translation.length(); }

    //! Length setter
    void setLength(qreal length)
    {
        if( length >= 0 )
        {
            if( direction() == QVector3D(0,0,0) ) { _translation = QVector3D(0,0,1); }
            setTranslation( direction() * length );
        }
    }

    // ========================================================================
    // => Property direction

    //! Direction getter
    QVector3D direction() { return _translation.normalized(); }

    //! Direction setter
    void setDirection(const QVector3D& direction)
    {
        if( length() == 0 ) { _translation = QVector3D(0,0,1); }
        setTranslation( direction * length() );
    }

    // ========================================================================
    // => Property translation

    //! Link translation getter
    const QVector3D& translation() { return _translation; }

    //! Link translation setter
    void setTranslation(const QVector3D& translation)
    {
        // Set the new translation
        _translation = translation;

        // Full update
        updateLink();
    }

    // ========================================================================
    // => Property in joint

    //! In joint pointer getter
    JointBlock* inJoint() { return _injoint.data(); }

    //! In joint weak pointer getter
    QWeakPointer<JointBlock> weakInJoint() { return _injoint; }

    //! In joint shared pointer getter
    QSharedPointer<JointBlock> sharedInJoint() { return _injoint.toStrongRef(); }

    //! Check if the link has a base
    bool hasInJoint() { if(_injoint) { return true; } else { return false; } }


    // ========================================================================
    // => Property out joint

    //! Joint output getter    QWeakPointer<JointBlock> weakOutput() { return _outjoint; }

    //! Joint base weak pointer getter    QSharedPointer<JointBlock> sharedOutput() { return _outjoint.toStrongRef(); }


signals:

public slots:

    //! To update the transform matrix with the translation and rotation matrix
    //! after a parameter change
    //!
    void updateLink();

    // ========================================================================
    // => BotBlock redefinition: connection system

    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnectAll();

    // ========================================================================
    // => PhysicBlock redefinition: updaters

    //! FROM PhysicBlock
    virtual void updatePhysicShapeData      ();
    //! FROM PhysicBlock
    virtual void updatePhysicPosition       ();
    //! FROM PhysicBlock
    virtual void updatePhysicTransform      ();
    //! FROM PhysicBlock
    virtual void updatePhysicPreTransform   ();
    //! FROM PhysicBlock
    virtual void updatePhysicPostTransform  ();
    //! FROM PhysicBlock
    virtual void updatePhysicSlaves         ();

protected:

    //! Link translation
    //! Position of the out joint in the in joint basis
    //!
    QVector3D _translation;

    //! Link rotation
    //! By default, Joints are axed on the Z vector.
    //! Link can provide a rotation to modify the axe of the outputJoint.
    //!
    //! _rotation = { 0, 90, 45 } means rotate 0°  around x axis
    //!                                 rotate 90° around y axis
    //!                                 rotate 45° around z axis
    QVector3D _rotation;

    //! In Joint
    //! Joint that is at the beginning of the link
    //!
    QWeakPointer<JointBlock> _injoint;

    //! Out Joint
    //! Joint that is at the end of the link
    //!
    QWeakPointer<JointBlock> _outjoint;

};

#endif // LINKBLOCK_HPP

