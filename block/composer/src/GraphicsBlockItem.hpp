#ifndef GRAPHICSBLOCKITEM_H
#define GRAPHICSBLOCKITEM_H

#include <QSize>
#include <QDebug>
#include <QPainter>
#include <BotBlock.hpp>
#include <QGraphicsItem>

//!
//! Block item
//!
class GraphicsBlockItem : public QGraphicsItem
{
public:
    //!
    //! Default constructor
    //!
    GraphicsBlockItem(BotBlock* block);

    //! FROM QGraphicsItem
    QRectF boundingRect() const;

    //! FROM QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //! When mouse is hover
    bool _hover;

    //! When object is dragged over
    bool _dragOver;

    //! Block size
    QSizeF _blockSize;

    //! Block top left
    QPointF _BlockTopLeft;

    //! Track the block it represents
    QPointer<BotBlock> _block;

 virtual void	hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
    {
        _hover = true;
        qDebug() << "in";
        update();
    }

    virtual void	hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
    {
        _hover = false;
         qDebug() << "out";
        update();
    }


    virtual void	mousePressEvent ( QGraphicsSceneMouseEvent * event )
    {
QGraphicsItem::mousePressEvent(event);
        qDebug() << "click";

    }

    //! FROM QGraphicsItem
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsItem
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsItem
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

};

#endif // GRAPHICSBLOCKITEM_H
