#include <BotApp.hpp>

//!
//! BotJs main enter point
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
int main(int argc, char *argv[])
{
    // Log
    std::cout << std::endl;
    std::cout << "===== BOTJS =====" << std::endl;
    std::cout << "++ Initial configuration start" << std::endl;

    // Start timer
    QTime timer;
    timer.start();

    // Create the application
    BotApp app(argc, argv);

    // Manage arguments
    QString js_file_path = app.analyzeArguments();

    // If no js script provided start console
    if(js_file_path.isEmpty())
    {
        app.js()->eval("");
    }
    else
    {
        app.js()->evalScriptFile(js_file_path);
    }

    // Stop timer
    int elapsed = timer.elapsed();

    // Log
    std::cout << "++ Configuration done in " << elapsed << " ms" << std::endl << std::endl;

    // Start the event loop
    return app.exec();
}
