CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
project(botjs)
INCLUDE(../cmake/botjs_config.cmake)


# Includes
INCLUDE_DIRECTORIES(
    src/app
    src/block
    src/type
    )

# Headers
SET(PROJECT_HEADER_FILES
    src/app/BotApp.hpp
    src/app/BotEngine.hpp
    src/app/CoreBlock.hpp

    src/block/BotBlock.hpp
    src/block/IProperty.hpp
    src/block/LogBuffer.hpp

    src/block/PhysicBlock.hpp

    src/type/QRealList.hpp
    src/type/Type.hpp
    src/type/ShapeData.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    src/main.cpp
    src/app/BotApp.cpp
    src/app/BotEngine.cpp
    src/app/CoreBlock.cpp

    src/block/BotBlock.cpp
    src/type/ShapeData.cpp
    )

# 
# ADD_DEFINITIONS( -DBOTJS_CORE_DEBUG_PRINT )

# Ressources
QT5_ADD_RESOURCES(PROJECT_RCC_FILES rsc/ressources.qrc)

# Tell CMake to create the executable
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
    ${PROJECT_HEADER_FILES}
    ${PROJECT_SOURCE_FILES}
    ${PROJECT_RCC_FILES}
    )

# Link libraries
QT5_USE_MODULES(${CMAKE_PROJECT_NAME}
    Qml
    Gui
    Core
    Widgets
    )

INSTALL(TARGETS ${CMAKE_PROJECT_NAME}   DESTINATION bin)
INSTALL(FILES   ${PROJECT_HEADER_FILES} DESTINATION include)
