#ifndef VIEWERMATRIX4X4_HPP
#define VIEWERMATRIX4X4_HPP

#include <QVector>
#include <QMatrix4x4>
#include <QDoubleSpinBox>

//!
//! To display and modify QMatrix4x4
//!
class ViewerQMatrix4x4 : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit ViewerQMatrix4x4(bool readOnly=false, QWidget* parent=0);

    //!
    //! To set the widget read only or writable
    //!
    void setReadOnly(bool readOnly);

    //!
    //! Data model getter
    //!
    const QMatrix4x4& matrix() const { return _dataMatrix; }
    
    //!
    //! Data model setter
    //!
    void setMatrix(const QMatrix4x4& matrix) { _dataMatrix = matrix; updateValues(); }

public slots:
    //!
    //! Update widget values with the data
    //!
    void updateValues();
    
    //!
    //! When the user change a value
    //!
    void onValueChange(double d);

signals:
    //! Emitted when the matrix is modified by the user
    void valueChanged(const QMatrix4x4& matrix);

protected:
    //! Data model
    QMatrix4x4 _dataMatrix;

    //! The matrix of editor
    QVector<QSharedPointer<QDoubleSpinBox> > _editMatrix;
};

#endif // VIEWERMATRIX4X4_HPP

