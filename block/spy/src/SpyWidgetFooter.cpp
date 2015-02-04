#include <SpyWidgetFooter.hpp>

#include <QHBoxLayout>

/* ============================================================================
 *
 * */
SpyWidgetFooter::SpyWidgetFooter(QWidget *parent)
    : QWidget(parent)
    , _buttonKill  (QIcon(":/icon/skull"), "")
    , _buttonCreate(QIcon(":/icon/plus" ), "")
{
    const QSize button_size(32,32);

    // Configure buttons
    _buttonKill.setFlat(true);
    _buttonCreate.setFlat(true);

    _buttonKill.setIconSize(button_size);
    _buttonKill.setMinimumSize(button_size);
    _buttonKill.setMaximumSize(button_size);

    _buttonCreate.setIconSize(QSize(25,25));
    _buttonCreate.setMinimumSize(button_size);
    _buttonCreate.setMaximumSize(button_size);

    // Connect buttons
    connect(&_buttonKill  , SIGNAL(clicked()), this, SLOT(killSpiedBlock())       );
    connect(&_buttonCreate, SIGNAL(clicked()), this, SLOT(createSonOfSpiedBlock()));

    // Create layout
    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(&_cbSpiedBlock);
    lay->addWidget(&_buttonCreate);
    lay->addWidget(&_buttonKill);
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::killSpiedBlock()
{
   
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::createSonOfSpiedBlock()
{
    
}

/* ============================================================================
 *
 * */
void SpyWidgetFooter::updateValues()
{

}
