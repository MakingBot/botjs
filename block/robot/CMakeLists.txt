CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
INCLUDE(../../cmake/botjs_config.cmake)

# Headers
SET(PROJECT_HEADER_FILES
    src/RobotBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/RobotBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS )

# Generation
BOTJS_GENERATE_BLOCK(
    robot
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
