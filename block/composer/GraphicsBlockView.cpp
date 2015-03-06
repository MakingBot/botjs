//!
//! \file GraphicsBlockView.cpp
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

#include <iostream>
#include <GraphicsBlockView.hpp>

/* ============================================================================
 *
 * */
GraphicsBlockView::GraphicsBlockView(QWidget* parent)
    : QGraphicsView(parent)
{

}

/* ============================================================================
 *
 * */
void GraphicsBlockView::mouseMoveEvent(QMouseEvent* event)
{

    switch( _mode )
    {
        case BlockViewMode::BSM_Editor  : break;
        case BlockViewMode::BSM_Zoom    : break;

        case BlockViewMode::BSM_Move    :
        {
            //! Redefine a view class, it is not the place for doing that
            
            //std::cout << "icici" << std::endl;
            
            //centerOn(5,5);
            
            break;
        }

        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }

    QGraphicsView::mouseMoveEvent(event);
}


