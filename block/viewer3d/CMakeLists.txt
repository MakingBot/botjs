CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(viewer3d)

# ====================================
# =============== BUILD ==============

# Includes
INCLUDE_DIRECTORIES( /usr/include/GL )

# Headers
SET(PROJECT_HEADER_FILES
    src/Glub.hpp
    src/Viewer.hpp
    src/Viewer3DBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/Glub.cpp
    src/Viewer.cpp
    src/Viewer3DBlock.cpp
    )

# Call common configs
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/module/")
INCLUDE(../../cmake/common_config.cmake)
INCLUDE(../../cmake/block_common_config.cmake)

# Link libraries
QT5_USE_MODULES(${CMAKE_PROJECT_NAME}
    OpenGL
    )
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} GLU )

