#ifndef COMPOSERBLOCK_HPP
#define COMPOSERBLOCK_HPP

#include <BotBlock.hpp>
#include <ComposerWidget.hpp>

//!
//! Block that allow to create the block architecture with a graphic interface
//!
class ComposerBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(bool    visible        READ visible WRITE setVisible MEMBER _visible )
    
public:
    //!
    //! Default constructor
    //!
    explicit ComposerBlock(const QString& name = QString("composer"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void init(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("composer"); }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockUi; }
    
    //! FROM BotBlock
    virtual QString getBlockDescription() const
    {
        return QString();
    }
    
    //!
    //! Create the widget if it is not
    //!
    void createWidgetIfRequired()
    {
        if(!_widget) {
            _widget = QSharedPointer<ComposerWidget>( new ComposerWidget( qSharedPointerObjectCast<ComposerBlock, BotBlock>(this->sharedFromThis()) ) );
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

public slots:
    //! FROM BotBlock
    virtual void connect(BotBlock* block);

    //! FROM BotBlock
    virtual void show() {
        createWidgetIfRequired();
        _widget->show(); _visible = true;  emit propertyValuesChanged();    }

    //! FROM BotBlock
    virtual void hide() { _widget->hide(); emit propertyValuesChanged();    }

protected:
    //! Widget visibility
    bool _visible;

    //! Widget
    QSharedPointer<ComposerWidget> _widget;
};

#endif // COMPOSERBLOCK_HPP
