#ifndef VIEWERVECTOR3D_HPP
#define VIEWERVECTOR3D_HPP

#include <QVector3D>
#include <QDoubleSpinBox>
 
//!
//! To display and modify Vector3D
//!
class ViewerVector3D : public QWidget
{

public:
    //!
    //! Default constructor
    //!
    explicit ViewerVector3D(QWidget* parent=0);
    
    //! The data model getter
    const QVector3D& vector() const { return _vector; }
    
    //! The data model setter
    void setVector(const QVector3D& vec) { _vector = vec; }
    
protected:
    //! The data model
    QVector3D _vector;

    // To display x
    QDoubleSpinBox* _editX;
    
    // To display y
    QDoubleSpinBox* _editY;
    
    // To display z
    QDoubleSpinBox* _editZ;
};

#endif // VIEWERVECTOR3D_HPP
