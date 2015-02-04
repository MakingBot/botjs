#ifndef SPYWIDGETFOOTER_HPP
#define SPYWIDGETFOOTER_HPP

#include <QWidget>
#include <BotBlock.hpp>

#include <QComboBox>
#include <QPushButton>

class SpyBlock;

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
    explicit SpyWidgetFooter(QWeakPointer<SpyBlock> spy_block, QWidget *parent = 0);

    //!
    //! To update block information
    //!
    void setSpiedBlock(QWeakPointer<BotBlock> block) { _block = block; updateStructure(); updateValues(); }

    //!
    //! To get a shared pointer the parent spy block (0 if no spied block)
    //!
    QSharedPointer<SpyBlock> getSharedSpyBlock()
    {
        if(_spyblock) { return _spyblock.toStrongRef();     }
        else          { return QSharedPointer<SpyBlock>(0); }
    }

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

    //! Update structure
    void updateStructure();
    
    //! Kill the spied block
    void killSpiedBlock();
    
    //! Create a son to the spied block
    void createSonOfSpiedBlock();

    //! When user change the spied block
    void onCBSpiedChange( const QString & text );

protected:
    //! Button to kill the spied block
    QPushButton _buttonKill;

    //! Button to create a son to the spied block
    QPushButton _buttonCreate;

    // Combobox to select an other spied block
    QComboBox _cbSpiedBlock;

    //! Current selection of the combo box
    int _currentValidSelection;
    
    //! The spied block
    QWeakPointer<BotBlock> _block;

    //! Parent block
    QWeakPointer<SpyBlock> _spyblock;
};

#endif // SPYWIDGETFOOTER_HPP
