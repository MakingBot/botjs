#include <SpyWidgetHeader.hpp>
#include <SpyBlock.hpp>
#include <QEvent>
#include <QPainter>
#include <QGridLayout>
#include <QStyleOption>

/* ============================================================================
 *
 * */
SpyWidgetHeader::SpyWidgetHeader(QWidget *parent)
    : QWidget(parent)
    , _labelTypName ( "type" )
    , _labelVersion ( "version")
    , _labelRolName ( "role" )
    , _labelFather  ( "father" )
    , _labelSonsNub ( "sons" )
    , _labelConnNub ( "connections" )
{
    // Widget geometrie
    const int height_name = 96;
    const int height      = height_name + 64;
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    // Widget properties
    this->setObjectName("SpyWidgetHeader");
    this->setStyleSheet("QWidget#SpyWidgetHeader"
    "{"
    "background-color: #FFFFFF;"\
    "}");

    // Label name properties
    setLabelNameProperties();
    _labelName.setMinimumHeight(height_name);
    _labelName.setMaximumHeight(height_name);
    _labelName.setAlignment(Qt::AlignBottom);

    // Widget composition
    new QGridLayout(this);
    ((QGridLayout*)layout())->setSpacing(5);
    ((QGridLayout*)layout())->setContentsMargins(0,0,0,0);
    	
    ((QGridLayout*)layout())->addWidget(&_labelName , 0, 0, 1, 6, Qt::AlignTop);

    ((QGridLayout*)layout())->addWidget(&_labelTypName, 1, 0);
    ((QGridLayout*)layout())->addWidget(&_labelVersion, 1, 1);
    ((QGridLayout*)layout())->addWidget(&_labelRolName, 1, 2);
    ((QGridLayout*)layout())->addWidget(&_labelFather , 1, 3);
    ((QGridLayout*)layout())->addWidget(&_labelSonsNub, 1, 4);
    ((QGridLayout*)layout())->addWidget(&_labelConnNub, 1, 5);

    updateValues();
}

/* ============================================================================
 *
 * */
void SpyWidgetHeader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/* ============================================================================
 *
 * */
void SpyWidgetHeader::updateValues()
{
    // Lanel name has its own function
    setLabelNameProperties();

    if(_block)
    {
        QSharedPointer<BotBlock> block = _block.toStrongRef();
        
        _labelTypName.setValue(block->getBlockTypeName());
        _labelVersion.setValue(QString::number(block->getBlockVersion()));
        _labelRolName.setValue(BotBlock::BlockRoleToString(block->getBlockRole()));
        _labelSonsNub.setValue(QString::number(block->getBlockNumberOfSons()));
        _labelConnNub.setValue(QString::number(block->getBlockNumberOfConnections()));
        
        QWeakPointer<BotBlock> father = block->getBlockFather();
        if(father)
        {
            _labelFather.setValue(father.toStrongRef()->getBlockName());  
        }
        else
        {
            _labelFather .setValue("X");
        }
    }
    else
    {
        _labelTypName.setValue("");
        _labelVersion.setValue("");
        _labelRolName.setValue("");
        _labelFather .setValue("");
        _labelSonsNub.setValue("");
        _labelConnNub.setValue("");
    }    
}
