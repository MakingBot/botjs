CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
project(project_botjs)
INCLUDE(cmake/botjs_config.cmake)

# === CORE ===

# Includes
INCLUDE_DIRECTORIES( core/app core/block core/type )

# Headers
SET(PROJECT_HEADER_FILES
    core/app/BotApp.hpp
    core/app/BotEngine.hpp
    core/app/CoreBlock.hpp

    core/block/BotBlock.hpp
    core/block/IProperty.hpp
    core/block/LogBuffer.hpp

    core/block/PhysicBlock.hpp

    core/type/QRealList.hpp
    core/type/Type.hpp
    core/type/ShapeData.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    core/main.cpp
    core/app/BotApp.cpp
    core/app/BotEngine.cpp
    core/app/CoreBlock.cpp

    core/block/BotBlock.cpp
    core/type/ShapeData.cpp
    )

# 
# ADD_DEFINITIONS( -DBOTJS_CORE_DEBUG_PRINT )

# Ressources
QT5_ADD_RESOURCES(PROJECT_RCC_FILES rsc/ressources.qrc)

# Tell CMake to create the executable
ADD_EXECUTABLE(botjs
    ${PROJECT_HEADER_FILES}
    ${PROJECT_SOURCE_FILES}
    ${PROJECT_RCC_FILES}
    )

# Link libraries
QT5_USE_MODULES(botjs Qml Gui Core Widgets)

INSTALL(TARGETS botjs                   DESTINATION bin)
INSTALL(FILES   ${PROJECT_HEADER_FILES} DESTINATION include)

# === SHELL ===

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

# === SPY ===

# Includes
INCLUDE_DIRECTORIES( block/spy )

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

# === VIEWER 3D ===

# Includes
INCLUDE_DIRECTORIES( block/viewer3d )

# Headers
SET(PROJECT_HEADER_FILES
    block/viewer3d/Glub.hpp
    block/viewer3d/Viewer.hpp
    block/viewer3d/Viewer3DBlock.hpp
    block/viewer3d/VertexBufferObject.hpp
    
    block/viewer3d/RenderNode.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/viewer3d/Glub.cpp
    block/viewer3d/Viewer.cpp
    block/viewer3d/Viewer3DBlock.cpp
    block/viewer3d/VertexBufferObject.cpp

    block/viewer3d/RenderNode.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Includes
INCLUDE_DIRECTORIES( /usr/include/GL )

# Block link
#SET(PROJECT_DEPENDENT_BLOCKS robot)

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





INCLUDE_DIRECTORIES( block/link_joint )



# Headers
SET(PROJECT_HEADER_FILES
    block/link_joint/JointBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/link_joint/JointBlock.cpp
    )

# Generation
BOTJS_GENERATE_BLOCK(
    joint
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )



# Headers
SET(PROJECT_HEADER_FILES
    block/link_joint/LinkBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/link_joint/LinkBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS joint)

# Generation
BOTJS_GENERATE_BLOCK(
    link
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )



# === KINASM ===

INCLUDE_DIRECTORIES( block/kinasm )

# Headers
SET(PROJECT_HEADER_FILES
    block/kinasm/KinAsmBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/kinasm/KinAsmBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
SET(PROJECT_DEPENDENT_BLOCKS joint link)

# Generation
BOTJS_GENERATE_BLOCK(
    kinasm
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )



# === ROBOT ===

INCLUDE_DIRECTORIES( block/robot )

# Headers
SET(PROJECT_HEADER_FILES
    block/robot/RobotBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/robot/RobotBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS )

# Generation
BOTJS_GENERATE_BLOCK(
    robot
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )
