#include <Viewer.hpp>
#include <iostream>
#include <Viewer3DBlock.hpp>


//! Maximum vertice in the obj
#define MAX_VERTEX_USED 500


/* ============================================================================
 *
 * */
Viewer::Viewer(QWeakPointer<Viewer3DBlock> parent_block, QWidget *parent)
    : QGLWidget(parent)
    , _up(0,1,0), _at(0,0,0), _eye(0,3,3)
    , _yaw(0)   , _pitch(0) , _zoom(5)
    , _parentBlock  (parent_block)
    , _vertexBuffer (QGLBuffer::VertexBuffer)
    , _indiceBuffer (QGLBuffer::IndexBuffer )
{
    connect( getSharedparentBlock().data(), SIGNAL(propertyValuesChanged()), this, SLOT(onBlockPropertiesChanged()) );
    onBlockPropertiesChanged();
}

/* ============================================================================
 *
 * */
void Viewer::onBlockPropertiesChanged()
{
    makeCurrent();
    QSharedPointer<Viewer3DBlock> pblock = getSharedparentBlock();
    if(pblock)
    {
        // Background color
        glClearColor(pblock->bgColor().x(), pblock->bgColor().y(), pblock->bgColor().z(), 1.0f);

    }
    else
    {
        // Background color
        glClearColor(128, 0, 0, 1.0f);

    }
    doneCurrent();
    
    // Update view
    updateGL();
}


//Compat method: gluLookAt deprecated
/*
void util_compat_gluLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat lookAtX, GLfloat lookAtY, GLfloat lookAtZ, GLfloat upX, GLfloat upY, GLfloat upZ) {
    Vector3f x, y, z;
    z = Vector3f(eyeX-lookAtX, eyeY-lookAtY, eyeZ-lookAtZ).normalize();
    y = Vector3f(upX, upY, upZ);
    x = y ^ z;
    y = z ^ x;
    x = x.normalize();
    y = y.normalize();
    // mat is given transposed so OpenGL can handle it.
    Matrix4x4 mat (new GLfloat[16]
                     {x.getX(), y.getX(),   z.getX(),   0,
                     x.getY(),  y.getY(),   z.getY(),   0,
                     x.getZ(),  y.getZ(),   z.getZ(),   0,
                     -eyeX,     -eyeY,      -eyeZ,      1});
    glMultMatrixf(mat.getComponents());
}
*/
/*
void gluLookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up)
{
    // z vector
    QVector3D z = eye-at;
    z.normalize();
    
    // y vector
    QVector3D y = up;
    
    QVector3D x = QVector3D::crossProduct(y, z);
              y = QVector3D::crossProduct(z, x);

    x.normalize();
    y.normalize();

    // mat is given transposed so OpenGL can handle it.
    QMatrix4x4 mat(
         x.x()  ,  y.x()  ,  z.x()  , 0 ,
         x.y()  ,  y.y()  ,  z.y()  , 0 ,
         x.z()  ,  y.z()  ,  z.z()  , 0 ,
        -eye.x(), -eye.y(), -eye.z(), 1 );

    glMultMatrixf(mat.constData());    
}
*/

/* ============================================================================
 *
 * */
void Viewer::paintGL()
{
    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformation matrix
    glLoadIdentity();

    // Compute camera vectors
    _eye.setX( _at.x() + qCos(_yaw) * qCos(_pitch) );
    _eye.setY( _at.y() +              qSin(_pitch) );
    _eye.setZ( _at.z() + qSin(_yaw) * qCos(_pitch) );

    QVector3D direction = _eye-_at;
    _eye = direction * _zoom;

    // Look at
    // gluLookAt( _eye, _at, _up);
    gluLookAt( _eye.x() , _eye.y() , _eye.z() ,
                _at.x() ,  _at.y() ,  _at.z() ,
                _up.x() ,  _up.y() ,  _up.z() );


    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(0, 2, 0);
    glEnd();

        glEnable( GL_LINE_SMOOTH );
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth( 1.5 );
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(6, 0, 0);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth( 1.5 );
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 6, 0);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth( 1.5 );
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 6);
    glEnd();
    glDisable( GL_LINE_SMOOTH );
}

/* ============================================================================
 *
 * */
void Viewer::initializeGL()
{
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    _vertexBuffer.create();
    _vertexBuffer.bind();
    _vertexBuffer.setUsagePattern(QGLBuffer::DynamicDraw);
    _vertexBuffer.allocate(MAX_VERTEX_USED * sizeof(QVector3D));
    _vertexBuffer.release();

    _indiceBuffer.create();
    _indiceBuffer.bind();
    _indiceBuffer.setUsagePattern(QGLBuffer::DynamicDraw);
    _indiceBuffer.allocate(MAX_VERTEX_USED * sizeof(GLuint    ));
    _indiceBuffer.release();
}


/* ============================================================================
 *
 * */
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

/* ============================================================================
 *
 * */
void Viewer::resizeGL(int width, int height)
{
    // Basic verification
    if(height == 0) height = 1;

    // Initialize view projection
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //perspectiveGL(70.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    gluPerspective(70.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    // Initialize model view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* ============================================================================
 *
 * */
void Viewer::wheelEvent(QWheelEvent *event)
{
    // Compute direction vector
    QVector3D direction = _at - _eye;
    direction.normalize();

    // Compute step number
    qint32 num_steps = (event->delta() / 8) / 15;

    // Compute new zoom
    _zoom += num_steps*0.5;

    // Accept event
    event->accept();

    // Update view
    updateGL();
}

/* ============================================================================
 *
 * */
void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    if(_moveView)
    {
        // Compute differences
        qint32 xdiff = event->pos().x() - _oldMousePos.x();
        qint32 ydiff = event->pos().y() - _oldMousePos.y();

        // Compute x movement
        if( xdiff )
        {
            _yaw += ( xdiff * 0.01 );
        }

        // Compute y movement
        if( ydiff )
        {
            _pitch += ( ydiff * 0.01 );
        }

        // Save mouse postion
        _oldMousePos = event->pos();
    }
    // Update view
    updateGL();
}

/* ============================================================================
 *
 * */
void Viewer::mousePressEvent(QMouseEvent *event)
{
    // Enable view movement
    _moveView = true;

    // Save mouse postion
    _oldMousePos = event->pos();

    // Update view
    updateGL();
}

/* ============================================================================
 *
 * */
void Viewer::mouseReleaseEvent(QMouseEvent *event)
{
    // Disable view movement
    _moveView = false;

    // Save mouse postion
    _oldMousePos = event->pos();

    // Update view
    updateGL();
}

/* ============================================================================
 *
 * */
void Viewer::closeEvent(QCloseEvent* event)
{
    if(_parentBlock)
    {
        //
        QSharedPointer<Viewer3DBlock> pblock = _parentBlock.toStrongRef();
        
        //
        pblock->hide();
        
        //
        event->ignore();
    }
}

