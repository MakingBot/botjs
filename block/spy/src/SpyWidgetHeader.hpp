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
    explicit SpyWidgetHeader(QWeakPointer<SpyBlock> spy_block, QWidget *parent = 0);

    //! FROM QWidget
    void paintEvent(QPaintEvent *event);

    //!
    //! Pointer on the parent spy block
    //!
    QSharedPointer<SpyBlock> getSharedSpyBlock()
    {
        if(_spyblock) { return _spyblock.toStrongRef(); }
        else          { throw std::runtime_error("This widget need a parent spy block"); }
    }

public slots:

    //! When the spied change
    void onSpiedBlockChange();

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




    //! Parent block
    QWeakPointer<SpyBlock> _spyblock;


};

#endif // SPYWIDGETHEADER_HPP
