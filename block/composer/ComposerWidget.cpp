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

#include <QPixmap>
#include <QGridLayout>
#include <QWheelEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSvgRenderer>
#include <ComposerWidget.hpp>
#include <ComposerBlock.hpp>

/* ============================================================================
 *
 * */
ComposerWidget::ComposerWidget(ComposerBlock* parent_block, QWidget *parent)
    : QWidget(parent), _block(parent_block), _view(this), _scene(this)
{
    // Window configuration
    setWindowTitle("Composer");
    setMinimumSize(1024 , 800);

    // Layout
    QGridLayout* lay = new QGridLayout(this);
    lay->setSpacing(0);
    lay->setContentsMargins(0,0,0,0);

    lay->addWidget(&_menuBar  , 0, 0, 1, 2);
    lay->addWidget(&_menuBlock, 1, 0);
    lay->addWidget(&_view     , 1, 1);

    // Set view properties
    _view.setScene(&_scene);
    _view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

    // Initialize cursors
    _cursorConnect  = InitializeSvgCusor(":/icon/plug");
    _cursorKill     = InitializeSvgCusor(":/icon/skull");
    _cursorZoom     = InitializeSvgCusor(":/icon/magnifier");

    // Build the menu bar with buttons
    QHBoxLayout* hlayout = new QHBoxLayout(&_menuBar);

    // Dev button
    QPushButton* updateDevCfg = new QPushButton(tr("Update Dev"));
    connect(updateDevCfg, &QPushButton::clicked, 
        [=](bool checked) {
            BotBlock::JsEngine.updateDevCfg();
        }
    );
    hlayout->addWidget(updateDevCfg);

    // Bot button
    QPushButton* updateBotCfg = new QPushButton(tr("Update Bot"));
    connect(updateBotCfg, &QPushButton::clicked, 
        [=](bool checked) {
            BotBlock::JsEngine.updateBotCfg();
        }
    );
    hlayout->addWidget(updateBotCfg);

    // Reset the all
    reset();
}

/* ============================================================================
 *
 * */
void ComposerWidget::reset()
{
    _scene.reset();
}

/* ============================================================================
 *
 * */
QCursor ComposerWidget::InitializeSvgCusor(const QString& filename)
{
    const unsigned int i = 20;

    // Create the image and the renderer
    QSvgRenderer svgRender( filename );
    QImage image(i, i, QImage::Format_ARGB32);

    // Get QPainter that paints to the image
    QPainter painter(&image);
    svgRender.render(&painter);

    // Cursor
    return QCursor( QPixmap::fromImage( image ) );
}

/* ============================================================================
 *
 * */
void ComposerWidget::wheelEvent(QWheelEvent* event)
{
    switch( _view.mode() )
    {
        case BlockViewMode::BSM_Editor  : break;

        case BlockViewMode::BSM_Zoom    :
        {
            // Define transformatio anchor
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
            break;
        }

        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void ComposerWidget::closeEvent(QCloseEvent* event)
{
    if(_block)
    {
        // Hide instead of close
        _block->hide();
        
        // Ignore
        event->ignore();
    }
}

/* ============================================================================
 *
 * */
void ComposerWidget::keyPressEvent(QKeyEvent* event)
{
    //std::cout << event->key() << std::endl;
    switch(event->key())
    {
        case Qt::Key_Control :
            setCursor(_cursorZoom);
            _view.setMode( BlockViewMode::BSM_Zoom );
            break;

        case Qt::Key_Shift :
            setCursor(Qt::SizeAllCursor);
            _view.setMode( BlockViewMode::BSM_Move );
            break;

        case Qt::Key_D :
            setCursor(_cursorKill);
            _view.setMode( BlockViewMode::BSM_Kill );
            break;

        case Qt::Key_C :
            setCursor(_cursorConnect);
            _view.setMode( BlockViewMode::BSM_Connect );
            break;
    }
}

/* ============================================================================
 *
 * */
void ComposerWidget::keyReleaseEvent(QKeyEvent* event)
{
    setCursor(Qt::ArrowCursor);
    _view.setMode( BlockViewMode::BSM_Editor );
}
