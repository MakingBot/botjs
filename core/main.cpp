//!
//! \file main.hpp
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

#include <BotApp.hpp>
#include <BotBlock.hpp>

//!
//! BotJs main enter point
//!
//! \author [XR]MakingBot ( http://makingbot.fr )
//!
int main(int argc, char *argv[])
{
    #ifdef BOTJS_CORE_DEBUG_PRINT
    std::cout << std::endl;
    std::cout << "===== BOTJS =====" << std::endl;
    std::cout << "++ Initial configuration start" << std::endl;
    // Start timer
    QTime timer;
    timer.start();
    #endif

    // Create the application
    BotApp app(argc, argv);

    // Manage arguments
    QString js_file_path = app.analyzeArguments();

    // If no js script provided start console
    if(js_file_path.isEmpty())
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use user script" << std::endl;
        #endif

        // Default script shell
        BotBlock::JsEngine.eval("core.create('shell', 'shell'); shell.start();");
    }
    else
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use user script" << std::endl;
        #endif

        // Start user script
        BotBlock::JsEngine.evalScriptFile(js_file_path);
    }


    #ifdef BOTJS_CORE_DEBUG_PRINT
    // Stop timer
    int elapsed = timer.elapsed();
    std::cout << "++ Configuration done in " << elapsed << " ms" << std::endl << std::endl;
    #endif

    // Start the event loop
    return app.exec();
}
