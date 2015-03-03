#ifndef GRAPHICSLINKITEM_HPP
#define GRAPHICSLINKITEM_HPP

#include "GraphicsBlockItem.hpp"


#include <QGraphicsItem>

class GraphicsLinkItem : public QGraphicsItem
{
public:
    GraphicsLinkItem( QWeakPointer<GraphicsBlockItem> b1, QWeakPointer<GraphicsBlockItem> b2 );



    //! FROM QGraphicsItem
    QRectF boundingRect() const;

    //! FROM QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Update item geometry
    void updateGeom();

protected:

    //! The bounded rectangle
    QRectF _boundRect;

    QWeakPointer<GraphicsBlockItem> _b1;

    QWeakPointer<GraphicsBlockItem> _b2;

};

#endif // GRAPHICSLINKITEM_HPP
