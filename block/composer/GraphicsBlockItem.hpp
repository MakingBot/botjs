#ifndef GRAPHICSBLOCKITEM_H
#define GRAPHICSBLOCKITEM_H

#include <QSize>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <BotBlock.hpp>
#include <QGraphicsItemGroup>

class GraphicsLinkItem;

//!
//! Block item
//!
class GraphicsBlockItem : public QGraphicsItemGroup
{

public:

    //!
    //! Default constructor
    //!
    GraphicsBlockItem(QSharedPointer<BotBlock> block, QGraphicsItem* parent = 0);

    //! FROM QGraphicsItem
    QRectF boundingRect() const;

    //! FROM QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:

    //! When mouse is hover
    bool _hover;

    //! When object is dragged over
    bool _dragOver;

    //! Color of the block role
    QColor _mainColor;


    //! Block size
    QSizeF _blockSize;


    //! Block
    //! Block that the item represent
    QSharedPointer<BotBlock> _block;




    QList<QWeakPointer<GraphicsLinkItem> > _links;


    //! Color passive border
    static const QColor BorderColor1;

    //! Color active border
    static const QColor BorderColor2;

    //! Color text
    static const QColor TextColor;


    //!
    //! Interface
    //!
    const QString blockName() const
    {
        return _block->blockName();
    }




    const bool hasChilds() const { return true; }

 virtual void	hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
    {
        _hover = true;
        update();
    }

    virtual void	hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
    {
        _hover = false;
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
