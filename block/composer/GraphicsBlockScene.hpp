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

#include <BotEngine.hpp>
#include <QGraphicsScene>
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
    explicit GraphicsBlockScene(QWidget* parent = 0);

    //!
    //! Initialize the secne and place block already existing
    //!
    void initialize();

protected:

    //! Window parent
    QWidget* _wParent;

    //! Item map
    //! Every item is stored in a map, linked to its id number
    QMap<quint32, QSharedPointer<GraphicsBlockItem> > _itemMap;

    //! FROM QGraphicsScene
    void dragMoveEvent (QGraphicsSceneDragDropEvent* event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsScene
    void dropEvent     (QGraphicsSceneDragDropEvent* event) Q_DECL_OVERRIDE;

};

#endif // GRAPHICSBLOCKSCENE_HPP
