#include <GraphicsBlockScene.hpp>

#include <QPair>
#include <QDrag>
#include <QStack>
#include <iostream>
#include <QMimeData>
#include <QLineEdit>
#include <BotBlock.hpp>
#include <QInputDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>

using namespace std;

//!
//! Helper
//!
typedef QPair<QSharedPointer<BotBlock>, GraphicsBlockItem*> PairBlockItem;

/* ============================================================================
 *
 * */
GraphicsBlockScene::GraphicsBlockScene(QWidget* parent)
    : QGraphicsScene(), _wParent(parent), _mode(BSM_Editor)
{
    // The scene must have a parent widget
    if( !_wParent )
    {
        throw std::runtime_error("No widget parent provided!");
    }

    // Set the background color
    setBackgroundBrush( QBrush(QColor( "#efefef" )) );
}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::reset()
{
    _itemMap.clear();


    initialize();
}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::onRequestBlockCreation(GraphicsBlockItem* creator, QPointF position, QString type)
{
    QSharedPointer<BotBlock> creator_block = creator->associatedBlock();

    // Get a name for the block from the user
    bool ok;
    QString block_name = QInputDialog::getText(_wParent, tr("Provide a name for the new block"), tr("Block name:"), QLineEdit::Normal, type, &ok);

    // Create the new block
    BotBlock* new_block = creator_block->create( type , block_name );

    // Set its position
    new_block->setBlockPosition( position );

    // Append the block into the scene
    appendBlock( new_block->toBlockSharedPointer(), creator );
}

/* ============================================================================
 *
 * */
void GraphicsBlockScene::initialize()
{
    // Create stack and store the core block to start
    QStack<PairBlockItem> blocks;
    blocks.push( PairBlockItem(BotBlock::JsEngine.coreBlock(), 0) );

    // Block after block
    while( !blocks.isEmpty() )
    {
        // Get the current block
        QPair<QSharedPointer<BotBlock>, GraphicsBlockItem*> block = blocks.pop();

        // Get core block pointer and append the block
        GraphicsBlockItem* item = appendBlock( block.first, block.second );

        // Add every son
        QMapIterator<QString, QSharedPointer<BotBlock> > son( block.first->blockSons() );
        while(son.hasNext())
        {
            son.next();
            blocks.push( PairBlockItem(son.value(), item) );
        }
    }
}

/* ============================================================================
 *
 * */
GraphicsBlockItem* GraphicsBlockScene::appendBlock(QSharedPointer<BotBlock> block, GraphicsBlockItem* creator)
{
    // Check input
    if( !block )
    {
        return 0;
    }

    // Create an item with the block
    QSharedPointer<GraphicsBlockItem> block_item(new GraphicsBlockItem(block, creator));

    // Save it
    _itemMap.insert(block->blockIdNumber(), block_item);

    // If no creator, Append it manually into the scene    
    if(!creator)
        addItem( block_item.data() );

    // Connection
    connect(block_item.data(), SIGNAL( requestBlockCreation  (GraphicsBlockItem*, QPointF, QString) ) ,
                         this, SLOT  ( onRequestBlockCreation(GraphicsBlockItem*, QPointF, QString) ) );

    // Return the created item
    return block_item.data();
}
