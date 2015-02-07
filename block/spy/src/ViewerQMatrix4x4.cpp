#include <ViewerQMatrix4x4.hpp>
#include <QGridLayout>

/* ============================================================================
 *
 * */
ViewerQMatrix4x4::ViewerQMatrix4x4(bool readOnly, QWidget* parent)
    : QWidget(parent)
{
    // Create the layout
    QGridLayout* lay = new QGridLayout(this);
  
    for(int r=0 ; r<4 ; r++)
    {
        for(int c=0 ; c<4 ; c++)
        {
            // Get constant
            const int index = r*4 + c;

            QSharedPointer<QDoubleSpinBox> box( new QDoubleSpinBox() );
            _editMatrix.append( box );
            
            // Add to layout, define properties and connect
            lay->addWidget( box.data(), r, c );
            box->setAlignment(Qt::AlignCenter);
            connect(box.data(), SIGNAL(valueChanged(double)), this, SLOT(onValueChange(double)) );
            
        }
    }

    setReadOnly(readOnly);
}

/* ============================================================================
 *
 * */
void ViewerQMatrix4x4::setReadOnly(bool readOnly)
{
    for(int i = 0 ; i< 4*4 ; i++)
    {
        _editMatrix.at(i)->setReadOnly(readOnly);
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
            
            // Set the value in the widget
            _editMatrix[index]->setValue( _dataMatrix(r,c) );
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
        int index = 0;
        for(int i = 0 ; i< 4*4 ; i++)
        {
            if( _editMatrix.at(i).data() == sender )
            {
                index = i;
                break;
            }
        }

        // Compute constant values
        const int r = index / 4;
        const int c = index % 4;
        
        // Affect the new value
        _dataMatrix(r,c) = d;
        
        // Alert
        emit valueChanged(_dataMatrix);
    }
}
