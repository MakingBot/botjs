#include <ViewerVector3D.hpp>
#include <QHBoxLayout>

/* ============================================================================
 *
 * */
ViewerVector3D::ViewerVector3D(QWidget* parent)
    : _editX(new QDoubleSpinBox())
    , _editY(new QDoubleSpinBox())
    , _editZ(new QDoubleSpinBox())
{
    // Limit boxes
    const int limit = 64;
    _editX->setMaximumWidth(limit);
    _editY->setMaximumWidth(limit);
    _editZ->setMaximumWidth(limit);
    
    // Create the layout
    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(_editX);
    lay->addWidget(_editY);
    lay->addWidget(_editZ);

    // Set large range
    _editX->setRange(-0xFFFFFFF , 0xFFFFFFF);
    _editY->setRange(-0xFFFFFFF , 0xFFFFFFF);
    _editZ->setRange(-0xFFFFFFF , 0xFFFFFFF);

}

/* ============================================================================
 *
 * */
void ViewerVector3D::updateValues()
{

}

/* ============================================================================
 *
 * */
void ViewerVector3D::onValueChange(double d)
{

}

