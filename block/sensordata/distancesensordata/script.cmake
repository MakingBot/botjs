INCLUDE_DIRECTORIES( block/sensordata/distancesensordata )

# Headers
SET(PROJECT_HEADER_FILES
    block/sensordata/distancesensordata/DistanceSensorDataBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/sensordata/distancesensordata/DistanceSensorDataBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets) 

# Generation
BOTJS_GENERATE_BLOCK(
    distancesensordata
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
