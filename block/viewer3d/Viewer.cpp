#include <Viewer.hpp>
#include <QCloseEvent>
#include <RenderNode.hpp>
#include <Viewer3DBlock.hpp>

#include <iostream>

#include <QTime>

//! Maximum vertice in the obj
#define MAX_VERTEX_USED 10000

/* ============================================================================
 *
 * */
Viewer::Viewer(Viewer3DBlock* parent_block, QWidget* parent_widget)
    : QGLWidget(parent_widget)
    , _up(0,1,0), _at(0,0,0), _eye(0,3,3)
    , _yaw(0)   , _pitch(0) , _zoom(5)
    , _parentBlock(parent_block)
    , _vbo(*this)
{
    // Connect the viewer with the evolution of the parent block 
    connect( _parentBlock, SIGNAL(blockiPropertyValuesChanged()), this, SLOT(onBlockPropertiesChange()) );
    connect( _parentBlock, SIGNAL(blockfPropertyValuesChanged()), this, SLOT(onBlockPropertiesChange()) );
    
    // First update
    onBlockPropertiesChange();
}

/* ============================================================================
 *
 * */
PhysicBlock::ModelType Viewer::model()
{
    if(_parentBlock){ return _parentBlock->model(); }
    else            { return PhysicBlock::ModelTypeBase; }
}
    
/* ============================================================================
 *
 * */
void Viewer::onBlockPropertiesChange()
{
    // Get opengl context
    makeCurrent();

    if(_parentBlock)
    {
        // Background color
        glClearColor(_parentBlock->bgColor().x(), _parentBlock->bgColor().y(), _parentBlock->bgColor().z(), 1.0f);

        // Start timer
        QTime timer;
        timer.start();

        
        // Check if there is an object to render
        QSharedPointer<PhysicBlock> physic_object = _parentBlock->sharedObject();
        if(physic_object)
        {

            _vbo.reset();

            //! Update the rendering tree
            _renderingTree = QSharedPointer<RenderNode>( new RenderNode(physic_object, this) );

            _vbo.write();

            // Log
            _parentBlock->beglog() << "Update render tree" << _parentBlock->endlog();
        }

        // Stop timer and log
        int elapsed = timer.elapsed();
        _parentBlock->beglog() << "New properties have been taken into account in " << elapsed << "ms" << _parentBlock->endlog();

    }
    else
    {
        // Background color
        glClearColor(128, 0, 0, 1.0f);

    }

    // Free opengl context
    doneCurrent();
    
    // Update view
    updateGL();
}


/* ============================================================================
 *
 * */
void Viewer::updateRenderingTreeStructure()
{

}

/* ============================================================================
 *
 * */
void Viewer::onRenderNodeChange()
{



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


//    glTranslated( 5, 2 ,3);

    // double test[16];
    // glGetDoublev( GL_MODELVIEW_MATRIX, test );
    // for(int j=0 ; j<4 ; j++)
    //     {
    //     for(int i=0 ; i<4 ; i++)
    //     {  
            
    //         std::cout << test[i*4+j] << " , ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl << std::endl;



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





    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    // _vbo.bind();

    // // Draw the object
    // _renderingTree->draw();

    // _vbo.release();



    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);





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

    // glEnable(GL_BLEND);
    // glEnable(GL_POLYGON_SMOOTH);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


    // float global_ambient[] = { 1.0f, 0.5f, 0.5f, 1.0f };
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    // int MatSpec [4] = {1,1,1,1};
    // glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    // glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);


    // int LightPos[4] = {5,5,5,1};
    // glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

    // // Enable lighting
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

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
        // Hide the widget
    	_parentBlock->hide();
        
        // Ignore the event
        event->ignore();
    }
}