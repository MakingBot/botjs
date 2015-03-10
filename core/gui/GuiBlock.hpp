#ifndef GUIBLOCK_HPP
#define GUIBLOCK_HPP
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

#include <QWidget>
#include <BotBlock.hpp>

//!
//! Gui block
//! Provide an interface for block that implement a gui.
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class GuiBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ visible WRITE setVisible MEMBER _visible)

public:

    //! Id of the visible property
    static const quint8 IdPropertyVisible;

    //!
    //! Default constructor
    //!
    explicit GuiBlock(const QString& name = QString(), QObject *parent = 0)
        : BotBlock(name, parent), _visible(false)
    {
        defineBlockIProperty(IdPropertyVisible, new IProperty("visible", IProperty::IPTypeBool, true));
    }

    //! FROM BotBlock
    virtual BlockRole blockRole() const { return BotBlock::BlockUi; }

    //!
    //! Widget visibility getter
    //!
    virtual bool visible()
    {
        return _visible;
    }
    
    //!
    //! Widget visibility setter
    //!
    virtual void setVisible(bool visible)
    {
        if(visible) show(); else hide();
    }

    //! FROM BotBlock
    virtual void jsCfgEnablePhase(CoreCfg cfg, QTextStream& stream, QString& var_name)
    {
        if( cfg == CoreCfg::CoreCfgDev )
        {
            BotBlock::jsCfgEnablePhase(cfg, stream, var_name);
            
            stream << var_name << JsIProperty("visible") << endl;
        }
    }

public slots:

    //!
    //! Widget visibility setter
    //!
    virtual void show()
    {
        _widget->show();
        _visible = true;
        emit blockiPropertyValuesChanged(IdPropertyVisible);
    }

    //!
    //! Widget visibility setter
    //!
    virtual void hide()
    {
        _widget->hide();
        _visible = false;
        emit blockiPropertyValuesChanged(IdPropertyVisible);
    }

protected:

    //! Widget visibility
    bool _visible;

    //! Pointer on the viewer widget
    QSharedPointer<QWidget> _widget;

};

#endif // GUIBLOCK_HPP
