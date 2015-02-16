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

#include <QMatrix4x4>
#include <QVariantList>
#include <QRealList.hpp>
#include <PhysicBlock.hpp>

class JointBlock;

//!
//! Fixe transformation between 2 joints
//! The link between 2 motors of a robot arm for example
//!
class LinkBlock : public PhysicBlock
{
    Q_OBJECT

    // ========================================================================
    // => Properties

    Q_PROPERTY(qreal        lenght      READ lenght         WRITE setLenght      )
    Q_PROPERTY(QVector3D    direction   READ direction      WRITE setDirection   )
    Q_PROPERTY(QVector3D    translation READ translation    WRITE setTranslation )

    Q_PROPERTY(QList<qreal>  rotation    READ rotation    WRITE setRotation     MEMBER _rotation   )
    Q_PROPERTY(QMatrix4x4    transform   READ transform                                            )

    Q_PROPERTY(QString       nameBase    READ baseName                                             )
    Q_PROPERTY(QString       nameEnd     READ endName                                              )

public:
    //!
    //! Default constructor
    //!
    explicit LinkBlock(const QString& name = QString("kinasm"), QObject *parent = 0)
        : PhysicBlock(name, parent), _rotation({0,0,0})
    {
        appendBlockIProperty("lenght"     , IProperty(IProperty::IPTypeReal    , true  ));
        appendBlockIProperty("direction"  , IProperty(IProperty::IPTypeVector3D, false ));
        appendBlockIProperty("translation", IProperty(IProperty::IPTypeVector3D, false ));

        appendBlockIProperty("rotation"   , IProperty(IProperty::IPTypeRealList, true ));
        appendBlockIProperty("transform"  , IProperty(IProperty::IPTypeMatrix44, false));

        appendBlockIProperty("nameBase"   , IProperty(IProperty::IPTypeString, false));
        appendBlockIProperty("nameEnd"    , IProperty(IProperty::IPTypeString, false));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }
  
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

    // ========================================================================
    // => PhysicBlock redefinition

    //! FROM PhysicBlock
    ShapeType getShapeType(ModelType model)
    {
        switch(model)
        {
            case ModelTypeKinematic: 
                return PhysicBlock::ShapeTypeArrow;
                break;

            default: return ShapeTypeNone; break;
        }
    }

    //! FROM PhysicBlock
    virtual QList<QSharedPointer<PhysicBlock> > getPhysicSlaves();

    //! FROM PhysicBlock
    virtual QMatrix4x4 getPreTransform();

    //! FROM PhysicBlock
    virtual QMatrix4x4 getPostTransform();


    virtual qreal getShapeLenght() { return lenght(); }


    // ========================================================================
    // => Property lenght

    //! Lenght getter
    qreal lenght() { return _translation.length(); }

    //! Lenght setter
    void setLenght(qreal lenght)
    {
        if( lenght >= 0 )
        {
            if( direction() == QVector3D(0,0,0) ) { _translation = QVector3D(0,0,1); }
            setTranslation( direction() * lenght );
        }
    }

    // ========================================================================
    // => Property direction

    //! Direction getter
    QVector3D direction() { return _translation.normalized(); }

    //! Direction setter
    void setDirection(const QVector3D& direction) { setTranslation( direction * lenght() ); }

    // ========================================================================
    // => Property translation

    //! Link translation getter
    const QVector3D& translation() { return _translation; }

    //! Link translation setter
    void setTranslation(const QVector3D& translation)
    {
        // Set the new translation
        _translation = translation;

        // Log
        beglog() << "Change translation parameter: " << _translation << endlog();


        emit blockPhysicStructureChanged();
        
        // Update transformation
        updateKinematic();
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


    void updateShapeData();


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
    
    //! Position of the outputJoint in the baseJoint basis
    QVector3D _translation;

    //! Link rotation
    //! By default, Joints are axed on the Z vector.
    //! Link can provide a rotation to modify the axe of the outputJoint.
    //!
    //! _rotation = { 0, 90, 45 } means rotate 0°  around x axis
    //!                                 rotate 90° around y axis
    //!                                 rotate 45° around z axis
    QRealList _rotation;
    


    //! Transform matrix
    //! It is computed from translation and rotation
    QMatrix4x4  _transform;

    QMatrix4x4 _preTransform;

    QMatrix4x4 _postTransform;
    
    //! Joint base
    QWeakPointer<JointBlock> _baseJoint;

    //! Joint output
    QWeakPointer<JointBlock> _outputJoint;

};

#endif // LINKBLOCK_HPP
