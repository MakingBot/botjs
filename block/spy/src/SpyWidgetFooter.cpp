#include <SpyWidgetFooter.hpp>

#include <QHBoxLayout>

/* ============================================================================
 *
 * */
SpyWidgetFooter::SpyWidgetFooter(QWidget *parent)
    : QWidget(parent)
{
    // Configure buttons
    
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
