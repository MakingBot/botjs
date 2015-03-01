#include <SpyWidgetFooter.hpp>
#include <SpyBlock.hpp>

#include <QHBoxLayout>

/* ============================================================================
 *
 * */
SpyWidgetFooter::SpyWidgetFooter(SpyBlock*  spy_block, QWidget *parent)
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
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();

    // Get block father chain
    QString chain = spied->blockIdChain();

    // ComboBox to this item
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
    QStringList chains;
	BotBlock::JsEngine.allIdChains(chains);

    // Clear ComboBox
    _cbSpiedBlock.clear();

    // Fill it again
    _cbSpiedBlock.addItem ("DO NOT SPY"); 
    _cbSpiedBlock.addItems( chains );

    // Connect ComboBox
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
    // If use want to stop spying 
    if( chain.compare("DO NOT SPY") == 0 )
    {
        // Disconnect if it were connected
    	_spyblock->dco(_spyblock->weakSpiedBlock().data());
        return;
    }

    // Special check if a block is already spied
    QSharedPointer<BotBlock> spied = _spyblock->weakSpiedBlock().toStrongRef();
    if(spied)
    {
        if( spied->blockIdChain().compare(chain) == 0 )
        {
            return;
        }
    }

    // Get the block from its father chain
    QSharedPointer<BotBlock> block = _spyblock->IdChainToBlockPointer( chain );

    // Try to connect to block
    if( !_spyblock->co(block.data()) )
    {
        // restore if fail
        _cbSpiedBlock.setCurrentIndex(_currentValidSelection);
    }
}
