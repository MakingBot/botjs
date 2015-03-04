//!
//! \file ComposerWidget.cpp
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

#include <QGridLayout>
#include <QWheelEvent>
#include <ComposerWidget.hpp>
#include <ComposerBlock.hpp>



/* ============================================================================
 *
 * */
ComposerWidget::ComposerWidget(ComposerBlock* parent_block, QWidget *parent)
    : QWidget(parent), _block(parent_block)
{
    // Window configuration
    setWindowTitle("Composer");

    setMinimumSize(800, 600);

    // Layout
    QGridLayout* lay = new QGridLayout(this);
    lay->setSpacing(0);
    lay->setContentsMargins(0,0,0,0);

    lay->addWidget(&_menuBar  , 0, 0, 1, 2);
    lay->addWidget(&_menuBlock, 1, 0);
    lay->addWidget(&_view     , 1, 1);

    _menuBar.addAction ( "Bim une action" );


    _scene.initialize();

    // Set view properties
    _view.setScene(&_scene);
    _view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

}



/* ============================================================================
 *
 * */
void ComposerWidget::wheelEvent(QWheelEvent* event)
{
    _view.setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0)
    {
        // Zoom in
        _view.scale(scaleFactor, scaleFactor);
    }
    else
    {
        // Zooming out
        _view.scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}