#ifndef SPYWIDGETFOOTER_HPP
#define SPYWIDGETFOOTER_HPP

#include <QWidget>
#include <BotBlock.hpp>

#include <QComboBox>
#include <QPushButton>

//!
//! Footer of the spy widget
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidgetFooter : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit SpyWidgetFooter(QWidget *parent = 0);

    //!
    //! To update block information
    //!
    void setSpiedBlock(QWeakPointer<BotBlock> block) { _block = block; updateValues(); }

    //!
    //! To get a shared pointer the spied block (0 if no spied block)
    //!
    QSharedPointer<BotBlock> getSharedSpiedBlock()
    {
        if(_block) { return _block.toStrongRef();        }
        else       { return QSharedPointer<BotBlock>(0); }
    }

public slots:

    //! Update values of the widget with data from the spied block
    void updateValues();
    
    //! Kill the spied block
    void killSpiedBlock();
    
    //! Create a son to the spied block
    void createSonOfSpiedBlock();

protected:
    //! Button to kill the spied block
    QPushButton _buttonKill;

    //! Button to create a son to the spied block
    QPushButton _buttonCreate;

    // Combobox to select an other spied block
    QComboBox _cbSpiedBlock;
    
    //! The spied block
    QWeakPointer<BotBlock> _block;
};

#endif // SPYWIDGETFOOTER_HPP
