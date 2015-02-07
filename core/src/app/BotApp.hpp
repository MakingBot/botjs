#ifndef BOTAPP_HPP
#define BOTAPP_HPP
//!
//! \file BotApp.hpp
//!
// Copyright 2015 MakingBot
// This file is part of BotJs.
//
// BotJs is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BotJs is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BotJs.  If not, see <http://www.gnu.org/licenses/>.

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
