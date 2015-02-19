#include <SpyWidgetFooter.hpp>
#include <SpyBlock.hpp>

#include <QHBoxLayout>

/* ============================================================================
 *
 * */
SpyWidgetFooter::SpyWidgetFooter(QWeakPointer<SpyBlock> spy_block, QWidget *parent)
    : QWidget(parent)
    , _buttonKill  (QIcon(":/icon/skull"), "")
    , _buttonCreate(QIcon(":/icon/plus" ), "")
    , _spyblock(spy_block)
{
    const QSize button_size(32,32);

    // Configure buttons
    _buttonKill.setFlat(true);
    _buttonCreate.setFlat(true);

    _buttonKill.setIconSize(button_size);
    _buttonKill.setMinimumSize(button_size);
    _buttonKill.setMaximumSize(button_size);

    _buttonCreate.setIconSize(QSize(25,25));
    _buttonCreate.setMinimumSize(button_size);
    _buttonCreate.setMaximumSize(button_size);

    // Connect buttons
    connect(&_buttonKill  , SIGNAL(clicked()), this, SLOT(killSpiedBlock())       );
    connect(&_buttonCreate, SIGNAL(clicked()), this, SLOT(createSonOfSpiedBlock()));

    // Create layout
    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(&_cbSpiedBlock);
    lay->addWidget(&_buttonCreate);
    lay->addWidget(&_buttonKill);

    // First update
    onSpiedBlockChange();
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::onSpiedBlockChange()
{
    updateStructure();
    updateValues();
}


/* ============================================================================
 *
 * */
void SpyWidgetFooter::updateValues()
{
    // Check the spied block
    QSharedPointer<BotBlock> spied = getSharedSpyBlock()->getSharedSpiedBlock();
    if(!spied) { return; }

    // Get block father chain
    QString chain = spied->getBlockFathersChain();

    // Comboboc to this item
    _cbSpiedBlock.setCurrentIndex( _cbSpiedBlock.findText(chain) );
    _currentValidSelection = _cbSpiedBlock.currentIndex();
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::updateStructure()
{
    // Disconnect
    disconnect( &_cbSpiedBlock, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onCBSpiedChange(const QString&)) );

    // Get chains
    QStringList chains = BotBlock::JsEngine.getAllFatherChains();

    // Clear combobox
    _cbSpiedBlock.clear();

    // Fill it again
    _cbSpiedBlock.addItem ("DO NOT SPY"); 
    _cbSpiedBlock.addItems( chains );

    // Connect combobox
    connect   ( &_cbSpiedBlock, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onCBSpiedChange(const QString&)) );
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::killSpiedBlock()
{
   
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::createSonOfSpiedBlock()
{
    
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::onCBSpiedChange( const QString & chain )
{
    // Get spy
    QSharedPointer<SpyBlock> spy = getSharedSpyBlock();

    // If use want to stop spying 
    if( chain.compare("DO NOT SPY") == 0 )
    {
        // Disconnect if it were connected
        spy->disconnect(getSharedSpyBlock()->getSharedSpiedBlock().data());
        return;
    }

    // Special check if a block is already spied
    QSharedPointer<BotBlock> spied = getSharedSpyBlock()->getSharedSpiedBlock();
    if(spied)
    {
        if( spied->getBlockFathersChain().compare(chain) == 0 )
        {
            // Cannot spy if its is already spied
            spy->beglog() << "Try to spy the block that is already spied" << spy->endlog();
            return;
        }
    }

    // Get the block from its father chain
    BotBlock* block = spy->getBlockFromFathersChain( chain );

    // Try to connect to block
    if( !spy->connect(block) )
    {
        // restore if fail
        _cbSpiedBlock.setCurrentIndex(_currentValidSelection);
    }
}
