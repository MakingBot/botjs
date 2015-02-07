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

private:
    //!
    //! Set application attributes: name, version...
    //!
    inline void setApplicationAttributes();

    //!
    //! Add module directory to the dynamic search path of Qt
    //!
    inline void intializeModuleDirectory();

    //!
    //! Initialize js engine and first prime modules
    //!
    inline void intializeJsEnvironment();

    //!
    //! Set the tweaks style to create modern ui
    //! Avoid orange focus on ubuntu
    //!
    inline void setTweaksStyle();
};

#endif // BOTAPP_HPP
