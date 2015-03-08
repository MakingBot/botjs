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
#include <GraphicsBlockView.hpp>
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

    //!
    //! To clear the composer and load the current architecture
    //!
    void reset();

protected:

    //! Block
    //! The parent block
    ComposerBlock*      _block;

    //! Menu block
    //!
    QWidget             _menuBar;

    //! Menu Block
    //! Display dragable block elements
    BlockMenu           _menuBlock;

    //! View
    //! One view on the scene
    GraphicsBlockView   _view;

    //! Scene
    //! The graphic scene, where items are displayed
    GraphicsBlockScene  _scene;

    //! Cursor
    QCursor             _cursorZoom;

    //! Cursor
    QCursor             _cursorKill;

    //! Cursor
    QCursor             _cursorConnect;

    //!
    //! This function initialize a cursor with a svg cursor
    //!
    static QCursor InitializeSvgCusor(const QString& filename);

    //! FROM QWidget
    void wheelEvent(QWheelEvent* event);

    //! FROM QWidget
    void closeEvent(QCloseEvent* event);

    //! FROM QWidget
    void keyPressEvent(QKeyEvent* event);
    
    //! FROM QWidget
    void keyReleaseEvent(QKeyEvent* event);

};

#endif // COMPOSERWIDGET_HPP
