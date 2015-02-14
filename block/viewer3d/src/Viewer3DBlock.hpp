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
#include <BotBlock.hpp>

class RobotBlock;

//!
//! Wrap functions for the robot viewer 3D
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Viewer3DBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(bool visible            READ visible            WRITE setVisible            MEMBER _visible           )

    Q_PROPERTY(int  vboUsedSize        READ vboUsedSize        WRITE setVboUsedSize        MEMBER _vboUsedSize        )
    Q_PROPERTY(int  nbOfRenderedObject READ nbOfRenderedObject WRITE setNbOfRenderedObject MEMBER _nbOfRenderedObject )

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
    // => visible member

    //! Widget visibility getter
    bool visible() { return _visible; }
    
    //! Widget visibility setter
    void setVisible(bool visible) { if(visible) show(); else hide(); }

    // ========================================================================
    // => vbo used size

    //! Vbo used size getter
    int vboUsedSize() { return _vboUsedSize; }

    //! Vbo used size setter
    void setVboUsedSize(int size) { _vboUsedSize = size; }

    // ========================================================================
    // => number of rendere object

    //! The number of object rendered by the viewer getter
    int nbOfRenderedObject() { return _nbOfRenderedObject; }

    //! The number of object rendered by the viewer setter
    void setNbOfRenderedObject(int nb) { _nbOfRenderedObject = nb; }

    // ========================================================================
    // => background color

    //! Background color getter
    const QVector3D& bgColor() const { return _bgColor; }

    //! Background color setter
    void setBgColor(const QVector3D& vec) { _bgColor = vec; emit blockiPropertyValuesChanged(); }

    // ========================================================================
    // => Robot property

    //! Weak pointer on robot getter
    QWeakPointer<RobotBlock> weakRobot() { return _robot; }

    //! 
    QSharedPointer<RobotBlock> sharedRobot()
    {
        if(_robot) return _robot.toStrongRef(); else return QSharedPointer<RobotBlock>(0);
    }



    // ========================================================================
    // => widget management

    //!
    //! Create the widget if it is not
    //!
    void createWidgetIfRequired()
    {
        if(!_widget)
        {
            _widget = QSharedPointer<Viewer>( new Viewer( qSharedPointerObjectCast<Viewer3DBlock, BotBlock>(this->getBlockSharedFromThis()) ) );
        }
    }

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

    // ========================================================================
    // => visible property

    //! Widget visibility setter
    virtual void show()
    {
        createWidgetIfRequired();
        _widget->show();
        _visible = true;
        emit blockiPropertyValuesChanged();
    }

    //! Widget visibility setter
    virtual void hide()
    {
        _widget->hide();
        _visible = false;
        emit blockiPropertyValuesChanged();
    }

protected:

    // ========================================================================
    // => properties

    //! Widget visibility
    bool _visible;

    //! The size used by buffers in octet
    int _vboUsedSize;

    //! The number of object rendered by the viewer
    int _nbOfRenderedObject;

    //! Background color
    QVector3D _bgColor;

    //! Connection on the robot managed by this session
    QWeakPointer<RobotBlock> _robot;

    // ========================================================================
    // => widget management

    //! Pointer on the viewer widget
    QSharedPointer<Viewer> _widget;

};


#endif // VIEWER3DBLOCK_HPP

