#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtMath>
#include <Glub.hpp>
#include <QGLBuffer>
#include <QGLWidget>
#include <QCloseEvent>

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
    explicit Viewer(QWeakPointer<Viewer3DBlock> parent_block, QWidget *parent = 0);

    //!
    //! Pointer on the parent block
    //!
    QSharedPointer<Viewer3DBlock> getSharedparentBlock()
    {
        if(_parentBlock) { return _parentBlock.toStrongRef();       }
        else             { return QSharedPointer<Viewer3DBlock>(0); }
    }

public:
    //! 
    void onBlockPropertiesChanged();

protected:
    // === VIEWER MANAGEMENT ===

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
    QWeakPointer<Viewer3DBlock> _parentBlock;

    // === ARRAY AND BUFFERS ===

    //! Array to store all vertex that will be rendered
    QVector<QVector3D>          _vertexArray;

    //! Arrays to store vertex indices
    QVector<GLuint>             _indiceArray;

    //! Vertex buffer
    QGLBuffer                   _vertexBuffer;

    //! Indice buffer
    QGLBuffer                   _indiceBuffer;

    // === FUNCTIONS ===

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