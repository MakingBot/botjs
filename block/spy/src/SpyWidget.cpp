#include <SpyWidget.hpp>
#include <SpyBlock.hpp>

#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QMapIterator>
#include <QMetaProperty>

/* ============================================================================
 *
 * */
SpyWidget::SpyWidget(QWeakPointer<SpyBlock> spy_block, QWidget* parent)
    : QWidget(parent)
    , _spyblock         (spy_block)
    , _header           (spy_block)
    , _body             (spy_block)
    , _footer           (spy_block)
{
    // Basic verification
    if(!getSharedSpyBlock()) {
        throw std::runtime_error("Spy widget has been created without a parent spy block");
    }

    // Window configuration
    setWindowTitle("SpyBlock: " + getSharedSpyBlock()->getBlockName());

    // Create layout
    new QGridLayout(this);
    ((QGridLayout*)layout())->setSpacing(0);
    ((QGridLayout*)layout())->setContentsMargins(0,0,0,0);
    
    ((QGridLayout*)layout())->addWidget(&_header, 0, 0, Qt::AlignTop);
    ((QGridLayout*)layout())->addWidget(&_body  , 1, 0);
    ((QGridLayout*)layout())->addWidget(&_footer, 2, 0, Qt::AlignBottom);
    
    // Connect update signals
    connect(getSharedSpyBlock().data(), SIGNAL(spiedBlockChanged()), this, SLOT(onSpiedBlockChange()));
}

/* ============================================================================
 *
 * */
QSharedPointer<BotBlock> SpyWidget::getSharedSpiedBlock()
{
    return getSharedSpyBlock()->getSharedSpiedBlock();
}

/* ============================================================================
 *
 * */
void SpyWidget::onSpiedBlockChange()
{
    _header.onSpiedBlockChange();
    _body  .onSpiedBlockChange();
    _footer.onSpiedBlockChange();

    // Build the new one
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {        
        // Connect events
        connect( spied.data(), SIGNAL(blockfPropertyValuesChanged  ()), &_header, SLOT(updateValues()) );   
    }
}

/* ============================================================================
 *
 * */
void SpyWidget::updateStructure()
{
    QSharedPointer<SpyBlock> block = getSharedSpyBlock();
    if(block)
    {

    }

    

    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        // Get property names
        const QStringList& property_names = spied->iProperties();
        
        // Go through properties
        foreach(const QString &property_name, property_names)
        {
            // Get the property
            QVariant property = spied->property(property_name.toStdString().c_str());

            // Get type
            _propertyMap[property_name].type = property.type();
            
            // Is the property writable
            int index = spied->metaObject()->indexOfProperty(property_name.toStdString().c_str());
            _propertyMap[property_name].isWritable = spied->metaObject()->property(index).isWritable();

            switch(_propertyMap[property_name].type)
            {
                case QVariant::String:
                    if(_propertyMap[property_name].isWritable)
                    {
                        _propertyMap[property_name].widget = new QLineEdit();
                        connect( (QLineEdit*)_propertyMap[property_name].widget, SIGNAL(textEdited(const QString&)), this, SLOT(onLineTextEdited(const QString&)) );
                    }
                    else
                    {
                        _propertyMap[property_name].widget = new QLabel();
                    }
                    break;

                case QVariant::Bool:
                    _propertyMap[property_name].widget = new QComboBox();
                    ((QComboBox*)_propertyMap[property_name].widget)->addItems( {"TRUE", "FALSE"} );
                    connect( (QComboBox*)_propertyMap[property_name].widget, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxBool(int)) );
                    break;

                // case QVariant::Vector3D:
                //     // _propertyMap[property_name].widget = new QComboBox();
                //     break;

                default:
                    _propertyMap[property_name].widget = new QLabel("Unmanaged property type");
                    break;
            }
            
            // Add it into the layout
            ((QFormLayout*)layout())->addRow(property_name, _propertyMap[property_name].widget);   
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidget::updateValues()
{
    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        // Go through properties
        QMapIterator<QString, PropertyInformation> property(_propertyMap);
        while (property.hasNext())
        {
            property.next();
            
            // Action depend on the widget
            switch(property.value().type)
            {
                case QVariant::String:
                    if(property.value().isWritable)
                    {
                        ((QLineEdit*)(property.value().widget))->setText( spied->property(property.key().toStdString().c_str()).toString() );
                    }
                    else
                    {
                        ((QLabel*)(property.value().widget))->setText( spied->property(property.key().toStdString().c_str()).toString() );
                    }
                    break;

                case QVariant::Bool:
                    if( spied->property(property.key().toStdString().c_str()).toBool() ) // TRUE
                    {
                        ((QComboBox*)(property.value().widget))->setCurrentIndex( SPY_TRUE );
                    }
                    else
                    {
                        ((QComboBox*)(property.value().widget))->setCurrentIndex( SPY_FALSE );   // FALSE
                    }
                    break;

                default:
                    break;
            }
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidget::onLineTextEdited(const QString& text)
{
    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        QObject* sender = QObject::sender();
        if(sender)
        {
            // Go through properties
            QMapIterator<QString, PropertyInformation> property(_propertyMap);
            while (property.hasNext())
            {
                property.next();

                // Check if the sender is this perperty widget
                if( property.value().widget != sender )
                {
                    continue;
                }
                
                // 
                switch(property.value().type)
                {
                    case QVariant::String:
                        spied->setProperty(property.key().toStdString().c_str(), ((QLineEdit*)(property.value().widget))->text());
                        break;

                    default:
                        throw std::runtime_error("SpyWidget::onLineTextEdited -> type unmanaged for this widget");
                        break;
                }
            }
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidget::onComboBoxBool( int index )
{
    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        QObject* sender = QObject::sender();
        if(sender)
        {
            // Go through properties
            QMapIterator<QString, PropertyInformation> property(_propertyMap);
            while (property.hasNext())
            {
                property.next();

                // Check if the sender is this perperty widget
                if( property.value().widget != sender )
                {
                    continue;
                }
                
                // 
                switch(property.value().type)
                {
                    case QVariant::Bool:
                        bool value;
                        if(((QComboBox*)(property.value().widget))->currentIndex() == SPY_TRUE )
                        {
                            value = true;
                        }
                        else
                        {
                            value = false;
                        }
                        spied->setProperty(property.key().toStdString().c_str(), value);
                        break;

                    default:
                        throw std::runtime_error("SpyWidget::onLineTextEdited -> type unmanaged for this widget");
                        break;
                }
            }
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidget::closeEvent(QCloseEvent* event)
{
    if(_spyblock)
    {
        //
        QSharedPointer<SpyBlock> spyblock = _spyblock.toStrongRef();
        
        //
        spyblock->hide();
        
        //
        event->ignore();
    }
}
