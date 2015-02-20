#ifndef VIEWER3DBLOCK_HPP
#define VIEWER3DBLOCK_HPP
//!
//! \file Viewer3DBlock.hpp
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

#include <QtGlobal>
#include <Viewer.hpp>
#include <GuiBlock.hpp>
#include <PhysicBlock.hpp>

class RobotBlock;

//!
//! Wrap functions for the robot viewer 3D
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Viewer3DBlock : public GuiBlock
{
    Q_OBJECT

    // Q_PROPERTY(int  vboUsedSize        READ vboUsedSize        WRITE setVboUsedSize        MEMBER _vboUsedSize        )
    // Q_PROPERTY(int  nbOfRenderedObject READ nbOfRenderedObject WRITE setNbOfRenderedObject MEMBER _nbOfRenderedObject )

    //Q_PROPERTY(PhysicBlock::ModelType model READ model WRITE setModel MEMBER _model)

public:
    //!
    //! Default constructor
    //!
    explicit Viewer3DBlock(const QString& name = QString("viewer3d"), QObject *parent = 0);

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }
    
    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockUi; }
    
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("viewer3d"); }


    // ========================================================================
    // => vbo used size

    //! Vbo used size getter
    int vboUsedSize() { return _vboUsedSize; }

    //! Vbo used size setter
    void setVboUsedSize(int size) { _vboUsedSize = size; emit blockiPropertyValuesChanged(); }

    // ========================================================================
    // => number of rendere object

    //! The number of object rendered by the viewer getter
    int nbOfRenderedObject() { return _nbOfRenderedObject; }

    //! The number of object rendered by the viewer setter
    void setNbOfRenderedObject(int nb) { _nbOfRenderedObject = nb; emit blockiPropertyValuesChanged(); }

    // ========================================================================
    // => Property model

    //! Current model getter 
    PhysicBlock::ModelType model() { return _model; }

    //! Set the current model
    void setModel(PhysicBlock::ModelType model) { _model = model; emit blockiPropertyValuesChanged(); }

    // ========================================================================
    // => background color

    //! Background color getter
    const QVector3D& bgColor() const { return _bgColor; }

    //! Background color setter
    void setBgColor(const QVector3D& vec) { _bgColor = vec; emit blockiPropertyValuesChanged(); }

    // ========================================================================
    // => Robot property

    //! Weak pointer on object getter
    QWeakPointer<PhysicBlock> weakObject() { return _object; }

    //! Shared pointer on the object getter
    QSharedPointer<PhysicBlock> sharedObject()
    { if(_object) return _object.toStrongRef(); else return QSharedPointer<PhysicBlock>(0); }

signals:


public slots:

    // ========================================================================
    // => BotBlock redefinition

    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnect(BotBlock* block, bool master=true);

    //! FROM BotBlock
    virtual void disconnectAll();

protected:

    // ========================================================================
    // => properties


    //! The size used by buffers in octet
    int _vboUsedSize;

    //! The number of object rendered by the viewer
    int _nbOfRenderedObject;

    //! Define the model that must be rendered
    PhysicBlock::ModelType _model;

    //! Background color
    QVector3D _bgColor;

    //! Object that must be rendered
    QWeakPointer<PhysicBlock> _object;

};


#endif // VIEWER3DBLOCK_HPP

