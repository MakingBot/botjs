#ifndef CONSOLEMODULE_HPP
#define CONSOLEMODULE_HPP

#include <QDebug>
#include <QMutex>
#include <BotBlock.hpp>
#include <ShellThread.hpp>

//!
//! The ShellBlock class
//!
class ShellBlock : public BotBlock
{
    Q_OBJECT

public:
    //!
    //! Default constructor
    //! \param parent
    //!
    explicit ShellBlock(const QString& name, QObject *parent = 0);

    //! Destructor
    ~ShellBlock();

    //! FROM BotBlock
    void blockInit(QSharedPointer<BotEngine> js_engine);
    
    //! FROM BotBlock
    virtual float getBlockVersion() const { return 1.0; }

    //! FROM BotBlock
    virtual QString getBlockTypeName() const { return QString("spy"); }

    //! FROM BotBlock
    virtual BlockRole getBlockRole() const { return BotBlock::BlockUi; }


    static const char ClearLine[];

    static const char StyleNormal[];
    static const char StyleBold[];
    static const char StyleUnderline[];

    static const char ColorBlack[];
    static const char ColorRed[];
    static const char Colorgreen[];
    static const char ColorYellow[];
    static const char ColorBlue[];
    static const char ColorMagenta[];
    static const char ColorCyan[];
    static const char ColorWhite[];

signals:

public slots:
    //!
    //! Start console event loop in a separate thread
    //!
    QObject* start();

    //!
    //! Stop thread
    //!
    void stop();

    //!
    QObject* log(const QString& message);

    QObject* cl         () { _cout << ClearLine     ; _cout.flush() ; return this; }

    QObject* normal     () { _cout << StyleNormal   ; _cout.flush() ; return this; }
    QObject* bold       () { _cout << StyleBold     ; _cout.flush() ; return this; }
    QObject* underline  () { _cout << StyleUnderline; _cout.flush() ; return this; }

    QObject* black      () { _cout << ColorBlack    ; _cout.flush() ; return this; }
    QObject* red        () { _cout << ColorRed      ; _cout.flush() ; return this; }
    QObject* green      () { _cout << Colorgreen    ; _cout.flush() ; return this; }
    QObject* yellow     () { _cout << ColorYellow   ; _cout.flush() ; return this; }
    QObject* blue       () { _cout << ColorBlue     ; _cout.flush() ; return this; }
    QObject* magenta    () { _cout << ColorMagenta  ; _cout.flush() ; return this; }
    QObject* cyan       () { _cout << ColorCyan     ; _cout.flush() ; return this; }
    QObject* white      () { _cout << ColorWhite    ; _cout.flush() ; return this; }


protected:
    //! The module mutex
    QMutex _mutex;

    //! Out stream text
    QTextStream _cout;

    //! The thread
    ShellThread _thread;
};

#endif // CONSOLEMODULE_HPP
