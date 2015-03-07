#ifndef GRAPHICSBLOCKSCENE_HPP
#define GRAPHICSBLOCKSCENE_HPP
//!
//! \file GraphicsBlockScene.hpp
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
#include <BotEngine.hpp>
#include <QGraphicsScene>
#include <BlockViewMode.hpp>
#include <GraphicsBlockItem.hpp>

//!
//! The scene of blocks
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class GraphicsBlockScene : public QGraphicsScene
{
    Q_OBJECT
    
public:

    //!
    //! Default constructor
    //!
    explicit GraphicsBlockScene(QWidget* parent);

    //!
    //! Initialize the secne and place block already existing
    //!
    void initialize();

    //!
    //! Create and append an item representing the block
    //!
    void appendBlock(QSharedPointer<BotBlock> block, GraphicsBlockItem* creator = 0);


    // ========================================================================
    // => Cursor management

    //!
    //! Widget centralize cursor management
    //!
    void setCursor(const QCursor& cursor)
    {
        _wParent->setCursor(cursor);
    }

    // ========================================================================
    // => Property mode

    //!
    //! Scene mode getter
    //!
    BlockViewMode mode()
    {
        return _mode;
    }

    //!
    //! Scene mode setter 
    //!
    void setMode(BlockViewMode mode)
    {
        _mode = mode;
    }

public slots:

    void onRequestBlockCreation(GraphicsBlockItem* creator, QPointF position, QString type);


protected:

    //! Window parent
    //! The scene need a parent widget
    QWidget* _wParent;

    //! TODO correct this architecture error
    //! Mode
    //! View mode, change action of the mouse
    BlockViewMode _mode;

    //! Item map
    //! Every item is stored in a map, linked to its id number
    QMap<quint32, QSharedPointer<GraphicsBlockItem> > _itemMap;

    //! FROM QWidget
    // virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif // GRAPHICSBLOCKSCENE_HPP
