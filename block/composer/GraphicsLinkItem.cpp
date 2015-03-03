#include "GraphicsLinkItem.hpp"

GraphicsLinkItem::GraphicsLinkItem( QWeakPointer<GraphicsBlockItem> b1, QWeakPointer<GraphicsBlockItem> b2 )
    : QGraphicsItem()
    , _b1(b1)
    , _b2(b2)
{


}

/* ============================================================================
 *
 * */
QRectF GraphicsLinkItem::boundingRect() const
{
    QSharedPointer<GraphicsBlockItem> block1 = _b1.toStrongRef();
    QSharedPointer<GraphicsBlockItem> block2 = _b2.toStrongRef();

    int x;
    if( block1->pos().x() < block2->pos().x() )
    {
        x = block1->pos().x();
    }
    else
    {
        x = block2->pos().x();
    }

    int y;
    if( block1->pos().y() > block2->pos().y() )
    {
        y = block1->pos().y();
    }
    else
    {
        y = block2->pos().y();
    }

    int width  = qAbs<int>( block1->pos().x() - block2->pos().x() );
    int height = qAbs<int>( block1->pos().y() - block2->pos().y() );

    const QPointF point = QPointF( x, y );

   // _boundRect = QRectF(point, QSize(width, height));

   //prepareGeometryChange();


    return QRectF(point, QSize(width, height));
}

/* ============================================================================
 *
 * *
void GraphicsLinkItem::updateGeom()
{
    QSharedPointer<GraphicsBlockItem> block1 = _b1.toStrongRef();
    QSharedPointer<GraphicsBlockItem> block2 = _b2.toStrongRef();

    int x;
    if( block1->pos().x() < block2->pos().x() )
    {
        x = block1->pos().x();
    }
    else
    {
        x = block2->pos().x();
    }

    int y;
    if( block1->pos().y() > block2->pos().y() )
    {
        y = block1->pos().y();
    }
    else
    {
        y = block2->pos().y();
    }

    int width  = qAbs<int>( block1->pos().x() - block2->pos().x() );
    int height = qAbs<int>( block1->pos().y() - block2->pos().y() );

    const QPointF point = QPointF( x, y );

    _boundRect = QRectF(point, QSize(width, height));

 //  this->prepareGeometryChange();


}
*/



/* ============================================================================
 *
 * */
void GraphicsLinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QSharedPointer<GraphicsBlockItem> block1 = _b1.toStrongRef();
    QSharedPointer<GraphicsBlockItem> block2 = _b2.toStrongRef();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    painter->drawLine ( block1->pos(),  block2->pos() );
}

/* ============================================================================
 *
 * */
void GraphicsLinkItem::updateGeom()
{
    QSharedPointer<GraphicsBlockItem> block1 = _b1.toStrongRef();
    QSharedPointer<GraphicsBlockItem> block2 = _b2.toStrongRef();

    int x;
    if( block1->pos().x() < block2->pos().x() )
    {
        x = block1->pos().x();
    }
    else
    {
        x = block2->pos().x();
    }

    int y;
    if( block1->pos().y() > block2->pos().y() )
    {
        y = block1->pos().y();
    }
    else
    {
        y = block2->pos().y();
    }

    int width  = qAbs<int>( block1->pos().x() - block2->pos().x() );
    int height = qAbs<int>( block1->pos().y() - block2->pos().y() );

    const QPointF point = QPointF( x, y );

    _boundRect = QRectF(point, QSize(width, height));

    this->prepareGeometryChange();


}
