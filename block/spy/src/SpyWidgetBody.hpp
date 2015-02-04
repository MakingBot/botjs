#ifndef SPYWIDGETBODY_HPP
#define SPYWIDGETBODY_HPP

#include <QWidget>
#include <BotBlock.hpp>

//!
//! Widget that display personal block properties 
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidgetBody : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    SpyWidgetBody(QWidget* parent=0);

    //! FROM QWidget
    void paintEvent(QPaintEvent *event);
    
    //!
    //! To define the new spied block
    //!
    void setSpiedBlock(QWeakPointer<BotBlock> block) { _block = block; updateStructure(); }
    
    //!
    //! To get a shared pointer the spied block (0 if no spied block)
    //!
    QSharedPointer<BotBlock> getSharedSpiedBlock()
    {
        if(_block) { return _block.toStrongRef();        }
        else       { return QSharedPointer<BotBlock>(0); }
    }
    
public slots:
    //! Update property structure
    void updateStructure();

    //! Update property values
    void updateValues();
    
    //! For line edit property widget
    void onLineTextEdited(const QString& text);

    //! For combobox that manage boolean switch
    void onComboBoxBool( const QString & text );

    //! For combobox that manage enum
    void onComboBoxEnum( const QString & text );

protected:
    //! The spied block
    QWeakPointer<BotBlock> _block;
    
    //! Map that contains widget of each property
    QMap<QString, QWidget*> _widgetMap;


    //! Delete all current widgets
    void destroyStructure();


    // void updateValueEnum(QSharedPointer<BotBlock> spied, BotBlock::InteractivePropertyMap& properties, QMapIterator<QString, QWidget*>& widget);


};

#endif // SPYWIDGETBODY_HPP
