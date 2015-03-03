# Includes
INCLUDE_DIRECTORIES( block/spy block/spy/viewer )

# Headers
SET(PROJECT_HEADER_FILES
    block/spy/SpyBlock.hpp
    block/spy/SpyWidget.hpp
    block/spy/SpyWidgetBody.hpp
    block/spy/SpyWidgetHeader.hpp
    block/spy/SpyWidgetFooter.hpp

    block/spy/DoubleLabel.hpp
    block/spy/ViewerQVectornD.hpp
    block/spy/ViewerRealList.hpp
    block/spy/ViewerQMatrix4x4.hpp

    block/spy/ViewerIProperty.hpp

    block/spy/viewer/SetButton.hpp

    block/spy/viewer/ViewerInteger.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/spy/SpyBlock.cpp
    block/spy/SpyWidget.cpp
    block/spy/SpyWidgetBody.cpp
    block/spy/SpyWidgetHeader.cpp
    block/spy/SpyWidgetFooter.cpp

    block/spy/ViewerQVectornD.cpp
    block/spy/ViewerRealList.cpp
    block/spy/ViewerQMatrix4x4.cpp

    block/spy/viewer/ViewerInteger.cpp
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
