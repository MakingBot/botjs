CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
INCLUDE(../../cmake/botjs_config.cmake)

# Headers
SET(PROJECT_HEADER_FILES
    src/Glub.hpp
    src/Viewer.hpp
    src/Viewer3DBlock.hpp
    src/VertexBufferObject.hpp
    
    src/RenderNode.hpp
    src/RenderNodeLink.hpp
    src/RenderNodeRobot.hpp
    src/RenderNodeJoint.hpp
    src/RenderNodeKinAsm.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/Glub.cpp
    src/Viewer.cpp
    src/Viewer3DBlock.cpp
    src/VertexBufferObject.cpp

    src/RenderNode.cpp
    
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Includes
INCLUDE_DIRECTORIES( /usr/include/GL )

# Block link
SET(PROJECT_DEPENDENT_BLOCKS robot)

# Generation
BOTJS_GENERATE_BLOCK(
    viewer3d
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )

# Link libraries
QT5_USE_MODULES( viewer3d OpenGL )
TARGET_LINK_LIBRARIES(viewer3d GLU )

