#include <ShellBlock.hpp>


const char ShellBlock::ClearLine[]           = "\033[2K";

const char ShellBlock::StyleNormal[]         = "\033[0m";
const char ShellBlock::StyleBold[]           = "\033[1m";
const char ShellBlock::StyleUnderline[]      = "\033[4m";

const char ShellBlock::ColorBlack[]          = "\033[30m";
const char ShellBlock::ColorRed[]            = "\033[31m";
const char ShellBlock::Colorgreen[]          = "\033[32m";
const char ShellBlock::ColorYellow[]         = "\033[33m";
const char ShellBlock::ColorBlue[]           = "\033[34m";
const char ShellBlock::ColorMagenta[]        = "\033[35m";
const char ShellBlock::ColorCyan[]           = "\033[36m";

const char ShellBlock::ColorWhite[]          = "\033[97m";

/* ============================================================================
 *
 * */
EXPORT_BLOCK(ShellBlock)

/* ============================================================================
 *
 * */
ShellBlock::ShellBlock(const QString& name, QObject *parent)
    : BotBlock(name, parent)
    , _cout(stdout)
    , _thread(_mutex, _cout, this)
{

}

/* ============================================================================
 *
 * */
ShellBlock::~ShellBlock()
{
    stop();
}

/* ============================================================================
 *
 * */
void ShellBlock::blockInit(QSharedPointer<BotEngine> js_engine)
{
    // Define the js engine for the console
    _thread.setJsEngine(js_engine);
}

/* ============================================================================
 *
 * */
QObject* ShellBlock::start()
{
    // Start the thread
    _thread.start(QThread::NormalPriority);

    return this;
}

/* ============================================================================
 *
 * */
void ShellBlock::stop()
{
    // Stop the thread
    _thread.terminate();

    // Join
    _thread.wait();
}

/* ============================================================================
 *
 * */
QObject* ShellBlock::log(const QString& message)
{

    _mutex.lock();
    _cout << message;
    _cout.flush();
    _mutex.unlock();
    return this;
    
}

//*/
