#include "GraphicsBlockItem.hpp"

#include <QPen>
#include <QDrag>
#include <QCursor>
#include <QMimeData>
#include <QMapIterator>
#include <ComposerStyle.hpp>
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
    setHandlesChildEvents(false);
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
    
    const QSize hsize(16,16);
    const int w2 = (blockSize().width() /2);
    const int h2 = (blockSize().height()/2);

    // 
    _corner = QPointF( - w2 , - h2 );

    //
    QPointF corner = QPointF( - w2 - hsize.width() , - h2 - hsize.height() );
    _extCorner     = QPointF( - w2 - hsize.width() , - h2 - hsize.height() );

    // local size
    QSizeF  size(blockSize());
    size += (hsize*2);

    //
    _brect  = QRectF(corner, size);

    //_topTextZone = QRectF( _corner , QSize() );

    // Handler rectangles
    _cHandler[BICornerTopLeft]  = QRectF( QPointF( _brect.center().x() - w2 - hsize.width() , _brect.center().y() - h2 - hsize.height() ) , hsize);
    _cHandler[BICornerBotLeft]  = QRectF( QPointF( _brect.center().x() - w2 - hsize.width() , _brect.center().y() + h2                  ) , hsize);
    _cHandler[BICornerBotRight] = QRectF( QPointF( _brect.center().x() + w2                 , _brect.center().y() + h2                  ) , hsize);
    _cHandler[BICornerTopRight] = QRectF( QPointF( _brect.center().x() + w2                 , _brect.center().y() - h2 - hsize.height() ) , hsize);
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
                painter->drawRect ( c.value() );
            }
        }

        // The body is always the same
        pen.setStyle     ( Qt::NoPen     );
        pen.setWidth     ( 4             );
        painter->setPen  ( pen           );
        painter->setBrush( Qt::SolidPattern   );
        painter->setBrush( QBrush(QColor( COMPOSER_BACKGROUND_LIGHT_1_COLOR )) );
        painter->drawRoundedRect( QRectF(_corner, blockSize()), 10, 10 );

        // Write the block name
        QFont font( "Roboto" );
        font.setBold ( true );
        font.setPixelSize(20);
        painter->setFont(font);
        pen.setStyle( Qt::SolidLine     );
        pen.setColor( QColor("#424242") );
        painter->setPen(pen);
        painter->drawText(QRectF( _corner + QPointF(5,5) , blockSize()), Qt::AlignLeft | Qt::AlignTop, blockName());
    }

    // === No Childs ===

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
                painter->drawRect ( c.value() );
            }

            // Draw the circle
            painter->setBrush( Qt::SolidPattern   );
            painter->setBrush( QBrush(QColor( _mainColor )) );
            painter->drawEllipse( QRectF(_corner, blockSize()) );

            // Write the block name
            QFont font( "Roboto" );
            font.setBold  ( true );
            font.setPixelSize (14);
            painter->setFont(font);
            pen.setStyle( Qt::SolidLine     );
            pen.setColor( QColor("#FFFFFF") );
            painter->setPen(pen);
            painter->drawText(QRectF(_corner, blockSize()), Qt::AlignCenter, blockName());
        }
        else
        {
            // Draw the circle
            pen.setStyle     ( Qt::SolidLine );
            pen.setColor     ( _mainColor    );
            pen.setWidth     ( 4             );
            painter->setPen  ( pen           );
            painter->setBrush( Qt::SolidPattern   );
            painter->setBrush( QBrush("#FFFFFF")  );
            painter->drawEllipse( QRectF(_corner, blockSize()) );

            // Write the block name
            QFont font( "Roboto" );
            font.setBold ( true  );
            font.setPixelSize (14);
            pen.setStyle ( Qt::SolidLine      );
            pen.setColor ( QColor("#424242")  );
            painter->setPen ( pen  );
            painter->setFont( font );
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

        default: break;
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

        default: break;
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

        default: break;
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
                if( !hasChilds() )
                {
                    if( new_size.width() > new_size.height() )
                    {
                        new_size.setWidth ( new_size.height() );
                    }
                    else
                    {
                        new_size.setHeight( new_size.width() );
                    }
                }
                setBlockSize( new_size );
            }
            else
            {
                QGraphicsItemGroup::mouseMoveEvent(event);        
            }
        }
        
        default: break;
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

        case BlockViewMode::BSM_Spy:
        {
            emit( requestBlockSpy(this) );
        }

        default: break;
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

        default: break;
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
    // If has text -> block creation
    if( event->mimeData()->hasText() )
    {
        // Get the requested block name
        QString type = event->mimeData()->text();

        // Request the block creation
        emit requestBlockCreation(this, event->pos(), type);

        // Accept the drop
        event->setAccepted(true);
    }
}

