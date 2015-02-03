#ifndef GRAPHICSMENUITEM_H
#define GRAPHICSMENUITEM_H

#include <QLabel>

//!
//! Menu item of the composer
//!
class MenuItem : public QLabel
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    MenuItem(const QString& block_name, QWidget* parent=0);

    //! FROM QWidget
    bool eventFilter(QObject *object, QEvent *event);

    //! FROM Widget
    virtual QSize sizeHint() const;

protected:
    //! The block name
    const QString _blockName;

    //! FROM QLabel
    virtual void mouseMoveEvent(QMouseEvent* ev);

    //! FROM QLabel
    virtual void mousePressEvent(QMouseEvent* ev);

    //! FROM QLabel
    virtual void mouseReleaseEvent(QMouseEvent* ev);
};

#endif // GRAPHICSMENUITEM_H
