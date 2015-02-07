CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(botjs)

# Includes
INCLUDE_DIRECTORIES(
    src/app
    src/block
    )

# Headers
SET(PROJECT_HEADER_FILES
    src/block/BotBlock.hpp
    src/block/IProperty.hpp
    src/block/LogBuffer.hpp
    src/block/LogBuffer.cpp
    
    src/app/BotApp.hpp
    src/app/BotEngine.hpp
    src/app/CoreBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/main.cpp
    src/app/BotApp.cpp
    src/app/BotEngine.cpp
    src/app/CoreBlock.cpp
    )

ADD_DEFINITIONS( -DBOTJS_CORE_DEBUG_PRINT )

# Call common configs
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/module/")
INCLUDE(../cmake/common_config.cmake)

QT5_ADD_RESOURCES(PROJECT_RCC_FILES rsc/ressources.qrc)

INCLUDE(../cmake/app_common_config.cmake)
