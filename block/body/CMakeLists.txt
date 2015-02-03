CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(body)

INCLUDE(../../cmake/block_common_config.cmake)

# ====================================
# =============== BUILD ==============

# Includes
INCLUDE_DIRECTORIES(
    src
    ${BOTJS_INCLUDE_DIR}
    )

# Headers
SET(PROJECT_HEADER_FILES
    src/BodyBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/BodyBlock.cpp
    )

# Tell CMake to create the library
ADD_LIBRARY(${CMAKE_PROJECT_NAME}
    SHARED
    ${PROJECT_HEADER_FILES}
    ${PROJECT_SOURCE_FILES}
    )

# Link libraries
QT5_USE_MODULES(${CMAKE_PROJECT_NAME}
    Qml
    Gui
    Core
    Widgets
    )

INSTALL(TARGETS ${CMAKE_PROJECT_NAME}   DESTINATION block)
INSTALL(FILES   ${PROJECT_HEADER_FILES} DESTINATION include)
