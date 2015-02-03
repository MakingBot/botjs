#ifndef LOGTAG_HPP
#define LOGTAG_HPP

#include <QMap>
#include <QLabel>

//!
//! A log tag is a special colored label
//!
class LogTag : public QLabel
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit LogTag(const QString& text="Tag", QString color="#404040", QWidget *parent = 0)
        : QLabel(text, parent)
    {
        const int height = 25;
        this->setMinimumHeight(height);
        this->setMaximumHeight(height);
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        changeTextColor(text, color);
    }

    //!
    //! 
    //!
    void changeTextColor(const QString& text, QString color)
    {
        this->setStyleSheet(
        "background-color:" + color + ";"\
        "color: white;"\
        "font: bold 12px Roboto;"\
        "padding: 3px;"\
        "border-radius: 3px;");
    }

};

#endif // LOGTAG_HPP
