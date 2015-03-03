#include "BlockMenuItem.hpp"

#include <QDrag>
#include <QEvent>
#include <QMimeData>

/* ============================================================================
 *
 * */
BlockMenuItem::BlockMenuItem(const QString& block_name, const int hue, QWidget* parent)
    : QLabel(block_name, parent), _blockName(block_name)
{
    // To catch custom user event
    installEventFilter(this);

    // Fixe size
    const QSize bsize(80,80);
    setMinimumSize(bsize);
    setMaximumSize(bsize);

    // Compute color
    QColor color;
    color.setHsv( hue, 89, 242 );

    // Define style
    QString style = QString("QLabel { background-color: ") +  color.name() +
                    QString("; font: 14px Roboto ;  }"); //border: 2px solid #666666;
    setStyleSheet( style );

    // Align
    setAlignment(Qt::AlignCenter);
}

/* ============================================================================
 *
 * */
bool BlockMenuItem::eventFilter(QObject *object, QEvent *event)
{
    // Enter / Leave
    if(event->type()==QEvent::Enter)
    {
        setCursor(Qt::OpenHandCursor);
    }
    if(event->type()==QEvent::Leave)
    {
        setCursor(Qt::ArrowCursor);
    }
    return QLabel::eventFilter(object, event);
}

/* ============================================================================
 *
 * */
void BlockMenuItem::mouseMoveEvent ( QMouseEvent * event )
{
    Q_UNUSED(event);

    // Prepare the drag
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
void BlockMenuItem::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}

/* ============================================================================
 *
 * */
void BlockMenuItem::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}
