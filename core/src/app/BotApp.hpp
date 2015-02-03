#ifndef BOTAPP_HPP
#define BOTAPP_HPP

#include <QApplication>
#include <BotEngine.hpp>

#include <QTime>
#include <iostream>

//!
//! Botjs is simply a Qt Application
//!
class BotApp : public QApplication
{
    Q_OBJECT

public:
    //!
    //! Default application
    //! \param argc
    //! \param argv
    //!
    explicit BotApp(int & argc, char** argv);

    //!
    //! Analyze arguments from cmd line
    //! \return the js file path if the user provide it, empty string else
    //!
    QString analyzeArguments();

    //!
    //! Js engine getter
    //!
    QSharedPointer<BotEngine> js() { return _jsEngine; }

signals:

public slots:

private:
    //! Pointer on the js engine
    QSharedPointer<BotEngine> _jsEngine;

    //!
    //! Set application attributes: name, version...
    //!
    void setApplicationAttributes();

    //!
    //! Add module directory to the dynamic search path of Qt
    //!
    void intializeModuleDirectory();

    //!
    //! Initialize js engine and first prime modules
    //!
    void intializeJsEnvironment();

};

#endif // BOTAPP_HPP
