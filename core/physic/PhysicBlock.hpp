#ifndef PHYSICBLOCK_HPP
#define PHYSICBLOCK_HPP
//!
//! \file PhysicBlock.hpp
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

#include <QMatrix4x4>
#include <QQuaternion>
#include <BotBlock.hpp>
#include <ShapeData.hpp>

//!
//! The physic block is an interface for blocks with a physic reality.
//! For example, they have a mass and a solid shape. They can be rendered in an 3D environment.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class PhysicBlock : public BotBlock
{
    Q_OBJECT
    Q_ENUMS(ModelType)

    Q_PROPERTY(QVector4D position READ getPhysicPosition )

public:

    // ========================================================================
    // => Global

    //! Define model types
    enum ModelType { ModelTypeBase, ModelTypeKinematic };

    //!
    //! Default constructor
    //!
    explicit PhysicBlock(const QString& name = QString(), QObject *parent = 0)
        : BotBlock   (name, parent)
        , _modelType (ModelTypeKinematic)
    {
        // POSITION
        appendBlockIProperty("position", IProperty(IProperty::IPTypeVector4D, false));
    }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockData; }

    // ========================================================================
    // => Basic getter and setter

    //!
    //! Model type setter
    //!
    virtual void setModelType(ModelType model)              {  _modelType = model; }

    //!
    //! Model type getter
    //!
    virtual ModelType modelType()                           const { return _modelType; }

    //!
    //! Shape data getter 
    //!
    virtual const ShapeData& getPhysicShapeData()           const { return _shapeData; }

    //!
    //! Physic position getter
    //!
    virtual const QVector4D& getPhysicPosition()            const { return _position; }

    //!
    //! Physic transform getter
    //!
    virtual const QMatrix4x4& getPhysicTransform()          const { return _transform; }

    //!
    //! Physic pre transform getter
    //!
    virtual const QMatrix4x4& getPhysicPreTransform()       const { return _preTransform; }

    //!
    //! Physic post transform getter
    //!
    virtual const QMatrix4x4& getPhysicPostTransform()      const { return _postTransform; }

    //!
    //! Interface to provide connected physic object blocks
    //!
    virtual const QList<QSharedPointer<PhysicBlock> >& getPhysicSlaves() const { return _physicSlaves; }


    virtual int colorize() { return 0; }

public slots:

    // ========================================================================
    // => Updaters

    virtual void updatePhysicShapeData      () { }
    virtual void updatePhysicPosition       () { }
    virtual void updatePhysicTransform      () { }
    virtual void updatePhysicPreTransform   () { }
    virtual void updatePhysicPostTransform  () { }
    virtual void updatePhysicSlaves         () { }

signals:

    //! Signal parameter changed
    //! When parameters have changed but the structure remains the same
    //!
    void blockPhysicParameterChanged();

    //! Signal shape structure changed
    //! When a modification implies a new structure computation
    //!
    void blockPhysicShapeStructureChanged();

    //! Signal connection structure changed
    //! When a modification implies a new block organisation
    //!
    void blockPhysicConnectionStructureChanged();

protected:

    //! Current model type
    ModelType   _modelType;

    //! Shape data
    ShapeData   _shapeData;

    //! Object global position
    //! (0,0,0,1) by default
    QVector4D   _position;

    //! Global transformation
    QMatrix4x4  _transform;

    //! Transformation to bring the model view in drawing position
    QMatrix4x4  _preTransform;

    //! Transformation to bring the model view in
    QMatrix4x4  _postTransform;

    //! Physic objects that are impacted by the change of this one
    QList<QSharedPointer<PhysicBlock> > _physicSlaves;

};

#endif // PHYSICBLOCK_HPP


