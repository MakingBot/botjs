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

#include <BotBlock.hpp>

#include <QMatrix4x4>

class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
class LinkBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(QVector3D  rotation    READ rotation    WRITE setRotation     MEMBER _rotation   )
    Q_PROPERTY(QVector3D  translation READ translation WRITE setTranslation  MEMBER _translation)

public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : BotBlock(name, parent)
    {
        appendBlockIProperty("rotation"   , IProperty(IProperty::IPTypeVector3D, true));
        appendBlockIProperty("translation", IProperty(IProperty::IPTypeVector3D, true));
    }

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }
  
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("link"); }


    //! Link rotation getter
    const QVector3D& rotation() { return _rotation; }
   
    //! Link rotation setter
    void setRotation(const QVector3D& rot) { _rotation = rot; updateTransform(); }
   
    //! Link translation getter
    const QVector3D& translation() { return _translation; }

    //! Link translation setter
    void setTranslation(const QVector3D& tra) { _translation = tra; }

    //! Transform matrix getter
    const QMatrix4x4& transform() const { return _transform; }
    
    //! Transform matrix setter
    void setTransform(const QMatrix4x4& matrix) { _transform = matrix; }

public slots:

    //! To update the transform matrix with the translation and rotation matrix
    //! after a parameter change
    void updateTransform()
    {

    }

protected:

    //! Link rotation
    //! By default, Joints are axed on the Z vector.
    //! Link can provide a rotation to modify the axe of the outputJoint.
    //!
    //! _rotation = { 0, 90, 45 } means rotate 0°  around x axis
    //!                                 rotate 90° around y axis
    //!                                 rotate 45° around z axis
    QVector3D _rotation;
    
    //! Position of the outputJoint in the baseJoint basis
    QVector3D _translation;
    
    //! Transform matrix
    //! It is computed from translation and rotation
    QMatrix4x4 _transform;
    
    //! Link base
    QWeakPointer<JointBlock> _baseJoint;
    
    //! Link output
    QWeakPointer<JointBlock> _outputJoint;

};

#endif // LINKBLOCK_HPP
