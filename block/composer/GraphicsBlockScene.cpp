#include <GraphicsBlockScene.hpp>


#include <QDrag>
#include <QMimeData>
#include <QLineEdit>
#include <QInputDialog>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>



#include <iostream>

using namespace std;

/* ============================================================================
 *
 * */
GraphicsBlockScene::GraphicsBlockScene(QWidget* parent)
    : _wParent(parent)
{


}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    QPointF pp(event->scenePos());

    
    QList<QGraphicsItem*> items = this->items( pp , Qt::IntersectsItemBoundingRect, Qt::AscendingOrder) ;


    if (event->mimeData()->hasText() && items.size()==0)
    {
        event->setAccepted(true);
    }
    else
    {
         QGraphicsScene::dragMoveEvent(event);
    }
}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    // Get drop point
    QPointF dropPoint(event->scenePos());

    // Check if items was under the mouse
    QList<QGraphicsItem*> items = this->items(dropPoint, Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);

    if(items.size()==0)
    {


        if (event->mimeData()->hasText() )
        {
            bool ok;
            event->setAccepted(true);

            // // Get the requested block name
            // QString requested_block_type = event->mimeData()->text();

            // // Get a name for the block from the user
            // QString block_name = QInputDialog::getText(_wParent, tr("Provide a name for the new block"), tr("Block name:"), QLineEdit::Normal, requested_block_type, &ok);

            // // 
            // BotBlock* block_ptr = _jsEngine->createBlock(requested_block_type, block_name);


            // GraphicsBlockItem* new_item = new GraphicsBlockItem(block_ptr);
            // new_item->setFlag(QGraphicsItem::ItemIsMovable);
            // new_item->setPos(dropPoint);

            // addItem(new_item);
            
            
        }




    }
    else
    {
        QGraphicsScene::dropEvent(event);
    }


}

