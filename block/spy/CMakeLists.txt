CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(spy)

# ====================================
# =============== BUILD ==============

INCLUDE_DIRECTORIES(widget)

# Headers
SET(PROJECT_HEADER_FILES
    src/SpyBlock.hpp
    src/SpyWidget.hpp
    src/SpyWidgetBody.hpp
    src/SpyWidgetHeader.hpp
    src/SpyWidgetFooter.hpp

    src/widget/LogTag.hpp
    src/widget/DoubleLabel.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/SpyBlock.cpp
    src/SpyWidget.cpp
    src/SpyWidgetBody.cpp
    src/SpyWidgetHeader.cpp
    src/SpyWidgetFooter.cpp
    )

# Call common configs
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/module/")
INCLUDE(../../cmake/common_config.cmake)
INCLUDE(../../cmake/block_common_config.cmake)
