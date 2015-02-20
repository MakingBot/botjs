# Includes
INCLUDE_DIRECTORIES( core/app core/block core/type )

# Headers
SET(PROJECT_HEADER_FILES
    core/app/BotApp.hpp
    core/app/BotEngine.hpp
    core/app/CoreBlock.hpp

    core/block/BotBlock.hpp
    core/block/GuiBlock.hpp
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

ADD_DEFINITIONS( -DBOTJS_CORE_DEBUG_PRINT )

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
