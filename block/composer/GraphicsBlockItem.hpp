#ifndef GRAPHICSBLOCKITEM_H
#define GRAPHICSBLOCKITEM_H

#include <QSize>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <BotBlock.hpp>
#include <BlockViewMode.hpp>
#include <QGraphicsItemGroup>

class GraphicsLinkItem;
class GraphicsBlockScene;

//!
//! Block item
//!
class GraphicsBlockItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:

    enum BlockItemCorner { BICornerTopLeft, BICornerBotLeft, BICornerBotRight, BICornerTopRight };

    //!
    //! Default constructor
    //!
    GraphicsBlockItem(QSharedPointer<BotBlock> block, QGraphicsItem* parent = 0);

    //! FROM QGraphicsItem
    QRectF boundingRect() const;

    //! FROM QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    //!
    //! Associate block getter
    //!
    QSharedPointer<BotBlock> associatedBlock()
    {
        return _block;
    }


signals:

    //!
    //! Signal to request a block creation
    //!
    void requestBlockCreation(GraphicsBlockItem* creator, QPointF position, QString type);

    //!
    //! Signal to request to be spied
    //!
    void requestBlockSpy(GraphicsBlockItem* me);

protected:

    //! When mouse is hover
    bool _hover;

    //! When object is dragged over
    bool _dragOver;

    //! Resize mode
    //! True when the item is in resize mode
    bool _resizeMode;

    //! Resize corner
    //! Hold the corner grab by the mouse for resizing
    BlockItemCorner _resizeCorner;

    //! Color of the block role
    QColor _mainColor;

    //! Bounding rectangle
    QRectF _brect;

    //! Top left corner point of the bounding rectangle
    QPointF _corner;
    
    QPointF _extCorner;

    QRectF _topTextZone;

    //! Corner handlers
    QMap<BlockItemCorner, QRectF> _cHandler;

    //! Block
    //! Block that the item represent
    QSharedPointer<BotBlock> _block;

    //!
    QList<QWeakPointer<GraphicsLinkItem> > _links;



    //!
    //! Compute each geometric parameters
    //!
    void computeGeometry();

    //!
    //! Paint the item body
    //!
    void paintStructure(QPainter* painter);


    //!
    //! Block scene mode getter 
    //!
    BlockViewMode bSceneMode();

    //!
    //! Block scene getter
    //!
    GraphicsBlockScene* bScene();


    //!
    //! Interface
    //!
    const QString blockName() const
    {
        return _block->blockName();
    }

    //!
    //! Interface
    //!
    const QSize& blockSize() const
    {
        return _block->blockSize();
    }

    //!
    //! Interface
    //!
    void setBlockSize(const QSize& size)
    {
        _block->setBlockSize(size);
        computeGeometry();
    }

    //!
    //! Interface
    //!
    const bool hasChilds() const
    {
        return _block->blockHasSons();
    }


    //! FROM QGraphicsItem
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

    //! FROM QGraphicsItem
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    //! FROM QGraphicsItem
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

    //! FROM QGraphicsItem
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    //! FROM QGraphicsItem
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //! FROM QGraphicsItem
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    //! FROM QGraphicsItem
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsItem
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsItem
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;


};

#endif // GRAPHICSBLOCKITEM_H
