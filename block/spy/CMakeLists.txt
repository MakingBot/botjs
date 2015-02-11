CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
INCLUDE(../../cmake/botjs_config.cmake)

# Headers
SET(PROJECT_HEADER_FILES
    src/SpyBlock.hpp
    src/SpyWidget.hpp
    src/SpyWidgetBody.hpp
    src/SpyWidgetHeader.hpp
    src/SpyWidgetFooter.hpp

    src/DoubleLabel.hpp
    src/ViewerQVectornD.hpp
    src/ViewerRealList.hpp
    src/ViewerQMatrix4x4.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/SpyBlock.cpp
    src/SpyWidget.cpp
    src/SpyWidgetBody.cpp
    src/SpyWidgetHeader.cpp
    src/SpyWidgetFooter.cpp

    src/ViewerQVectornD.cpp
    src/ViewerRealList.cpp
    src/ViewerQMatrix4x4.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS )

# Generation
BOTJS_GENERATE_BLOCK(
    spy
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
