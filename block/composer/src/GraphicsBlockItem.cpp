#include <GraphicsBlockItem.hpp>

#include <QPen>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>

#warning TODO delete
#include <iostream>
using namespace std;

/* ============================================================================
 *
 * */
GraphicsBlockItem::GraphicsBlockItem(BotBlock* block)
    : _hover(false)
    , _dragOver(false)
    , _blockSize(100,100)
    , _BlockTopLeft(-50, -50)
    , _block(QPointer<BotBlock>(block)) 
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
}

/* ============================================================================
 *
 * */
QRectF GraphicsBlockItem::boundingRect() const
{
    return QRectF(_BlockTopLeft, _blockSize);
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = painter->pen();
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen); 

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

