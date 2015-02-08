# ====================================
# =============== BUILD ==============

SET( CMAKE_EXE_LINKER_FLAGS     "${CMAKE_EXE_LINKER_FLAGS} -Wl,-E" )

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
