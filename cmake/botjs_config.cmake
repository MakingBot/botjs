# =============================================================================
# Environment configuration
#

# Search for Qt config
MESSAGE("-- BotJs searching Qt Cmake Config")
FIND_PATH(  
    QT_CMAKE_CONFIG
    Qt5WidgetsConfig.cmake
    PATHS
    $ENV{HOME}/Qt/5.4/*/lib/cmake/Qt5Widgets
    /opt/Qt/5.4/*/lib/cmake/Qt5Widgets
    /opt/Qt5.4/5.4/*/lib/cmake/Qt5Widgets
    )
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_CMAKE_CONFIG})

# Check Qt config
IF(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")
    MESSAGE( SEND_ERROR "BotJs Qt Cmake Config not found !!!")
ELSE(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")
    MESSAGE( STATUS "BotJs Qt Cmake Config found: ${QT_CMAKE_CONFIG}")
ENDIF(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")

# Search for BotJs Install
MESSAGE("-- BotJs searching includes in $ENV{HOME}/opt")
FIND_PATH( 
    BOTJS_INCLUDE_DIR
    BotBlock.hpp
    PATHS $ENV{HOME}/opt
    )
MESSAGE("-- BotJs found includes: ${BOTJS_INCLUDE_DIR}")

# Include DIRECTORY
IF(${BOTJS_INCLUDE_DIR} STREQUAL "BOTJS_INCLUDE_DIR-NOTFOUND")

    INCLUDE_DIRECTORIES( src )
    
ELSE(${BOTJS_INCLUDE_DIR} STREQUAL "BOTJS_INCLUDE_DIR-NOTFOUND" )
    
    INCLUDE_DIRECTORIES( src ${BOTJS_INCLUDE_DIR})

ENDIF(${BOTJS_INCLUDE_DIR} STREQUAL "BOTJS_INCLUDE_DIR-NOTFOUND")



# =============================================================================
# Qt configuration
#

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

# Find the Qt libraries
FIND_PACKAGE(Qt5Widgets REQUIRED)

# =============================================================================
# Compiler parameters
#

# Compile flag for C++11
LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x")

SET(CMAKE_BUILD_TYPE "Release")

# Release or debug
MESSAGE("== COMPILE MODE: " ${CMAKE_BUILD_TYPE})
IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
    ADD_DEFINITIONS( -DQT_NO_DEBUG_OUTPUT )
ELSE(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
ENDIF(${CMAKE_BUILD_TYPE} STREQUAL "Release")

# For string manipulation
ADD_DEFINITIONS( -DQT_COMPILING_QSTRING_COMPAT_CPP )

# =============================================================================
# Function to generate a block
#
FUNCTION(BOTJS_GENERATE_BLOCK
    BLOCK_NAME
    BLOCK_HEADER_FILES
    BLOCK_SOURCE_FILES
    BLOCK_QT_MODULES
    BLOCK_DEPENDENT_BLOCKS
    )

    # Define project name
    IF  ( ${BLOCK_NAME} )
        MESSAGE( SEND_ERROR "Block name must be just a string: BOTJS_GENERATE_BLOCK( block_name .... )" )
    ELSE( ${BLOCK_NAME} )
        # PROJECT(${BLOCK_NAME})
        MESSAGE("==========> ${BLOCK_NAME} <==========")
    ENDIF()

    # Tell CMake to create the library
    ADD_LIBRARY(${BLOCK_NAME}
        SHARED
        ${${BLOCK_HEADER_FILES}}
        ${${BLOCK_SOURCE_FILES}}
        )

    # Link Qt Modules
    IF  ( ${BLOCK_QT_MODULES} )
        QT5_USE_MODULES(${BLOCK_NAME} ${${BLOCK_QT_MODULES}} )
    ELSE( ${BLOCK_QT_MODULES} )
        MESSAGE( SEND_ERROR "BLOCK_QT_MODULES must be a list: ${BLOCK_QT_MODULES}" )
    ENDIF(${BLOCK_QT_MODULES} )

    # Dependent block link
    IF  ( ${BLOCK_DEPENDENT_BLOCKS} )

        FOREACH(BLOCK ${${BLOCK_DEPENDENT_BLOCKS}})
            TARGET_LINK_LIBRARIES(${BLOCK_NAME} ${BLOCK})
        ENDFOREACH(BLOCK)
    
    ELSE( ${BLOCK_DEPENDENT_BLOCKS} )
        MESSAGE( STATUS "No dependent block" )
    ENDIF()

    # Installation
    INSTALL(TARGETS ${BLOCK_NAME}            DESTINATION block)
    INSTALL(FILES   ${${BLOCK_HEADER_FILES}} DESTINATION include)

ENDFUNCTION(BOTJS_GENERATE_BLOCK)



