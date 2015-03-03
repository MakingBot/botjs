#include "GraphicsBlockItem.hpp"

#include <QPen>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>

#include <iostream>
using namespace std;


const QColor GraphicsBlockItem::BorderColor1 = QColor("#666666");

const QColor GraphicsBlockItem::BorderColor2 = QColor("#666666");

const QColor GraphicsBlockItem::TextColor    = QColor("#000000");



/* ============================================================================
 *
 * */
GraphicsBlockItem::GraphicsBlockItem( )
    : QGraphicsItemGroup(),
      _hover(false)
    , _dragOver(false)
    , _blockSize(100,100)
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);

    setFlag(ItemIsMovable);
   Q_ASSERT(flags() & ItemIsMovable); // fails
   setFlag(ItemIsSelectable);
   setFlag(ItemSendsGeometryChanges);

    _mainColor.setHsv(40, 89, 242);

    setZValue(10);

}

/* ============================================================================
 *
 * */
QRectF GraphicsBlockItem::boundingRect() const
{
    //const QPointF point = QPointF( this->pos().x()- (_blockSize.width()/2) , this->pos().y()  - (_blockSize.height()/2) );
    const QPointF point = QPointF( - (_blockSize.width()/2) ,    - (_blockSize.height()/2) );
    return QRectF(point, _blockSize);
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Get pen
    QPen pen = painter->pen();

    // Common const values
    const QPointF point = QPointF( -( _blockSize.width()/2), -(_blockSize.height()/2) );
    const QRectF  rect(point, _blockSize);

    QPointF point2 = QPointF( -( _blockSize.width()/2), -(_blockSize.height()/2) + 20 );
    QSizeF  size2 = _blockSize;
    size2.setHeight( size2.height() - 20 );
    const QRectF  rect2(point2, size2);


    // Select the painting style
    if( hasChilds() )
    {
        // Draw rectangle
        pen.setStyle(Qt::NoPen);
       // pen.setColor( QColor("#FFFFFF") );
       // pen.setWidth( pen.width()*2 );
        painter->setPen(pen);
        painter->setBrush(QColor("#FFFFFF"));
        painter->drawRect(rect);

         pen.setStyle(Qt::SolidLine);

//        if(_hover)
//        {



//        }
//        else
//        {

            // Draw rectangle
            pen.setColor( BorderColor1 );
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor("#FFFFFF")));
            painter->drawRect(rect2);

            // Draw text
            QFont font( "Roboto" );
            font.setBold(true);
            font.setPixelSize(16);
            painter->setFont(font);
            pen.setColor( TextColor );
            painter->setPen(pen);
            painter->drawText(rect, Qt::AlignLeft,  blockName());
       // }
    }
    else
    {
        if(_hover)
        {
            // Draw rectangle
            pen.setColor( BorderColor2 );
            pen.setWidth( pen.width()*2 );
            painter->setPen(pen);
            painter->setBrush(QBrush(_mainColor));
            painter->drawRect(rect);

            // Draw text
            QFont font( "Roboto" );
            font.setPixelSize(16);
            painter->setFont(font);
            pen.setColor( TextColor );
            painter->setPen(pen);
            painter->drawText(rect, Qt::AlignCenter, blockName());
        }
        else
        {
            // Draw rectangle
            pen.setColor( BorderColor1 );
            painter->setPen(pen);
            painter->setBrush(QBrush(_mainColor));
            painter->drawRect(rect);

            // Draw text
            QFont font( "Roboto" );
            font.setPixelSize(16);
            painter->setFont(font);
            pen.setColor( TextColor );
            painter->setPen(pen);
            painter->drawText(rect, Qt::AlignCenter, blockName());
        }
    }





    /*
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen);
*/

/*
    this->pos()


    QSizeF  colorbox_size(20, _blockSize.height());
    QSizeF  infobox_size(_blockSize.width()-20 , _blockSize.height());
    QPointF infobox_leftop(_BlockTopLeft.x()+20, _BlockTopLeft.y()  );

    if(_hover)
    {
        painter->setBrush(QBrush(QColor("#388E3C")));
    }
    else
    {
        painter->setBrush(QBrush(QColor("#4CAF50")));
    }
    painter->drawRect(QRectF(_BlockTopLeft, colorbox_size));


    painter->setBrush(QBrush(QColor("#FFFFFF")));
    painter->drawRect(QRectF(infobox_leftop, infobox_size));
*/

}


/* ============================================================================
 *
 * */
void GraphicsBlockItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        _dragOver = true;
        update();
    }
    else
    {
        event->setAccepted(false);
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{

    cout << "block : " << event->mimeData()->text().toStdString() << endl;
}

