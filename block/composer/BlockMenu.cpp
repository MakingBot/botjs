#include "BlockMenu.hpp"

#include <QPainter>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QScrollBar>

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
    const int min_width = 130;
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




    for(int i = 0 ; i < 10 ; i++)
    {

        QSharedPointer<BlockMenuItem> item ( new BlockMenuItem("test", 50) );

        lay->addWidget( item.data() );

        _items << item;
    }

    setWidget( _menu.data() );

}



