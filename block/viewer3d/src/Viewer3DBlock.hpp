#ifndef VIEWER3DBLOCK_HPP
#define VIEWER3DBLOCK_HPP

#include <QtGlobal>
#include <Viewer.hpp>
#include <BotBlock.hpp>

//!
//! Wrap functions for the robot viewer 3D
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Viewer3DBlock : public BotBlock
{
    Q_OBJECT
    Q_PROPERTY(bool      visible READ visible WRITE setVisible MEMBER _visible)

public:
    //!
    //! Default constructor
    //!
    explicit Viewer3DBlock(const QString& name = QString("viewer3d"), QObject *parent = 0);

    //! FROM BotBlock
    virtual void blockInit(QSharedPointer<BotEngine> js_engine);

    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }
    
    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockUi; }
    
    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("viewer3d"); }

    //!
    //! Create the widget if it is not
    //!
    void createWidgetIfRequired()
    {
        if(!_widget) {
            _widget = QSharedPointer<Viewer>( new Viewer( qSharedPointerObjectCast<Viewer3DBlock, BotBlock>(this->getBlockSharedFromThis()) ) );
        }
    }

    //! Widget visibility getter
    bool visible() { return _visible; }
    
    //! Widget visibility setter
    void setVisible(bool visible)
    {
        if(visible) { show(); }
        else        { hide(); }
    }

    //! Background color getter
    const QVector3D& bgColor() const { return _bgColor; }

    //! Background color setter
    void setBgColor(const QVector3D& vec) { _bgColor = vec; emit blockiPropertyValuesChanged(); }

signals:


public slots:

    //! Widget visibility setter
    virtual void show()
    {
        createWidgetIfRequired();
        _widget->show(); _visible = true;  emit blockiPropertyValuesChanged();
    }

    //! Widget visibility setter
    virtual void hide() { _widget->hide(); _visible = false; emit blockiPropertyValuesChanged(); }

protected:
    //! Widget visibility
    bool _visible;

    //! Background color
    QVector3D _bgColor;

    //! Pointer on the viewer widget
    QSharedPointer<Viewer> _widget;

};


#endif // VIEWER3DBLOCK_HPP
