CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
INCLUDE(../../cmake/botjs_config.cmake)

# Headers
SET(PROJECT_HEADER_FILES
    src/LinkBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/LinkBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS joint)

# Generation
BOTJS_GENERATE_BLOCK(
    link
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )

# Headers
SET(PROJECT_HEADER_FILES
    src/JointBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/JointBlock.cpp
    )

# Generation
BOTJS_GENERATE_BLOCK(
    joint
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
