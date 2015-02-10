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





# #
# # Function to generate a block
# #
# FUNCTION(BOTJS_GENERATE_BLOCK
#     B_NAME
#     B_HEADER_FILES
#     B_SOURCE_FILES
#     B_LINK
#     )

#     # Define project name
#     PROJECT(${${B_NAME}}) 

#     # Tell CMake to create the library
#     ADD_LIBRARY(${CMAKE_PROJECT_NAME}
#         SHARED
#         ${${B_HEADER_FILES}}
#         ${${B_SOURCE_FILES}}
#         )

#     # Link Qt Modules
#     QT5_USE_MODULES(${CMAKE_PROJECT_NAME}
#         Qml
#         Gui
#         Core
#         Widgets
#         )

#     # # Install config
#     # TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
#     #     ${CMAKE_INSTALL_PREFIX}/block/liblink.so
#     #     )

#     # Install config
#     INSTALL(TARGETS ${CMAKE_PROJECT_NAME}   DESTINATION block)
#     INSTALL(FILES   ${PROJECT_HEADER_FILES} DESTINATION include)

# ENDFUNCTION(BOTJS_GENERATE_BLOCK)

