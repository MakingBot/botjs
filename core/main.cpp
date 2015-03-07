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


    if     ( app.useCfgBot() )
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use bot configuration script" << std::endl;
        #endif

        BotBlock::JsEngine.evalScriptFile( BotBlock::JsEngine.botCfgFilePath() );
    }
    else if( app.useCfgDev() )
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use dev configuration script" << std::endl;
        #endif

        BotBlock::JsEngine.evalScriptFile( BotBlock::JsEngine.devCfgFilePath() );
    }
    else if( app.useCustom() )
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use user script" << std::endl;
        #endif

        BotBlock::JsEngine.evalScriptFile(js_file_path);
    }
    else
    {
        #ifdef BOTJS_CORE_DEBUG_PRINT
        std::cout << "++ Use basic shell script" << std::endl;
        #endif

        BotBlock::JsEngine.eval("core.create('shell', 'shell'); shell.start();");
    }

    #ifdef BOTJS_CORE_DEBUG_PRINT
    // Stop timer
    int elapsed = timer.elapsed();
    std::cout << "++ Configuration done in " << elapsed << " ms" << std::endl << std::endl;
    #endif

    // Start the event loop
    return app.exec();
}
