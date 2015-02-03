#include <QDrag>
#include <QEvent>
#include <QMimeData>
#include <BlockMenuItem.hpp>

/* ============================================================================
 *
 * */
MenuItem::MenuItem(const QString& block_name, QWidget* parent)
    : QLabel(block_name, parent), _blockName(block_name)
{
    // To catch custom user event
    installEventFilter(this);

    // Fixe size
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Define style
    setStyleSheet("QLabel{ background-color: #FFFFFF; font: bold 14px; border: 1px solid gray; }");


    setAlignment(Qt::AlignCenter);

}

/* ============================================================================
 *
 * */
bool MenuItem::eventFilter(QObject *object, QEvent *event)
{
    // Enter / Leave
    if(event->type()==QEvent::Enter)
    {
        setCursor(Qt::OpenHandCursor);
        // _tagHover = true;
        // _brightPtr->start();
    }
    if(event->type()==QEvent::Leave)
    {
        setCursor(Qt::ArrowCursor);

        // _tagHover = false;
        // _fadePtr->start();
    }

    return QLabel::eventFilter(object, event);
}

/* ============================================================================
 *
 * */
QSize MenuItem::sizeHint() const
{
    return QSize(100, 30);
}

/* ============================================================================
 *
 * */
void MenuItem::mouseMoveEvent ( QMouseEvent * event )
{
    QDrag *drag = new QDrag( this );
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    mime->setText ( _blockName );

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

/* ============================================================================
 *
 * */
void MenuItem::mousePressEvent(QMouseEvent* event)
{
    setCursor(Qt::ClosedHandCursor);
}

/* ============================================================================
 *
 * */
void MenuItem::mouseReleaseEvent(QMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);
}
