#ifndef COMPOSERWIDGET_HPP
#define COMPOSERWIDGET_HPP

//!
//! \file ComposerWidget.hpp
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
#include <QMenuBar>
#include <BlockMenu.hpp>
#include <QGraphicsView>
#include <GraphicsBlockScene.hpp>

class ComposerBlock;

//!
//!
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class ComposerWidget : public QWidget
{
    Q_OBJECT

public:

    //!
    //! Default constructor
    //!
    explicit ComposerWidget(ComposerBlock* parent_block, QWidget *parent = 0);

protected:

    //! Block
    //! The parent block
    ComposerBlock* _block;

    //! Menu block
    //!
    QMenuBar _menuBar;

    //! Menu Block
    //! Display dragable block elements
    BlockMenu _menuBlock;

    //! View
    //!
    QGraphicsView _view;

    //! Scene
    //!
    GraphicsBlockScene _scene;


    //! FROM QWidget
    void wheelEvent(QWheelEvent* event);


};

#endif // COMPOSERWIDGET_HPP
