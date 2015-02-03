#include <ComposerWidget.hpp>
#include <ComposerBlock.hpp>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QCloseEvent>

/* ============================================================================
 *
 * */
ComposerWidget::ComposerWidget(QWeakPointer<ComposerBlock> composer_block, QWidget *parent)
    : QWidget(parent)
    , _composerblock(composer_block)
    , _menu    (new QWidget())
    , _menuZone(new QScrollArea())
    , _view    (new QGraphicsView())
    , _scene   (new GraphicsBlockScene(this))
{
    // Window configuration
    setWindowTitle("Block Composer");
    setMinimumSize(QSize(800, 600));

    // Create the layout
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);
    gridLayout->addWidget(_menuZone, 0, 0);
    gridLayout->addWidget(_view    , 0, 1);

    // Place the scene in the view
    _view->setScene(_scene);

    // Define scene properties
    _scene->setBackgroundBrush(QBrush(QColor("#eeeeee")));


    // MenuItem* menu = new MenuItem("spy");
    // MenuItem* menu2 = new MenuItem("robot");


    // QVBoxLayout* vLayout = new QVBoxLayout(_menu);
    // vLayout->setMargin(0);
    // vLayout->setSpacing(5);

    // vLayout->addWidget(menu);
    // vLayout->addWidget(menu2);


    // _menuZone->setMinimumWidth(100);
    // _menuZone->setMaximumWidth(100);
    // _menuZone->setWidget(_menu);

 

}


// GraphicsBlockItem* mmmm = new GraphicsBlockItem();
// _scene->addItem ( mmmm );
// mmmm->setFlag(QGraphicsItem::ItemIsMovable);
// mmmm->setPos(100,100);



/* ============================================================================
 *
 * */
void ComposerWidget::closeEvent(QCloseEvent* event)
{
    if(_composerblock)
    {
        //
        QSharedPointer<ComposerBlock> block = _composerblock.toStrongRef();
        
        //
        block->hide();
        
        //
        event->ignore();
    }
}

