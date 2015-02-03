#include <SpyWidgetBody.hpp>

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
SpyWidgetBody::SpyWidgetBody(QWidget* parent)
    : QWidget(parent)
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
void SpyWidgetBody::updateStructure()
{
    // Clean structure
    destroyStructure();

    // Check the spied block pointer
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
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
                widget = new QComboBox();
                ((QComboBox*)widget)->addItems( {"TRUE", "FALSE"} );
                //connect( (QComboBox*)widget, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxEnum(const QString&)) );
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
    /*
    QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
    if(spied)
    {
        // Get properties
        BotBlock::InteractivePropertyMap properties = spied->iProperties();
       
        // Go through widgets
        QMapIterator<QString, QWidget*> widget(_widgetMap);
        while (widget.hasNext())
        {
            widget.next();

            switch(properties[widget.key()].type)
            {
                case InteractiveObject::IPTypeReal:
                    break;

                case InteractiveObject::IPTypeEnum:

                    updateValueEnum(spied, properties, widget);


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
void SpyWidgetBody::onComboBoxBool( int index )
{

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
