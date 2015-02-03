#ifndef COMPOSERWIDGET_H
#define COMPOSERWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <BotBlock.hpp>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <GraphicsBlockScene.hpp>

class ComposerBlock;

//!
//! Composer widget
//!
class ComposerWidget : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit ComposerWidget(QWeakPointer<ComposerBlock> composer_block, QWidget *parent = 0);

    //!
    //! Javascript engine setter
    //!
    void setJsEngine(QSharedPointer<BotEngine> js_engine)
    {
        _jsEngine = js_engine;
        _scene->setJsEngine(_jsEngine);
    }


signals:

public slots:



protected:
    //! Pointer on the js engine
    QSharedPointer<BotEngine> _jsEngine;

    //! Parent block
    QWeakPointer<ComposerBlock> _composerblock;




    //! The menu widget
    QWidget* _menu;

    //! The scroll zone
    QScrollArea* _menuZone;

    //! The viewport
    QGraphicsView* _view;

    //! The scene
    GraphicsBlockScene* _scene;

    //! FROM QWidget
    virtual void closeEvent(QCloseEvent* event);
};

#endif // COMPOSERWIDGET_H
