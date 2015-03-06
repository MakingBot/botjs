
INCLUDE_DIRECTORIES( block/robot )

# Headers
SET(PROJECT_HEADER_FILES
    block/robot/RobotBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/robot/RobotBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
SET(PROJECT_DEPENDENT_BLOCKS kinasm)

# Generation
BOTJS_GENERATE_BLOCK(
    robot
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
