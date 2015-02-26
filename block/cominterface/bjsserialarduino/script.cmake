INCLUDE_DIRECTORIES( block/cominterface/bjsserialarduino )

# Headers
SET(PROJECT_HEADER_FILES
    block/cominterface/bjsserialarduino/BjsSerialArduinoBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/cominterface/bjsserialarduino/BjsSerialArduinoBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets SerialPort) 

# Generation
BOTJS_GENERATE_BLOCK(
    bjsserialarduino
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
