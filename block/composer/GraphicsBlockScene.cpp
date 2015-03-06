#include <GraphicsBlockScene.hpp>

#include <QDrag>
#include <iostream>
#include <QMimeData>
#include <QLineEdit>
#include <BotBlock.hpp>
#include <QInputDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>

using namespace std;

/* ============================================================================
 *
 * */
GraphicsBlockScene::GraphicsBlockScene(QWidget* parent)
    : QGraphicsScene(), _wParent(parent), _mode(BSM_Editor)
{
    if( !_wParent )
    {
        throw std::runtime_error("No widget parent found!");
    }

    // Set the background color
    setBackgroundBrush( QBrush(QColor( "#efefef" )) );

}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::initialize()
{
    // Get core block pointer
    QSharedPointer<BotBlock> core = BotBlock::JsEngine.getCoreBlock();

    // Create an item with it
    QSharedPointer<GraphicsBlockItem> core_item(new GraphicsBlockItem(core));

    // Save it
    _itemMap.insert(core->blockIdNumber(), core_item);

    // Append it into the scene
    addItem( core_item.data() );

    // Connection
    connect(core_item.data(), SIGNAL( requestBlockCreation  (QSharedPointer<BotBlock>, QPointF, QString) ) ,
                        this, SLOT  ( onRequestBlockCreation(QSharedPointer<BotBlock>, QPointF, QString) ) );
}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::appendBlock(QSharedPointer<BotBlock> block)
{
    // Create an item with it
    QSharedPointer<GraphicsBlockItem> block_item(new GraphicsBlockItem(block));

    // Save it
    _itemMap.insert(block->blockIdNumber(), block_item);

    // Append it into the scene
    addItem( block_item.data() );

    // Connection
    connect(block_item.data(), SIGNAL( requestBlockCreation  (QSharedPointer<BotBlock>, QPointF, QString) ) ,
                         this, SLOT  ( onRequestBlockCreation(QSharedPointer<BotBlock>, QPointF, QString) ) );
}


/* ============================================================================
 *
 * */
void GraphicsBlockScene::onRequestBlockCreation(QSharedPointer<BotBlock> creator_block, QPointF position, QString type)
{
    bool ok;

    std::cout << "block " << position.x() << std::endl;


    // Get a name for the block from the user
    QString block_name = QInputDialog::getText(_wParent, tr("Provide a name for the new block"), tr("Block name:"), QLineEdit::Normal, type, &ok);


    BotBlock* new_block = creator_block->create( type , block_name );

    new_block->setBlockPosition( position );

    appendBlock( new_block->toBlockSharedPointer() );
}


/* ============================================================================
 *
 * */
// void GraphicsBlockScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
// {
//     switch( _mode )
//     {
//         case BlockSceneMode::BSM_Editor  : break;
//         case BlockSceneMode::BSM_Zoom    : break;

//         case BlockSceneMode::BSM_Move    :
//         {
//             //! Redefine a view class, it is not the place for doing that
            
            
//             views()[0]->translate(5,5);
            
//             break;
//         }

//         case BlockSceneMode::BSM_Kill    : break;
//         case BlockSceneMode::BSM_Connect : break;
//     }
// }

/* ============================================================================
 *
 * */
//void GraphicsBlockScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
//{
    // QPointF pp(event->scenePos());

    
    // QList<QGraphicsItem*> items = this->items( pp , Qt::IntersectsItemBoundingRect, Qt::AscendingOrder) ;


    // if (event->mimeData()->hasText() && items.size()==0)
    // {
    //     event->setAccepted(true);
    // }
    // else
    // {
    //      QGraphicsScene::dragMoveEvent(event);
    // }
//}

/* ============================================================================
 *
 * */
//void GraphicsBlockScene::dropEvent(QGraphicsSceneDragDropEvent* event)
//{
    // // Get drop point
    // QPointF dropPoint(event->scenePos());

    // // Check if items was under the mouse
    // QList<QGraphicsItem*> items = this->items(dropPoint, Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);

    // if(items.size()==0)
    // {


    //     if (event->mimeData()->hasText() )
    //     {
    //         bool ok;
    //         event->setAccepted(true);

    //         // // Get the requested block name
    //         // QString requested_block_type = event->mimeData()->text();

    //         // // Get a name for the block from the user
    //         // QString block_name = QInputDialog::getText(_wParent, tr("Provide a name for the new block"), tr("Block name:"), QLineEdit::Normal, requested_block_type, &ok);

    //         // // 
    //         // BotBlock* block_ptr = _jsEngine->createBlock(requested_block_type, block_name);


    //         // GraphicsBlockItem* new_item = new GraphicsBlockItem(block_ptr);
    //         // new_item->setFlag(QGraphicsItem::ItemIsMovable);
    //         // new_item->setPos(dropPoint);

    //         // addItem(new_item);
            
            
    //     }




    // }
    // else
    // {
    //     QGraphicsScene::dropEvent(event);
    // }


//}

