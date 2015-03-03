#ifndef GRAPHICSBLOCKSCENE_HPP
#define GRAPHICSBLOCKSCENE_HPP

#include <BotEngine.hpp>
#include <QGraphicsScene>
#include <GraphicsBlockItem.hpp>

//!
//! The scene of blocks
//!
class GraphicsBlockScene : public QGraphicsScene
{
    Q_OBJECT
    
public:
    //!
    //! Default constructor
    //!
    explicit GraphicsBlockScene(QWidget* parent = 0);

    //!
    //! Javascript engine setter
    //!
    void setJsEngine(QSharedPointer<BotEngine> js_engine) { _jsEngine = js_engine; }

protected:
    //! Window parent
    QWidget* _wParent;

    //! Pointer on the js engine
    QSharedPointer<BotEngine> _jsEngine;

    //! FROM QGraphicsScene
    void dragMoveEvent (QGraphicsSceneDragDropEvent* event) Q_DECL_OVERRIDE;

    //! FROM QGraphicsScene
    void dropEvent     (QGraphicsSceneDragDropEvent* event) Q_DECL_OVERRIDE;



};


#endif // GRAPHICSBLOCKSCENE_HPP
