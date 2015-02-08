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
#include <QVariantList>
#include <QRealList.hpp>

class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
class LinkBlock : public BotBlock
{
    Q_OBJECT

    Q_PROPERTY(QList<qreal>  rotation    READ rotation    WRITE setRotation     MEMBER _rotation   )
    Q_PROPERTY(QList<qreal>  translation READ translation WRITE setTranslation  MEMBER _translation)
    Q_PROPERTY(QMatrix4x4    transform   READ transform                                            )

    Q_PROPERTY(QString       nameBase    READ baseName                                             )
    Q_PROPERTY(QString       nameEnd     READ endName                                              )

public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : BotBlock(name, parent), _rotation({0,0,0}), _translation({0,0,0})
    {
        appendBlockIProperty("rotation"   , IProperty(IProperty::IPTypeRealList, true ));
        appendBlockIProperty("translation", IProperty(IProperty::IPTypeRealList, true ));
        appendBlockIProperty("transform"  , IProperty(IProperty::IPTypeMatrix44, false));

        appendBlockIProperty("nameBase"   , IProperty(IProperty::IPTypeString, false));
        appendBlockIProperty("nameEnd"    , IProperty(IProperty::IPTypeString, false));
    }

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }
  
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("link"); }

    //! FROM BotBlock
    virtual int getBlockNumberOfConnections() const
    {
        int nb = BotBlock::getBlockNumberOfConnections();
        if( _baseJoint   ) { nb++; }
        if( _outputJoint ) { nb++; }
        return nb;
    }

    //! Link rotation getter
    const QList<qreal>& rotation() { return _rotation; }
   
    //! Link rotation setter
    void setRotation(const QList<qreal>& rotation)
    {
        // Set the new rotation
        _rotation = rotation;

        // Log
        beglog() << "Change rotation parameter: " << _rotation << endlog();
        
        // Update transformation
        updateKinematic();
    }
   
    //! Link translation getter
    const QList<qreal>& translation() { return _translation; }

    //! Link translation setter
    void setTranslation(const QList<qreal>& translation)
    {
        // Set the new translation
        _translation = translation;

        // Log
        beglog() << "Change translation parameter: " << _translation << endlog();
        
        // Update transformation
        updateKinematic();
    }

    //! Transform matrix getter
    const QMatrix4x4& transform() const { return _transform; }
    
    //! Transform matrix setter
    void setTransform(const QMatrix4x4& matrix)
    {
        // Set the new transform
        _transform = matrix;

        // Alert chain elements
        emit spreadKinematic();

        // Alert BotJs
        emit blockiPropertyValuesChanged();
    }


    //! Check if the link has a base
    bool hasBase() { if(_baseJoint) { return true; } else { return false; } }

    //! Joint base
    JointBlock* base() { return _baseJoint.data(); }

    //! Joint base weak pointer getter
    QWeakPointer<JointBlock> weakBase() { return _baseJoint; }
 
    //! Joint base weak pointer getter
    QSharedPointer<JointBlock> sharedBase() { return _baseJoint.toStrongRef(); }

    //! Getter for the base name
    QString baseName();


    //! Joint output getter
    QWeakPointer<JointBlock> weakOutput() { return _outputJoint; }

    //! Joint base weak pointer getter
    QSharedPointer<JointBlock> sharedOutput() { return _outputJoint.toStrongRef(); }

    //! Getter for the base name
    QString endName();

signals:

    //! Emitted when transform is modified
    void spreadKinematic();

public slots:

    //! To update the transform matrix with the translation and rotation matrix
    //! after a parameter change
    void updateKinematic();

    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnectAll();

protected:

    //! Link rotation
    //! By default, Joints are axed on the Z vector.
    //! Link can provide a rotation to modify the axe of the outputJoint.
    //!
    //! _rotation = { 0, 90, 45 } means rotate 0°  around x axis
    //!                                 rotate 90° around y axis
    //!                                 rotate 45° around z axis
    QRealList _rotation;
    
    //! Position of the outputJoint in the baseJoint basis
    QRealList _translation;
    
    //! Transform matrix
    //! It is computed from translation and rotation
    QMatrix4x4  _transform;

    //! Joint base
    QWeakPointer<JointBlock> _baseJoint;

    //! Joint output
    QWeakPointer<JointBlock> _outputJoint;

};

#endif // LINKBLOCK_HPP
