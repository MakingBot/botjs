#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <QList>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

//!
//! Provide a widget to select a text among severals
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class Selector : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit Selector(QWidget parent = 0)
    {
        new QHBoxLayout(this);
    }
    
    //void 

signals:

    //! When a new box has been selected
    void selectionChanged(QString selection);

protected:
    
    //! Selection buttons 
    QList<QPushButton> _buttons;

};

#endif // SELECTOR_HPP
