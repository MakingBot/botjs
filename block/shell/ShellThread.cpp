#include <ShellBlock.hpp>
#include <ShellThread.hpp>

#include <unistd.h>
#include <termios.h>

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QCoreApplication>

typedef QPair<QString, QJSValue> JsProperty;

/* ============================================================================
 *
 * */
ShellThread::ShellThread(QMutex& mutex, QTextStream& ccout, QObject *parent)
    : QThread(parent)
    , _mutex(mutex)
    , _cout(ccout)
{

}

/* ============================================================================
 *
 * */
void ShellThread::run()
{
    // Configure terminal for unbeffered input
    struct termios old_tio, new_tio;
    // get the terminal settings for stdin
    tcgetattr(STDIN_FILENO,&old_tio);
    // we want to keep the old setting to restore them a the end
    new_tio=old_tio;
    // disable canonical mode (buffered i/o) and local echo
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    // set the new settings immediately
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    // Start console
    while(1)
    {
        // Get a command line
        QString cmd_line = getCommandLine();

        if(commandIsValid(cmd_line))
        {
            _cmdHisto.insert(0, cmd_line);
            if(_cmdHisto.size() > 30)      // pass 30 in parameters 
            {
                _cmdHisto.removeLast();
            }

            // // Debug
            // qDebug() << "++ Try to execute command" << cmd_line;

            displayCommandResult(BotBlock::JsEngine.eval(cmd_line));
        }
    }

    // Restore the former settings
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}

/* ============================================================================
 *
 * */
void ShellThread::prompt(const QString& command_line, int cursor_position)
{
    // Compute VT100 sequence to adjust the cursor position
    QString adjust_cursor;
    int diff = command_line.size() - cursor_position;
    if(diff>0) { adjust_cursor = "\033[" + QString::number(diff) + "D"; }

    // Write cout stream
    _mutex.lock();

    _cout
    << ShellBlock::ClearLine << ShellBlock::StyleBold << ShellBlock::ColorBlue
    << "\r" << QCoreApplication::applicationName() << " >"
    << ShellBlock::StyleNormal << ShellBlock::ColorWhite
    << command_line << adjust_cursor;
    _cout.flush();

    _mutex.unlock();
}

/* ============================================================================
 *
 * */
Qt::Key ShellThread::getNextChar()
{
    // Get char
    char c1 = getchar();

    // while(1)
    // {
    //     char c = getchar();
    //     _cout << '(' << (int)c << ')';
    //     _cout.flush();
    // }

    // Special char arrow
    if(c1 == 27)
    {
        char c2 = getchar();
        if(c2 == 91)
        {
            char c3 = getchar();
            switch(c3)
            {
                case 65:
                    return Qt::Key_Up;
                break;
                case 66:
                    return Qt::Key_Down;
                break;
                case 67:
                    return Qt::Key_Right;
                break;
                case 68:
                    return Qt::Key_Left;
                break;
            }
        }
        return Qt::Key_Escape;
    }

    // Enter end of line
#ifdef WIN32
    if(c1 == 10)
    {
        char c2 = getchar();
        if(c2 == 13)
        {
            return Qt::Key_Enter;
        }
    }
#else
    if(c1 == 10)
    {
        return Qt::Key_Enter;
    }
#endif

    // Others special
    switch(c1)
    {
        case 9:
            return Qt::Key_Tab;
        break;

        case 127:
            return Qt::Key_Backspace;
        break;
    }

    return (Qt::Key)c1;
}

/* ============================================================================
 *
 * */
QJSValue ShellThread::searchExactSymbol(const QJSValue& context, const QString& symbol)
{
    QJSValueIterator it(context);
    while(it.hasNext())
    {
        it.next();
        if(it.name().compare(symbol) == 0)
        {
            return it.value();
        }
    }
    return QJSValue();
}




void objectNameMatch(const QJSValue& context, const QString& symbol, QList<QPair<QString, QJSValue>>& list)
{
    list.clear();

    QJSValueIterator it(context);
    while(it.hasNext())
    {
        it.next();
        if(it.name().midRef(0, symbol.size()).compare(symbol) == 0)
        {
            list.append(QPair<QString, QJSValue>(it.name(), it.value()));
        }
    }
}



/* ============================================================================
 *
 * */
