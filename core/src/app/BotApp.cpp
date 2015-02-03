#include <QDir>
#include <QDebug>
#include <QtGlobal>

#include <cstdlib>
#include <iostream>

#include <BotApp.hpp>
#include <QCommandLineParser>

/* ============================================================================
 *
 * */
BotApp::BotApp(int & argc, char** argv)
    : QApplication(argc, argv)
    , _jsEngine(BotEngine::Create(this))
{
    // Set application attributes
    setApplicationAttributes();

    // Check module directory
    intializeModuleDirectory();

    // Initialize js engine and add it the system module
    intializeJsEnvironment();
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
    QString block_dir = app_dir + QDir::separator() + QString("../block");

    // Set the module directory
    _jsEngine->setBlockLibDirectory(block_dir);
}

/* ============================================================================
 *
 * */
void BotApp::intializeJsEnvironment()
{
    _jsEngine->createBigBlock();
}
