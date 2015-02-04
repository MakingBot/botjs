#ifndef SPYWIDGETHEADER_HPP
#define SPYWIDGETHEADER_HPP

#include <BotBlock.hpp>
#include <widget/DoubleLabel.hpp>

class SpyBlock;

//!
//! Header of the spy widget
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
class SpyWidgetHeader : public QWidget
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //!
    explicit SpyWidgetHeader(QWidget *parent = 0);

    //! FROM QWidget
    void paintEvent(QPaintEvent *event);

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
    //! Update property values
    void updateValues();

protected:
    //! Label for name 
    QLabel _labelName;

    //! Tag for the type name
    DoubleLabel _labelTypName;

    //! Tag for version
    DoubleLabel _labelVersion;

    //! Tag for version
    DoubleLabel _labelRolName;

    //! Label for father name
    DoubleLabel _labelFather;

    //! Label for number of sons
    DoubleLabel _labelSonsNub;

    //! Label for number of connections
    DoubleLabel _labelConnNub;




    // 3 buttons (radio)
    // no log
    // enbale log     
    // enable verbose 




    //! The spied block
    QWeakPointer<BotBlock> _block;

    //!
    //! Set properties of the label name
    //!
    void setLabelNameProperties()
    {
        QSharedPointer<BotBlock> block = getSharedSpiedBlock();
        if(block)
        {
            _labelName.setText(block->getBlockName());
            _labelName.setStyleSheet(
            "background-color:" + BotBlock::BlockRoleToColor(block->getBlockRole()) + " ;"\
            "color: #FFFFFF;"\
            "font: 34px Roboto;"\
            "padding: 10px;"\
            );
        }
        else
        {
            _labelName.setText("No block spied");
            _labelName.setStyleSheet(
            "background-color:" + BotBlock::BlockRoleToColor((BotBlock::BlockRole)0xFFFF) + " ;"\
            "color: #FFFFFF;"\
            "font: 34px Roboto;"\
            "padding: 10px;"\
            );
        }
    }

};

#endif // SPYWIDGETHEADER_HPP
