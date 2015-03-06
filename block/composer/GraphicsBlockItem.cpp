#include "GraphicsBlockItem.hpp"

#include <QPen>
#include <QDrag>
#include <QCursor>
#include <QMimeData>
#include <QMapIterator>
#include <GraphicsBlockScene.hpp>
#include <QGraphicsSceneDragDropEvent>

#include <iostream>
using namespace std;



/* ============================================================================
 *
 * */
GraphicsBlockItem::GraphicsBlockItem(QSharedPointer<BotBlock> block, QGraphicsItem* parent)
    : QObject(), QGraphicsItemGroup(parent)
    , _hover(false) , _dragOver(false)
    , _block(block)
{
    // Configure events
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    // Define flags
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    // Define the position
    setPos(block->blockPosition());

    // Initialize block main color
    _mainColor = QColor( BotBlock::BlockRoleToColor(block->blockRole()) );

    // Compute geometry
    computeGeometry();
}

/* ============================================================================
 *
 * */
QRectF GraphicsBlockItem::boundingRect() const
{
    return _brect;
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Activate antialiasing
    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);

    // Paint the structure
    paintStructure(painter);
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::computeGeometry()
{
    prepareGeometryChange();
    
    const int margin = 32;
    const QSize hsize(16,16);
    const int w2 = (blockSize().width() /2);
    const int h2 = (blockSize().height()/2);

    //
    _corner = QPointF( - w2 , - h2 );

    //
    QPointF corner = QPointF( - w2 - hsize.width() - margin , - h2 - hsize.height() - margin );
    _extCorner     = QPointF( - w2 - hsize.width()          , - h2 - hsize.height()          );

    // local size
    QSizeF  size(blockSize());
    size += (hsize*2);
    size += QSize(margin,margin)*2;

    //
    _brect  = QRectF(corner, size);

    // Handler rectangles
    // _cHandler[BICornerTopLeft]  = QRectF( QPointF( _brect.center().x() - w2 - hsize.width() , _brect.center().y() - h2 - hsize.height() ) , hsize);
    _cHandler[BICornerBotLeft]  = QRectF( QPointF( _brect.center().x() - w2 - hsize.width() , _brect.center().y() + h2                  ) , hsize);
    // _cHandler[BICornerBotRight] = QRectF( QPointF( _brect.center().x() + w2                 , _brect.center().y() + h2                  ) , hsize);
    _cHandler[BICornerTopRight] = QRectF( QPointF( _brect.center().x() + w2                 , _brect.center().y() - h2 - hsize.height() ) , hsize);

    //
    _topTextZone = QRectF( corner, QSize(size.width(),margin) );
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::paintStructure(QPainter* painter)
{
    // Get pen
    QPen pen = painter->pen();

    // ==========================================
    if( hasChilds() )
    {

        if( isSelected() )
        {
            // Draw corners if the item is selected
            pen.setStyle     ( Qt::NoPen        );
            painter->setPen  ( pen              );
            painter->setBrush( Qt::SolidPattern );
            painter->setBrush(QBrush(QColor("#C62828")));
            QMapIterator<BlockItemCorner, QRectF> c(_cHandler);
            while(c.hasNext())
            {
                c.next();
                if( c.key() == BICornerTopLeft )
                {
                    continue;
                }
                painter->drawRect ( c.value() );
            }
        }

        // The body is always the same
        pen.setStyle     ( Qt::SolidLine );
        pen.setColor     ( _mainColor    );
        pen.setWidth     ( 4             );
        painter->setPen  ( pen           );
        painter->setBrush( Qt::SolidPattern   );
        painter->setBrush( QBrush(QColor( "#efefef" )) );

        QVector<QPointF> point_chain;
        point_chain << _brect.center();
        point_chain << _extCorner;
        point_chain << QPointF(_brect.x(), _extCorner.y());
        QPolygonF line( point_chain );

        painter->drawPolyline( line );

        painter->drawRoundedRect( QRectF(_corner, blockSize()), 30, 30 );

        // Write the block name
        QFont font( "Roboto" );
        font.setBold ( true );
        font.setPixelSize(20);
        painter->setFont(font);
        pen.setColor( QColor("#000000") );
        painter->setPen(pen);
        painter->drawText(_topTextZone, Qt::AlignLeft, blockName());

    }

    // ==========================================
    else
    {

        if( isSelected() )
        {
            // Draw corners if the item is selected
            pen.setStyle     ( Qt::NoPen        );
            painter->setPen  ( pen              );
            painter->setBrush( Qt::SolidPattern );
            painter->setBrush(QBrush(QColor("#C62828")));
            QMapIterator<BlockItemCorner, QRectF> c(_cHandler);
            while(c.hasNext())
            {
                c.next();
                if( c.key() == BICornerTopLeft )
                {
                    continue;
                }
                painter->drawRect ( c.value() );
            }

            pen.setStyle     ( Qt::SolidLine );
            pen.setColor     ( _mainColor    );
            pen.setWidth     ( 4             );
            painter->setPen  ( pen           );

            painter->setBrush( Qt::SolidPattern   );
            painter->setBrush( QBrush(QColor( "#efefef" )) );

            QVector<QPointF> point_chain;
            point_chain << _brect.center();
            point_chain << _extCorner;
            point_chain << QPointF(_brect.x(), _extCorner.y());
            QPolygonF line( point_chain );

            painter->drawPolyline( line );

            painter->drawEllipse ( QRectF(_corner, blockSize()) );

            // Write the block name
            QFont font( "Roboto" );
            font.setBold ( true );
            font.setPixelSize(20);
            painter->setFont(font);
            pen.setColor( QColor("#000000") );
            painter->setPen(pen);
            painter->drawText(_topTextZone, Qt::AlignLeft, blockName());

        }
        else
        {


            pen.setStyle     ( Qt::NoPen        );
            painter->setPen  ( pen              );

            painter->setBrush( Qt::SolidPattern   );
            painter->setBrush( QBrush(_mainColor) );
            painter->drawEllipse ( QRectF(_corner, blockSize()) );

            // Write the block name
            QFont font( "Roboto" );
            font.setBold ( false );
            font.setPixelSize(20);
            painter->setFont(font);

            pen.setStyle     ( Qt::SolidLine );
            pen.setColor( QColor("#FFFFFF") );
            painter->setPen(pen);
            painter->drawText(QRectF(_corner, blockSize()), Qt::AlignCenter, blockName());

        }

        

    }
}

/* ============================================================================
 *
 * */
BlockViewMode GraphicsBlockItem::bSceneMode()
{
    return bScene()->mode();
}

/* ============================================================================
 *
 * */
GraphicsBlockScene* GraphicsBlockItem::bScene()
{
    return qobject_cast<GraphicsBlockScene*>(scene());
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
            // Set a flag
            _hover = true;
            // Change cursor
            bScene()->setCursor(QCursor(Qt::OpenHandCursor));
            // refresh view
            update();
            break;

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
            // Set a flag
            _hover = false;
            // Change cursor
            bScene()->setCursor(QCursor(Qt::ArrowCursor));
            // refresh view
            update();
            break;

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{   
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
        {
            QMapIterator<BlockItemCorner, QRectF> c(_cHandler);
            while(c.hasNext())
            {
                c.next();
                if( c.value().contains(event->pos()) )
                {
                    // Change cursor
                    bScene()->setCursor(QCursor(Qt::SizeBDiagCursor));
                }
            }
        }

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
        {
            if( _resizeMode )
            {
                QSize new_size = blockSize();
                QPointF diff = event->scenePos() - event->lastScenePos();
                diff *= 2;
                if( !hasChilds() )
                {
                    if( diff.x() > diff.y() )
                    {
                        diff.setY( diff.x() );
                    }
                    else
                    {
                        diff.setX( diff.y() );
                    }
                }
                switch(_resizeCorner)
                {
                    case BICornerTopLeft:
                        break;

                    case BICornerBotLeft:
                        new_size += QSize( -diff.x() ,  diff.y() );
                        break;
                    
                    case BICornerBotRight:
                        break;

                    case BICornerTopRight:
                        new_size += QSize( diff.x() , -diff.y() );
                        break;
                }
                setBlockSize( new_size );
            }
            else
            {
                QGraphicsItemGroup::mouseMoveEvent(event);        
            }
        }

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
        {
            QMapIterator<BlockItemCorner, QRectF> c(_cHandler);
            while(c.hasNext())
            {
                c.next();
                if( c.value().contains(event->pos()) )
                {
                    _resizeMode = true;
                    _resizeCorner = c.key();
                }
            }
            if( !_resizeMode )
            {
                bScene()->setCursor(QCursor(Qt::ClosedHandCursor));
                QGraphicsItemGroup::mousePressEvent(event); 
            }
            break;
        }

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::mouseReleaseEvent( QGraphicsSceneMouseEvent* event)
{
    switch( bSceneMode() )
    {
        case BlockViewMode::BSM_Editor:
        {
            // If resize mode was enabled, disable it
            if( _resizeMode )
            {
                _resizeMode = false;
            }

            // Change cursor
            if( _hover )
            {
                bScene()->setCursor(QCursor(Qt::OpenHandCursor));
            }
            else
            {
                bScene()->setCursor(QCursor(Qt::ArrowCursor));
            }

            QGraphicsItemGroup::mouseReleaseEvent(event);
            break;
        }

        case BlockViewMode::BSM_Zoom    : break;
        case BlockViewMode::BSM_Move    : break;
        case BlockViewMode::BSM_Kill    : break;
        case BlockViewMode::BSM_Connect : break;
    }


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
    Q_UNUSED(event);

    _dragOver = false;

    update();
}

/* ============================================================================
 *
 * */
void GraphicsBlockItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{


    if (event->mimeData()->hasText() )
    {
            bool ok;
            event->setAccepted(true);

            // Get the requested block name
            QString requested_block_type = event->mimeData()->text();


            QPointF new_block_position = event->scenePos() - pos();



            emit requestBlockCreation(_block, new_block_position, requested_block_type);



    }


}

