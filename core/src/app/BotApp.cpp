//!
//! \file BotApp.cpp
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

#include <QDir>
#include <QDebug>
#include <QtGlobal>
#include <QProxyStyle>
#include <QFontDatabase>

#include <cstdlib>
#include <iostream>

#include <BotApp.hpp>
#include <BotBlock.hpp>
#include <BotEngine.hpp>

#include <QCommandLineParser>

/* ============================================================================
 *
 * */
BotApp::BotApp(int & argc, char** argv)
    : QApplication(argc, argv)
{
    // Set application attributes
    setApplicationAttributes();

    // Check module directory
    intializeModuleDirectory();

    // Initialize js engine and add it the system module
    intializeJsEnvironment();

    // Style
    setTweaksStyle();
}

/* ============================================================================
 *
 * */
QString BotApp::analyzeArguments()
{
    // Prepare the command parser
    QCommandLineParser parser;
    QString description = "\n" + QApplication::applicationName() + ":-)";
    parser.setApplicationDescription(description);

    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("js_file", QApplication::translate("main", "Js file script"));

    // Process the actual command line arguments given by the user
    parser.process(*this);

    // If exist return the js file
    const QStringList args = parser.positionalArguments();
    if(args.size() >= 1)
    {
        return args.at(0);
    }

    // Return empty string
    return QString();
}

/* ============================================================================
 *
 * */
void BotApp::setApplicationAttributes()
{
    QApplication::setApplicationName("Botjs");
    QApplication::setApplicationVersion("1.0");

    QApplication::setOrganizationName("MakingBot");
    QApplication::setOrganizationDomain("makingbot.com");
}

/* ============================================================================
 *
 * */
void BotApp::intializeModuleDirectory()
{
    // Get application directory
    QString app_dir = QCoreApplication::applicationDirPath();

    // Build the module directory path
    QString block_lib = app_dir + QDir::separator() + QString("../block");
    QString block_log = app_dir + QDir::separator() + QString("../log");

    // Set the module directory
    BotBlock::JsEngine.setBlockLibDirectory(block_lib);
    BotBlock::JsEngine.setBlockLogDirectory(block_log);

    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << "++ Initialize path to log  : " << block_log.toStdString() << std::endl;
    std::cout << "++ Initialize path to block: " << block_lib.toStdString() << std::endl;
    #endif
}

/* ============================================================================
 *
 * */
void BotApp::intializeJsEnvironment()
{
    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << "++ Create Core Block" << std::endl;
    #endif

    BotBlock::JsEngine.createCoreBlock();
}

/* ============================================================================
 *
 * */
class Style_tweaks : public QProxyStyle
{
    public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const
    {
        /* do not draw focus rectangles - this permits modern styling */
        if (element == QStyle::PE_FrameFocusRect)
            return;

        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
};

/* ============================================================================
 *
 * */
void BotApp::setTweaksStyle()
{
    // Set tweaks style
    this->setStyle(new Style_tweaks);
}
