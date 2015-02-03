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

# ==== NOT FOUND ====
IF(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")

MESSAGE("-- ** BotJs Qt Cmake Config not found **")

# ==== FOUND ====
ELSE(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")

MESSAGE("-- BotJs Qt Cmake Config found: ${QT_CMAKE_CONFIG}")

ENDIF(${QT_CMAKE_CONFIG} STREQUAL "QT_CMAKE_CONFIG-NOTFOUND")


MESSAGE("-- BotJs searching includes in $ENV{HOME}/opt")
FIND_PATH( 
    BOTJS_INCLUDE_DIR
    BotBlock.hpp
    PATHS $ENV{HOME}/opt
    )
MESSAGE("-- BotJs found includes: ${BOTJS_INCLUDE_DIR}")



