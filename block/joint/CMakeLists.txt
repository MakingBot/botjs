CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(joint)

# ====================================
# =============== BUILD ==============

# Headers
SET(PROJECT_HEADER_FILES
    src/JointBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/JointBlock.cpp
    )

# Call common configs
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/module/")
INCLUDE(../../cmake/common_config.cmake)
INCLUDE(../../cmake/block_common_config.cmake)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
    /home/rodriguez/opt/botjs/block/liblink.so
    )
