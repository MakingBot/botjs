#include <SpyWidgetHeader.hpp>
#include <SpyBlock.hpp>
#include <QEvent>
#include <QPainter>
#include <QGridLayout>
#include <QStyleOption>

/* ============================================================================
 *
 * */
SpyWidgetHeader::SpyWidgetHeader(QWeakPointer<SpyBlock> spy_block, QWidget *parent)
    : QWidget(parent)
    , _labelTypName ( "type" )
    , _labelVersion ( "version")
    , _labelRolName ( "role" )
    , _labelFather  ( "father" )
    , _labelSonsNub ( "sons" )
    , _labelConnNub ( "connections" )
    , _spyblock     ( spy_block )
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
void SpyWidgetHeader::onSpiedBlockChange()
{
    updateValues();
}

/* ============================================================================
 *
 * */
void SpyWidgetHeader::updateValues()
{
    QSharedPointer<BotBlock> block = getSharedSpyBlock()->getSharedSpiedBlock();
    if(block)
    {
        _labelName.setText(block->blockName());
        _labelName.setStyleSheet(
        "background-color:" + BotBlock::BlockRoleToColor(block->blockRole()) + " ;"\
        "color: #FFFFFF;"\
        "font: 34px Roboto;"\
        "padding: 10px;"\
        );

        _labelTypName.setValue(block->blockTypeName());
        _labelVersion.setValue(QString::number(block->blockVersion()));
        _labelRolName.setValue(BotBlock::BlockRoleToString(block->blockRole()));
        _labelSonsNub.setValue(QString::number(block->blockNbSons() ));
        _labelConnNub.setValue(QString::number(block->blockNbConnections()));
        
        QWeakPointer<BotBlock> father = block->blockFather();
        if(father)
        {
            _labelFather.setValue(father.toStrongRef()->blockName());  
        }
        else
        {
            _labelFather .setValue("X");
        }
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

        _labelTypName.setValue("");
        _labelVersion.setValue("");
        _labelRolName.setValue("");
        _labelFather .setValue("");
        _labelSonsNub.setValue("");
        _labelConnNub.setValue("");
    }    
}
