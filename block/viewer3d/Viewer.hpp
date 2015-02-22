#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtMath>
#include <Glub.hpp>
#include <QGLWidget>
#include <PhysicBlock.hpp>

class RenderNode;
class Viewer3DBlock;

//!
//! Opengl viewer
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Viewer : public QGLWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit Viewer(Viewer3DBlock* parent_block, QWidget* parent_widget = 0);

    //!
    //! Vertex buffer object getter
    //!
    VertexBufferObject& vbo() { return _vbo; }

    //!
    //! Model getter
    //!
    PhysicBlock::ModelType model();


public slots:

    //! Action to perform when the block properties change 
    void onBlockPropertiesChange();


    void updateRenderingTreeStructure();

    void onRenderNodeChange();

protected:

    // ========================================================================
    // => Viewer Management

    //! Up vector
    QVector3D                   _up;

    //! At vector
    QVector3D                   _at;
    
    //! Eye postion
    QVector3D                   _eye;

    //! Radian angle to lead horizontal movement
    float                       _yaw;

    //! Radian angle to lead vertical movement
    float                       _pitch;

    //! Zoom on the view
    float                       _zoom;

    //! True if the view can be moved
    bool                        _moveView;

    //! Old position of the mouse
    QPoint                      _oldMousePos;

    //! The parent block
    Viewer3DBlock*              _parentBlock;

    // ========================================================================
    // => VBO configuration

    //! VBO configuration
    VertexBufferObject          _vbo;

    //! Rendering tree
    QSharedPointer<RenderNode>  _renderingTree;

    // ========================================================================
    // => Functions

    //! QOpenGLWidget
    virtual void paintGL();

    //! QOpenGLWidget
    virtual void initializeGL();

    //! QOpenGLWidget
    virtual void resizeGL(int width, int height);

    //! FROM QWidget
    void wheelEvent(QWheelEvent *event);

    //! FROM QWidget
    void mouseMoveEvent(QMouseEvent* event);

    //! FROM QWidget
    void mousePressEvent(QMouseEvent* event);

    //! FROM QWidget
    void mouseReleaseEvent(QMouseEvent * event);

    //! FROM QWidget
    virtual void closeEvent(QCloseEvent* event);
};


#endif // VIEWER_HPP
