#ifndef CONSOLETHREAD_HPP
#define CONSOLETHREAD_HPP

#include <QMutex>
#include <QThread>
#include <QVector>
#include <QtGlobal>
#include <QTextStream>
#include <BotEngine.hpp>
#include <QSocketNotifier>

//!
//! The shell thread
//!
class ShellThread : public QThread
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //! \param parent
    //!
    explicit ShellThread(QMutex& mutex, QTextStream& ccout, QObject *parent = 0);

    //!
    //! Javascript engine setter
    //!
    void setJsEngine(QSharedPointer<BotEngine> js_engine) { _jsEngine = js_engine; }

signals:

private slots:

protected:
    //! Pointer on the js engine
    QSharedPointer<BotEngine> _jsEngine;

    //! The module mutex
    QMutex& _mutex;

    //! Out stream text
    QTextStream& _cout;

    //! Command historic
    QVector<QString> _cmdHisto;

    //! FROM QThread
    void run();


    void prompt(const QString& command_line, int cursor_position);

    Qt::Key getNextChar();

    //!
    //! Search for an exact symbol inside the context
    //! \param context
    //! \param symbol
    //! \return a QJSvalue with the found value, null value else
    //!
    static QJSValue searchExactSymbol(const QJSValue& context, const QString& symbol);


    void autocompletion(QString& command_line, int* cursor);

    //!
    //! Get a command line from user input
    //!
    QString getCommandLine();

    //!
    //! Check if the command line is good enought to be evaluated
    //! \param  command_line
    //! \return true if valid
    //!
    bool commandIsValid(const QString& command_line);

    //!
    //! Display the result of the evaluation is needed
    //!
    void displayCommandResult(QJSValue jsvalue);
};

#endif // CONSOLETHREAD_HPP
