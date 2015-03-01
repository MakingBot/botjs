INCLUDE_DIRECTORIES( block/controller/bjsushcsr04ctrl )

# Headers
SET(PROJECT_HEADER_FILES
    block/controller/bjsushcsr04ctrl/BjsUsHCSR04CtrlBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/controller/bjsushcsr04ctrl/BjsUsHCSR04CtrlBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets) 

# Generation
BOTJS_GENERATE_BLOCK(
    bjsushcsr04ctrl
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
