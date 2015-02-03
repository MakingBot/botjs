CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(robot)

# ====================================
# =============== PARAM ==============

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/module/")

# ====================================
# =============== BOTJS ==============

FIND_PACKAGE(Botjs REQUIRED)

# ====================================
# =============== QT 5 ===============

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

# Find the Qt libraries
FIND_PACKAGE(Qt5Widgets REQUIRED)

# ====================================
# =============== PARAM ==============

# Compile flag for C++11
LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x")

MESSAGE("== COMPILE MODE: " ${CMAKE_BUILD_TYPE})

# ==== Release ====
IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
    ADD_DEFINITIONS( -DQT_NO_DEBUG_OUTPUT )

# ==== Debug ====
ELSE(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

ENDIF(${CMAKE_BUILD_TYPE} STREQUAL "Release")

# ====================================
# =============== BUILD ==============

# Includes
INCLUDE_DIRECTORIES(
    src
    ${BOTJS_INCLUDE_DIR}
    )

# Headers
SET(PROJECT_HEADER_FILES
    src/RobotBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/RobotBlock.cpp
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
