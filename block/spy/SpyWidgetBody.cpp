#include <SpyWidgetBody.hpp>
#include <SpyBlock.hpp>

#include <iostream>

#include <QEvent>
#include <QPainter>
#include <QFormLayout>
#include <QGridLayout>
#include <QMapIterator>
#include <QVectorIterator>
#include <QStyleOption>

#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <ViewerRealList.hpp>
#include <ViewerQVectornD.hpp>
#include <ViewerQMatrix4x4.hpp>

#include <ViewerInteger.hpp>


/* ============================================================================
 *
 * */
SpyWidgetBody::SpyWidgetBody(SpyBlock*  spy_block, QWidget* parent)
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
    QSharedPointer<BotBlock> spied = _spyblock->weakSpiedBlock().toStrongRef();
    if(!spied) { return; }

    // Go through properties
    quint id = 0;
    QVectorIterator<QSharedPointer<IProperty> > property( spied->iProperties() );
    while (property.hasNext())
    {
        // New property, new widget
        QSharedPointer<IProperty> cur_property = property.next();
        QWidget* widget = 0;

        // Go next if no property associated to this id
        if(!cur_property) { id++; continue; }

        // Create the widget in function of the property type
        switch(cur_property->type())
        {
            
            case IProperty::IPTypeInt:
                widget = new ViewerInteger(id, !property.value().isWritable());
                if( property.value().isWritable() )
                {
                    connect( (ViewerInteger*)widget, SIGNAL(newValueRequestedFor(quint8)), this, SLOT(onNewValueRequestFor(quint8)) );
                }
                
            default:
                // TODO log the warning
                break;
        }
        
        // Go next if no widget has been created 
        if(!widget) { id++; continue; }

        // Add it into the layout
        // _widgetMap[property.key()] = widget;
        // ((QFormLayout*)layout())->addRow( propids.key(property.key()), widget );
        id++;
    }
    
    
    /*

    QMapIterator<quint8, IProperty> property(properties);
    while (property.hasNext())
    {
        // New property, new widget
        property.next();
        QWidget* widget = 0;

        // Create the widget in function of the property type
        switch(property.value().type())
        {

            case IProperty::IPTypeInt:
                widget = new ViewerInteger(property.key(), !property.value().isWritable());
                if( property.value().isWritable() )
                {
                    connect( (ViewerInteger*)widget, SIGNAL(newValueRequestedFor(quint8 propid)), this, SLOT(onNewValueRequestFor(quint8)) );
                }
                
                //((QSpinBox*)widget)->setRange ( -0xFFFFF, 0xFFFFFF);
                break;

            default:
                // TODO log the warning
                break;
        }
        if(!widget) { continue; }

        // Add it into the layout
        _widgetMap[property.key()] = widget;
        ((QFormLayout*)layout())->addRow( propids.key(property.key()), widget );
    }
*/
/*





        std::cout << property.key().toStdString() << std::endl;



            case IProperty::IPTypeBool:
                if(property.value().isWritable())
                {
                    widget = new QComboBox();
                    ((QComboBox*)widget)->addItems( QStringList( {"TRUE", "FALSE"} ) );
                    connect( (QComboBox*)widget, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onComboBoxBool(const QString&)) );
                }
                else
                {

                }
                break;



            case IProperty::IPTypeReal:
                widget = new QDoubleSpinBox();
                connect( (QDoubleSpinBox*)widget, SIGNAL(valueChanged(double)), this, SLOT(onDoubleSpinBoxChange(double)) );
                break;

            case IProperty::IPTypeString:
                if(property.value().isWritable())
                {
                    widget = new QLineEdit();
                    connect( widget, SIGNAL(textEdited(const QString&)), this, SLOT(onLineTextEdited(const QString&)) );
                }
                else
                {
                    widget = new QLabel(); 
                }
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
               // ((QComboBox*)widget)->addItems( spied->selectBlockSonChains( property.value().compatList() ) );
                break;

            case IProperty::IPTypeBrotherBlock:
                break;
            
            case IProperty::IPTypeRealList:
                widget = new ViewerRealList();
                break;

            case IProperty::IPTypeVector3D:
                widget = new ViewerQVectornD(3);
                connect( (ViewerQVectornD*)widget, SIGNAL(modelEdited(const QVector3D&)), this, SLOT(onVector3DEdit(const QVector3D&)) );
                if(property.value().isWritable())
                {
                    
                }
                else
                {
 
                }
                break;

            case IProperty::IPTypeVector4D:
                widget = new ViewerQVectornD(4);
                connect( (ViewerQVectornD*)widget, SIGNAL(modelEdited(const QVector4D&)), this, SLOT(onVector4DEdit(const QVector4D&)) );
                if(property.value().isWritable())
                {
                    
                }
                else
                {
 
                }
                break;    

            case IProperty::IPTypeMatrix44:
                if(property.value().isWritable())
                {
                    
                }
                else
                { widget = new ViewerQMatrix4x4(true); }
                
                break;        


        }
        if(!widget) { continue; }

    }
*/

    updateValues();
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::updateValues()
{
    /*
    // Check the spied block pointer
    QSharedPointer<BotBlock> spied = _spyblock->weakSpiedBlock().toStrongRef();
    if(!spied) { return; }

    // Get properties
    // const QMap<QString, quint8>& propids = spied->iPropIds();
    const QMap<quint8, IProperty>& properties = spied->iProperties();

    // Go through widgets
    QMapIterator<quint8, QWidget*> widget(_widgetMap);
    while (widget.hasNext())
    {
        // Get widget and property associated
        widget.next();
        IProperty property = properties[widget.key()];

        //
        switch(property.type())
        {

            case IProperty::IPTypeInt:
                ((ViewerInteger*)(widget.value()))->setInterger( spied->blockIPropertyValue(widget.key()).toInt() );
                break;

            default:
                // TODO log the warning
                break;
        }
    }
*/
    /*

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

                case IProperty::IPTypeInt:

                     ((QSpinBox*)widget.value())->setValue( spied->property(widget.key().toStdString().c_str()).toInt() );


                     break;

                case IProperty::IPTypeReal:
                    ((QDoubleSpinBox*)widget.value())->setValue( spied->property(widget.key().toStdString().c_str()).toDouble() );
                    break;


                case IProperty::IPTypeString:
                    if(property.isWritable())
                    {
                        ((QLineEdit*)widget.value())->setText( spied->property(widget.key().toStdString().c_str()).toString() );
                    }
                    else
                    {
                        ((QLabel*)widget.value())->setText   ( spied->property(widget.key().toStdString().c_str()).toString() );
                    }
                    break;

                case IProperty::IPTypeEnum: 
                    ((QComboBox*)widget.value())->setCurrentIndex( ((QComboBox*)widget.value())->findText( property.enumName( spied->property(widget.key().toStdString().c_str()).toInt() ) ) );  
                    break;

                case IProperty::IPTypeSonBlock:
                	std::cout << spied->property(widget.key().toStdString().c_str()).toString().toStdString() << std::endl;
                    ((QComboBox*)widget.value())->setCurrentIndex( ((QComboBox*)widget.value())->findText( spied->property(widget.key().toStdString().c_str()).toString() ) );
                    break;

                case IProperty::IPTypeRealList:
                    ((ViewerRealList*)widget.value())->setList( qvariant_cast<QList<qreal> >( spied->property(widget.key().toStdString().c_str()) ) );
                    connect( (ViewerRealList*)widget.value(), SIGNAL(listModified(QList<qreal>&)), this, SLOT(onListModified(QList<qreal>&)) );
                    break;

                case IProperty::IPTypeVector3D:
                    ((ViewerQVectornD*)widget.value())->setModel( *((QVector3D*)spied->property(widget.key().toStdString().c_str()).data()) );
                    break;

                case IProperty::IPTypeVector4D:
                    ((ViewerQVectornD*)widget.value())->setModel( *((QVector4D*)spied->property(widget.key().toStdString().c_str()).data()) );
                    break;

                case IProperty::IPTypeMatrix44:
                    ((ViewerQMatrix4x4*)widget.value())->setMatrix( qvariant_cast<QMatrix4x4 >( spied->property(widget.key().toStdString().c_str()) ) );
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
void SpyWidgetBody::onNewValueRequestFor(quint8 propid)
{

}


/* ============================================================================
 *
 * */
void SpyWidgetBody::onLineTextEdited(const QString& text)
{
/*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        QString new_value = ((QLineEdit*)widget.value())->text();
        QString old_value = spied->property(widget.key().toStdString().c_str()).toString();

        if(new_value.compare(old_value) != 0)
        {
            spied->setProperty(widget.key().toStdString().c_str(), new_value);
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onComboBoxBool(const QString& text)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onComboBoxEnum(const QString& enum_name)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        int new_value = property.enumValue(enum_name);
        int old_value = spied->property(widget.key().toStdString().c_str()).toInt();
        
        if( new_value != old_value )
        {
            spied->setProperty( widget.key().toStdString().c_str(), new_value );
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onListModified(QList<qreal>& new_value)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        const QList<qreal>& old_value = qvariant_cast<QList<qreal> >(spied->property(widget.key().toStdString().c_str()));

        if( new_value != old_value )
        {
            spied->setProperty( widget.key().toStdString().c_str(), QVariant(QVariant::Matrix4x4, &new_value) );
        }    
    }
    */
}


/* ============================================================================
 *
 * */
void SpyWidgetBody::onVector3DEdit(const QVector3D& new_value)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        const QVector3D& old_value = qvariant_cast<QVector3D>(spied->property(widget.key().toStdString().c_str()));

        if( new_value != old_value )
        {
            spied->setProperty( widget.key().toStdString().c_str(), QVariant(QVariant::Vector3D, &new_value) );
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onVector4DEdit(const QVector4D& new_value)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        const QVector4D& old_value = qvariant_cast<QVector4D>(spied->property(widget.key().toStdString().c_str()));

        if( new_value != old_value )
        {
            spied->setProperty( widget.key().toStdString().c_str(), QVariant(QVariant::Vector4D, &new_value) );
        }
    }
    */
}

/* ============================================================================
 *
 * */
void SpyWidgetBody::onDoubleSpinBoxChange(double new_value)
{
    /*
    // Check the spied block pointer
    QWeakPointer<BotBlock> wspied = _spyblock->weakSpiedBlock();
    if(!wspied) { return; }
    QSharedPointer<BotBlock> spied = wspied.toStrongRef();
    
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
        double old_value = spied->property(widget.key().toStdString().c_str()).toDouble();

        if( new_value != old_value )
        {
            spied->setProperty( widget.key().toStdString().c_str(),  new_value );
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
    QMapIterator<quint8, QWidget*> widget(_widgetMap);
    while (widget.hasNext())
    {
        widget.next();

        // Find the label and destroy it
        QWidget* label = ((QFormLayout*)layout())->labelForField(widget.value());
        if(label)
        {
            label->deleteLater();
        }

        // Destroy the widget
        widget.value()->deleteLater();
    }
    _widgetMap.clear();
}
