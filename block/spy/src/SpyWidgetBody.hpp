#ifndef SPYWIDGETBODY_HPP
#define SPYWIDGETBODY_HPP

#include <QWidget>
#include <BotBlock.hpp>

class SpyBlock;

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
    SpyWidgetBody(QWeakPointer<SpyBlock> spy_block, QWidget* parent=0);

    //! FROM QWidget
    void paintEvent(QPaintEvent *event);

    //!
    //! Pointer on the parent spy block
    //!
    QSharedPointer<SpyBlock> getSharedSpyBlock()
    {
        if(_spyblock) { return _spyblock.toStrongRef(); }
        else          { throw std::runtime_error("This widget need a parent spy block"); }
    }
    
public slots:

    //! When the spied change
    void onSpiedBlockChange();

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

    //! For real list modification
    void onListModified(QList<qreal>& list);

protected:
    //! Map that contains widget of each property
    QMap<QString, QWidget*> _widgetMap;

    //! Parent block
    QWeakPointer<SpyBlock>   _spyblock;

    //! Delete all current widgets
    void destroyStructure();


    // void updateValueEnum(QSharedPointer<BotBlock> spied, BotBlock::InteractivePropertyMap& properties, QMapIterator<QString, QWidget*>& widget);


};

#endif // SPYWIDGETBODY_HPP
