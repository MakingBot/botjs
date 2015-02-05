#include <QDir>
#include <QDebug>
#include <QtGlobal>
#include <QProxyStyle>
#include <QFontDatabase>

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
    _jsEngine->setBlockLibDirectory(block_lib);
    _jsEngine->setBlockLogDirectory(block_log);
}

/* ============================================================================
 *
 * */
void BotApp::intializeJsEnvironment()
{
    _jsEngine->createBigBlock();
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