void ShellThread::autocompletion(QString& command_line, int* cursor)
{
    // Initialize context
    QJSValue context = BotBlock::JsEngine.go();

    // Initialize cmd line analysis
    QList<JsProperty> result;
    QStringList command_composition = command_line.split(".");

    // Analyze the command string
    for(int i=0 ; i<command_composition.size() ; i++)
    {
        const QString& object_name = command_composition.at(i);

        if(i < command_composition.size()-1)
        {
            QJSValue value = searchExactSymbol(context, object_name);
            if(!value.isNull())
            {
                context = value;
            }
            else
            {
                return;
            }
        }
        else
        {
            objectNameMatch(context, object_name, result);
            if(result.size() == 0)
            {
                return;
            }
            else if(result.size() == 1)
            {
                QString property_name = result.at(0).first;
                int diff = property_name.size() - object_name.size();
                QStringRef add_str = property_name.midRef(object_name.size(), diff);

                command_line += add_str;
                *cursor += add_str.size();
            }
            else
            {
                _mutex.lock();

                _cout << "\n";
                foreach(JsProperty property, result)
                {   
                    QString adjust_cursor;
                    int diff = 40 - property.first.size(); // TODO pass 40 in parameter
                    if(diff > 0)
                    {
                        adjust_cursor = "\033[" + QString::number(diff) + "C";
                    }

                    _cout << property.first << adjust_cursor << property.second.toString() << "\n";
                }

                _mutex.unlock();
            }
        }
    }
}

/* ============================================================================
 *
 * */
QString ShellThread::getCommandLine()
{
    // Get the line
    bool up = false;
    bool down = false;
    int cursor = 0;
    int histo  = 0;
    Qt::Key key;
    QString cmd_line="";

    do
    {
        // Print line
        prompt(cmd_line, cursor);
        key = getNextChar();

        // Analyse char
        switch(key)
        {
            case Qt::Key_Enter: break; // Stop at the end of the line
            //case '(': cmd_line.insert(cursor, "()"); cursor++; break;
            case Qt::Key_Tab:   autocompletion(cmd_line, &cursor); break;
            case Qt::Key_Up:    if(down) {
                                    histo++;
                                    down = false; }
                                if(!_cmdHisto.isEmpty())
                                    cmd_line=_cmdHisto[histo]; cursor=cmd_line.size();
                                if(histo<_cmdHisto.size()-1) { histo++; }
                                up = true;
            break;
            case Qt::Key_Down:  if(up) {
                                    histo--;
                                    up = false; }
                                if(!_cmdHisto.isEmpty())
                                    cmd_line=_cmdHisto[histo]; cursor=cmd_line.size();
                                if(histo>0) { histo--; }
                                down = true;
            break;
            case Qt::Key_Right: if(cursor<cmd_line.size())  { cursor++; } break;
            case Qt::Key_Backspace: cmd_line.remove(cursor-1, 1); // Care backspace use left :-)
            case Qt::Key_Left:  if(cursor>0)                { cursor--; } break;

            default: cmd_line.insert(cursor, key); cursor++; break;
        }
    }
    while( key != Qt::Key_Enter );

    // Clear and return
    _mutex.lock();
    _cout << "\n"; _cout.flush();
    _mutex.unlock();

    return cmd_line;
}

/* ============================================================================
 *
 * */
bool ShellThread::commandIsValid(const QString& command_line)
{
    // For debug purpose
    // for(int i=0 ; i<command_line.size() ; i++)
    // {
    //     qDebug() << "char" << i << ":" << command_line[i].cell();
    // }

    // Check if the line is not empty
    if(command_line.compare("") == 0 || command_line.isEmpty())
    {
        return false;
    }

    // It is ok else
    return true;
}

/* ============================================================================
 *
 * */
void ShellThread::displayCommandResult(QJSValue jsvalue)
{
    // if(jsvalue.isObject())
    // {
    //     QJsonObject* obj = (QJsonObject*) jsvalue.toQObject() ;
    //     _mutex.lock();
    //     _cout << obj;
    //     _cout.flush();
    //     _mutex.unlock();
    // }

    // Resulat
    if( !jsvalue.isUndefined() )
    {
        _mutex.lock();
        _cout << jsvalue.toString() << endl;
        _mutex.unlock();
    }
}

//*/
