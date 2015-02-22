INCLUDE_DIRECTORIES( block/link block/joint )

# Headers
SET(PROJECT_HEADER_FILES
    block/link/LinkBlock.hpp
    block/joint/JointBlock.hpp
    )

# Sources
SET(PROJECT_SOURCE_FILES
    block/link/LinkBlock.cpp
    block/joint/JointBlock.cpp
    )

# Qt Modules
SET(PROJECT_USED_QT_MODULE Qml Gui Core Widgets)

# Block link
# SET(PROJECT_DEPENDENT_BLOCKS joint)

ADD_DEFINITIONS( -DJOINT_BUILD )

# Generation
BOTJS_GENERATE_BLOCK(
    link
    PROJECT_HEADER_FILES
    PROJECT_SOURCE_FILES
    PROJECT_USED_QT_MODULE
    PROJECT_DEPENDENT_BLOCKS
    )