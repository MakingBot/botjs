#include <ViewerQMatrix4x4.hpp>

/* ============================================================================
 *
 * */
ViewerQMatrix4x4::ViewerQMatrix4x4(QWidget* parent)
    : QWidget(parent)
    , _editMatrix( QVector<QDoubleSpinBox>(4*4) )
{
    // Create the layout
    QGridLayout* lay = new QGridLayout(this);
  
    for(int r=0 ; r<4 ; r++)
    {
        for(int c=0 ; c<4 ; c++)
        {
            // Get constant
            const int index = r*4 + c;
            QDoubleSpinBox* widget = &(_editMatrix[index]);
            
            // Add to layout, define properties and connect
            lay->addWidget( widget, r, c );
            widget->setAlignment(Qt::AlignCenter);
            connect(widget, SIGNAL(valueChanged(double)), this, onValueChange(double) );
        }
    }
}

/* ============================================================================
 *
 * */
void ViewerQMatrix4x4::updateValues()
{
    // Go through widgets
    for(int r=0 ; r<4 ; r++)
    {
        for(int c=0 ; c<4 ; c++)
        {
            const int index = r*4 + c;
            QDoubleSpinBox* widget = &(_editMatrix[index]);
            
            // Set the value in the widget
            widget->setValue( _dataMatrix(r,c) );
        }
    }
}

/* ============================================================================
 *
 * */
void ViewerQMatrix4x4::onValueChange(double d)
{
    QDoubleSpinBox* sender = (QDoubleSpinBox*) QObject::sender();
    if(sender)
    {
        // Compute constant values
        const int index = _editMatrix->indexOf(sender);
        const int r = index / 4;
        const int c = index % 4;
        
        // Affect the new value
        _dataMatrix(r,c) = d;
        
        // Alert
        emit valueChanged(_dataMatrix);
    }
}
