//!
//! \file BlockMenu.cpp
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

#include <BotBlock.hpp>
#include <BlockMenu.hpp>

#include <QPainter>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QStyleOption>

/* ============================================================================
 *
 * */
BlockMenu::BlockMenu(QWidget *parent)
    : QScrollArea(parent)
{
    // Define style
    setObjectName("BlockMenu");
    QString style = QString("QScrollArea#BlockMenu{ background-color: #FFFFFF; } "

                            );
    setStyleSheet( style );


    QScrollBar* vScrollBar = verticalScrollBar();
    vScrollBar->setStyleSheet( "QScrollBar{  "
                               "    background-color: white;"
                                "   border: 1px solid white; "
                               "}"

                               "QScrollBar::handle:vertical {"
                                  " background: #424242;"
                                  " min-height: 20px;"
                              " }"
                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                     "border: 2px solid grey;"
                                    " width: 3px;"
                                    " height: 3px;"
                                    " background: white;"
                                " }"
);

    // Set size
    const int min_width = 200;
    setMinimumWidth(min_width);
    setMaximumWidth(min_width);

    // Menu area
    _menu = QSharedPointer<QWidget>( new QWidget() );
    _menu->setObjectName("BlockMenuArea");
    style = QString("QWidget#BlockMenuArea{ background-color: #FFFFFF; }");
    _menu->setStyleSheet( style );

    // Build layout
    QVBoxLayout* lay = new QVBoxLayout( _menu.data() );
    lay->setContentsMargins(QMargins(16,16,16,16));
    lay->setSpacing(16);

    // Get available blocks
    QStringList blocknames;
    BotBlock::JsEngine.availableBlockNames(blocknames);

    // Go through blocks
    foreach(const QString& blockname, blocknames)
    {
        // Create the item
        QSharedPointer<BlockMenuItem> item ( new BlockMenuItem(blockname, 50) );

        // Append the widget in the view
        lay->addWidget( item.data() );

        // Save the pointer on this item
        _items << item;
    }

    // Give a widget for the scrollaera
    setWidget( _menu.data() );
}



