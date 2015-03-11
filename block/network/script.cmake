INCLUDE_DIRECTORIES( block/network )

# Headers
SET(PROJECT_HEADER_FILES
    block/network/NetworkBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/network/NetworkBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets) 

# Generation
BOTJS_GENERATE_BLOCK(
    network
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
