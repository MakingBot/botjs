CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
project(project_botjs)
INCLUDE(cmake/botjs_config.cmake)

# === CORE ===

INCLUDE(core/script.cmake)

# === CONTROLLER ===

INCLUDE(block/controller/bjsushcsr04ctrl/script.cmake)

# === SENSOR-DATA ===

INCLUDE(block/sensordata/distancesensordata/script.cmake)

# === COM-INTERFACE ===

INCLUDE(block/cominterface/bjsserialarduino/script.cmake)

# === SHELL ===

# Includes
INCLUDE_DIRECTORIES( block/shell )

# Headers
SET(PROJECT_HEADER_FILES
    block/shell/ShellBlock.hpp
    block/shell/ShellThread.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/shell/ShellBlock.cpp
    block/shell/ShellThread.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS )

# Generation
BOTJS_GENERATE_BLOCK(
    shell
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )

# === WIDGETS ===

INCLUDE(block/spy/script.cmake)
INCLUDE(block/network/script.cmake)
INCLUDE(block/composer/script.cmake)


# # === VIEWER 3D ===

# # Includes
# INCLUDE_DIRECTORIES( block/viewer3d )

# # Headers
# SET(PROJECT_HEADER_FILES
#     block/viewer3d/Glub.hpp
#     block/viewer3d/Viewer.hpp
#     block/viewer3d/Viewer3DBlock.hpp
#     block/viewer3d/VertexBufferObject.hpp
    
#     block/viewer3d/RenderNode.hpp
#     )

# # Sources
# SET(PROJECT_SOURCE_FILES
#     block/viewer3d/Glub.cpp
#     block/viewer3d/Viewer.cpp
#     block/viewer3d/Viewer3DBlock.cpp
#     block/viewer3d/VertexBufferObject.cpp

#     block/viewer3d/RenderNode.cpp
#     )

# # Qt Modules
# SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# # Includes
# INCLUDE_DIRECTORIES( /usr/include/GL )

# # Block link
# #SET(PROJECT_DEPENDENT_BLOCKS robot)

# # Generation
# BOTJS_GENERATE_BLOCK(
#     viewer3d
#     PROJECT_HEADER_FILES
#     PROJECT_SOURCE_FILES
#     PROJECT_USED_QT_MODULE
#     PROJECT_DEPENDENT_BLOCKS
#     )

# # Link libraries
# QT5_USE_MODULES( viewer3d OpenGL )
# TARGET_LINK_LIBRARIES(viewer3d GLU )



# # === LINK ===
# INCLUDE(block/link/script.cmake)

# # === JOINT ===
# INCLUDE(block/joint/script.cmake)


# # === KINASM ===

# INCLUDE_DIRECTORIES( block/kinasm )

# # Headers
# SET(PROJECT_HEADER_FILES
#     block/kinasm/KinAsmBlock.hpp
#     )

# # Sources
# SET(PROJECT_SOURCE_FILES
#     block/kinasm/KinAsmBlock.cpp
#     )

# # Qt Modules
# SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# # Block link
# SET(PROJECT_DEPENDENT_BLOCKS joint link)

# # Generation
# BOTJS_GENERATE_BLOCK(
#     kinasm
#     PROJECT_HEADER_FILES
#     PROJECT_SOURCE_FILES
#     PROJECT_USED_QT_MODULE
#     PROJECT_DEPENDENT_BLOCKS
#     )



# # === ROBOT ===
# INCLUDE(block/robot/script.cmake)
