# ====================================
# =============== BOTJS ==============

FIND_PACKAGE(Botjs REQUIRED)

# Includes
INCLUDE_DIRECTORIES(
    src
    ${BOTJS_INCLUDE_DIR}
    )

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

# For string manipulation
ADD_DEFINITIONS( -DQT_COMPILING_QSTRING_COMPAT_CPP )
