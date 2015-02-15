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

#include <BotBlock.hpp>

#include <QMap>
#include <QMatrix4x4>

//!
//! The physic block is an interface for blocks with a physic reality.
//! For example, they have a mass and a solid shape. They can be rendered in an 3D environment.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class PhysicBlock : public BotBlock
{
    Q_OBJECT
    Q_ENUMS(ShapeType)
    Q_ENUMS(ModelType)
    
public:

    // ========================================================================
    // => Global

    //! Define shape types
    enum ShapeType { ShapeTypeNone, ShapeTypeBox, ShapeTypeSphere, ShapeTypeCylender, ShapeTypeArrow };

    //! Define model types
    enum ModelType { ModelTypeBase, ModelTypeKinematic };
  
    //!
    //! Default constructor
    //!
    explicit PhysicBlock(const QString& name = QString(), QObject *parent = 0)
        : BotBlock(name, parent)
    { }

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockData; }

    // ========================================================================
    // => Interface definition

    //!
    //! Interface to get the shape of the object in function of the model
    //!
    virtual ShapeType getShapeType(ModelType model) { return ShapeTypeNone; }


    //const QList<QSharedPointer>

protected:


};

#endif // PHYSICBLOCK_HPP
