#ifndef SPYBLOCK_HPP
#define SPYBLOCK_HPP

#include <SpyWidget.hpp>

//!
//! The Spy Block povide a way to get and modify block properties and data 
//!
class SpyBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(bool    visible        READ visible WRITE setVisible MEMBER _visible )
    Q_PROPERTY(QString spiedBlockName READ getSpiedBlockName                        )

public:
    //!
    //! Default constructor
    //!
    explicit SpyBlock(const QString& name = QString("spy"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void blockInit(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockSpy; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("spy"); }

    //! FROM BotBlock
    virtual int getBlockNumberOfConnections() const
    {
        if(_spiedBlock) { return 1; }
        else            { return 0; }
    }


    //!
    //! Create the widget if it is not
    //!
    void createWidgetIfRequired()
    {
        if(!_widget) {
            _widget = QSharedPointer<SpyWidget>( new SpyWidget( qSharedPointerObjectCast<SpyBlock, BotBlock>(this->getBlockSharedFromThis()) ) );
        }
    }

    //!
    //! Widget visibility getter
    //!
    bool visible() { return _visible; }
    
    //!
    //! Widget visibility setter
    //!
    void setVisible(bool visible)
    {
        if(visible) { show(); }
        else        { hide(); }
    }
   
    QWeakPointer<BotBlock> getSpiedBlock() { return _spiedBlock; }

    //!
    //! Pointer on the spied block
    //!
    QSharedPointer<BotBlock> getSharedSpiedBlock()
    {
        if(_spiedBlock) { return _spiedBlock.toStrongRef();   }
        else            { return QSharedPointer<BotBlock>(0); }
    }

    //!
    //! Spied block name getter
    //!
    const QString getSpiedBlockName()
    {
        QSharedPointer<BotBlock> spied = getSharedSpiedBlock();
        if(spied) { return spied->getBlockName(); }
        return QString();
    }

signals:
    //! Emitted when the spied block has changed
    void spiedBlockChanged();

public slots:

    //! FROM BotBlock
    virtual bool connect(BotBlock* block, bool master=true);

    //!
    //! Widget visibility setter
    //!
    virtual void show()
    { 
        createWidgetIfRequired();
        _widget->show(); _visible = true;  /* emit propertyValuesChanged(); */
    }

    //!
    //! Widget visibility setter
    //!
    virtual void hide() { _widget->hide(); _visible = false; /* emit propertyValuesChanged(); */ }

protected:
    //! Widget visibility
    bool _visible;

    //! Pointer on the spied block
    QWeakPointer<BotBlock> _spiedBlock;

    //! Widget
    QSharedPointer<SpyWidget> _widget;
};

#endif // SPYBLOCK_HPP
