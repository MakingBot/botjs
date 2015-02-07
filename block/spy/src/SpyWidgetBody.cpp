#include <SpyWidgetBody.hpp>
#include <SpyBlock.hpp>

#include <iostream>

#include <QEvent>
#include <QPainter>
#include <QFormLayout>
#include <QGridLayout>
#include <QMapIterator>
#include <QStyleOption>

#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>

/* ============================================================================
 *
 * */
SpyWidgetBody::SpyWidgetBody(QWeakPointer<SpyBlock> spy_block, QWidget* parent)
    : QWidget(parent), _spyblock(spy_block)
{
    new QFormLayout(this);
    ((QFormLayout*)layout())->setSpacing(8);
    ((QFormLayout*)layout())->setContentsMargins(10,10,10,10);
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onSpiedBlockChange()
{
    updateStructure();
    updateValues();
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::updateStructure()
{
    // Clean structure
    destroyStructure();

    // Check the spied block pointer
    QSharedPointer<BotBlock> spied = getSharedSpyBlock()->getSharedSpiedBlock();
    if(!spied) { return; }
    
    // Get properties
    const QMap<QString, IProperty>& properties = spied->iProperties();

    // Go through properties
    QMapIterator<QString, IProperty> property(properties);
    while (property.hasNext())
    {
        // New property, new widget
        property.next();
        QWidget* widget = 0;

        // Create the widget in function of the property type
        switch(property.value().type())
        {
            case IProperty::IPTypeBool:
                if(property.value().isWritable())
                {
                    widget = new QComboBox();
                    ((QComboBox*)widget)->addItems( {"TRUE", "FALSE"} );
                    connect( (QComboBox*)widget, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxBool(const QString&)) );
                }
                else
                {

                }
                break;

            case IProperty::IPTypeInt:
                widget = new QSpinBox();
                break;

            case IProperty::IPTypeReal:
                widget = new QDoubleSpinBox();
                break;
                
            case IProperty::IPTypeEnum:
                widget = new QComboBox();
                ((QComboBox*)widget)->addItems( property.value().enumStringList() );
                connect( (QComboBox*)widget, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxEnum(const QString&)) );
                break;

            case IProperty::IPTypeBlock:
                break;

            case IProperty::IPTypeSonBlock:
                widget = new QComboBox();
                ((QComboBox*)widget)->addItem ( "NONE" );
                ((QComboBox*)widget)->addItems( spied->getBlockSonsChains() );
                break;

            case IProperty::IPTypeBrotherBlock:
                break;
            
            case IProperty::IPTypeVector3D:
                break;

            case IProperty::IPTypeMatrix44:
                break;        

            default:
                // TODO Log erreur
                break;
        }
        if(!widget) { continue; }

        // Add it into the layout
        _widgetMap[property.key()] = widget;
        ((QFormLayout*)layout())->addRow(property.key(), _widgetMap[property.key()]); 
    }

    updateValues();
}


/*
void SpyWidgetBody::updateValueEnum(QSharedPointer<BotBlock> spied, BotBlock::InteractivePropertyMap& properties, QMapIterator<QString, QWidget*>& widget)
{
    QString str = InteractiveObject::valueToEnumName( properties[widget.key()].enumTextList, spied->property(widget.key().toStdString().c_str()).toInt() ) ;

    std::cout << str.toStdString() << std::endl;

    int index = ((QComboBox*)widget.value())->findText( str );

    std::cout << index << std::endl;

    if(index != -1) {
        ((QComboBox*)widget.value())->setCurrentIndex( index );
    }
}
*/

/* ============================================================================
 *
 * */
void SpyWidgetBody::updateValues()
{
    QSharedPointer<BotBlock> spied = getSharedSpyBlock()->getSharedSpiedBlock();
    if(spied)
    {
        // Get properties
        const QMap<QString, IProperty>& properties = spied->iProperties();

        // Go through widgets
        QMapIterator<QString, QWidget*> widget(_widgetMap);
        while (widget.hasNext())
        {
            // Get widget and property associated
            widget.next();
            IProperty property = properties[widget.key()];

            switch(property.type())
            {
                // BOOL
                case IProperty::IPTypeBool:
                    if(property.isWritable())
                    {
                        if( spied->property(widget.key().toStdString().c_str()).toBool() )
                        { ((QComboBox*)widget.value())->setCurrentIndex( ((QComboBox*)widget.value())->findText("TRUE")  ); }
                        else
                        { ((QComboBox*)widget.value())->setCurrentIndex( ((QComboBox*)widget.value())->findText("FALSE") ); }
                    }
                    else
                    {
                        if( spied->property(widget.key().toStdString().c_str()).toBool() )
                        {

                        }
                        else
                        {

                        }
                    }
                    break;


                default:
                    break;
            }
        }
    }
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onLineTextEdited(const QString& text)
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
void SpyWidgetBody::onComboBoxBool(const QString& text)
{
    // Get spied
    QSharedPointer<BotBlock> spied = getSharedSpyBlock()->getSharedSpiedBlock();
    if(!spied) { return; }
    
    // Get sender
    QObject* sender = QObject::sender();
    if(!sender) { return; }

    // Get properties
    const QMap<QString, IProperty>& properties = spied->iProperties();

    // Go through widgets
    QMapIterator<QString, QWidget*> widget(_widgetMap);
    while (widget.hasNext())
    {
        // Get widget and property associated
        widget.next();

        // Check if the sender is this property widget
        if( widget.value() != sender )
        {
            continue;
        }

        // Get property and values
        IProperty property = properties[widget.key()];
        bool new_value;
        bool old_value = spied->property(widget.key().toStdString().c_str()).toBool();

        if( text.compare("TRUE")  == 0 ) { new_value = true;  }
        else                             { new_value = false; }
        if( old_value != new_value )
        {
            spied->setProperty(widget.key().toStdString().c_str(), new_value);
        }    
    }
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onComboBoxEnum(const QString& text)
{
    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        // Get properties
        BotBlock::InteractivePropertyMap properties = spied->iProperties();
        
        QObject* sender = QObject::sender();
        if(sender)
        {
            // Go through widgets
            QMapIterator<QString, QWidget*> widget(_widgetMap);
            while (widget.hasNext())
            {
                widget.next();

                // Check if the sender is this widget
                if( widget.value() != sender )
                {
                    continue;
                }

                // Find the value of the enum
                int value = 0;
                for( int i=0 ; i<properties[widget.key()].enumTextList.size() ; i++ )
                {
                    if( text.compare( properties[widget.key()].enumTextList.at(i).name ) == 0 )
                    {
                        value = properties[widget.key()].enumTextList.at(i).value;
                    }
                }

                // Prevent infinite loop
                if( value !=  spied->property(widget.key().toStdString().c_str()).toInt() )
                {
                    // Set the new value of the enum
                    spied->setProperty(widget.key().toStdString().c_str(), value);     
                }


            }
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::destroyStructure()
{
    // Go through widgets
    QMapIterator<QString, QWidget*> widget(_widgetMap);
    while (widget.hasNext())
    {
        widget.next();

        // Find the label and destroy it
        QWidget* label = ((QFormLayout*)layout())->labelForField(widget.value());
        if(label) {
            label->deleteLater();
        }

        // Destroy the widget
        widget.value()->deleteLater();
    }
    _widgetMap.clear();
}
