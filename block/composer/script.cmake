INCLUDE_DIRECTORIES( block/composer )

# Headers
SET(PROJECT_HEADER_FILES
    block/composer/BlockMenu.hpp
    block/composer/BlockMenuItem.hpp
        
    block/composer/BlockViewMode.hpp

    block/composer/ComposerBlock.hpp
    block/composer/ComposerWidget.hpp

    block/composer/GraphicsLinkItem.hpp
    block/composer/GraphicsBlockItem.hpp
    
    block/composer/GraphicsBlockView.hpp
    block/composer/GraphicsBlockScene.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/composer/BlockMenu.cpp
    block/composer/BlockMenuItem.cpp

    block/composer/ComposerBlock.cpp
    block/composer/ComposerWidget.cpp

    block/composer/GraphicsLinkItem.cpp
    block/composer/GraphicsBlockItem.cpp
    block/composer/GraphicsBlockView.cpp
    block/composer/GraphicsBlockScene.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets Svg) 

# Generation
BOTJS_GENERATE_BLOCK(
    composer
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )


