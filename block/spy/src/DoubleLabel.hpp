#ifndef DOUBLELABEL_HPP
#define DOUBLELABEL_HPP

#include <QLabel>
#include <QVBoxLayout>

//!
//! Label with the value in block bold in top and title bellow
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class DoubleLabel : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    DoubleLabel(const QString title = QString(), QWidget* parent = 0)
        : QWidget(parent), _title(title)
    {
        // Label properties
        _value.setAlignment(Qt::AlignCenter);
        _title.setAlignment(Qt::AlignCenter);

        _value.setStyleSheet(
        "color: #000000;"\
        "font-weight: 500;"\
        "font: bold 15px Roboto;"\
        );

        _title.setStyleSheet(
        "color: #000000;"\
        "font: 13px Roboto;"\
        );

        // Build layout
        QVBoxLayout* lay = new QVBoxLayout(this);
        lay->addWidget(&_value);
        lay->addWidget(&_title);
    }

    //! Value setter
    void setValue(const QString& value) { _value.setText(value); }

protected:
    //! Value
    QLabel _value;

    //! Title
    QLabel _title;
};


#endif // DOUBLELABEL_HPP

