#!/bin/sh

# === CONSTANTES ===

# Cmake output file name
cmakeof="CMakeLists.txt"

# Build script output file name
buildof="build.sh"

# === VARIABLES ===

# flag dev/bot
flag_dev=0
flag_bot=0

# list of block
block_list=""

# flag debug/release
flag_debug=0
flag_release=0

# paths to qt5 cmake
qt_cmake_path=""

# install prefix
prefix="$HOME/opt"

# === FUNCTIONS ===

# Usage info
show_help() {
cat << EOF
Usage: ${0##*/} [-h] [--dev | --bot --block=BLOCK_LIST] [--debug | --release] [--qt_cmake=PATH]

    -h                      display this help and exit

    -j                      number of threads used to compile

    --rpi                   create an raspbian linux image with pre-installed libs

    --dev                   build core and all blocks
    --bot                   build core and only block provided by --block
    --block     BLOCK_LIST  list of blocks that has to be built

    --debug                 compile core and blocks with debug flags
    --release               compile core and blocks with release flags

    --qt_cmake  PATH        path to the qt cmake directory

EOF
}

# To build the CMakeLists.txt
build_cmakelists() {

}

# To build the build.sh and clean.sh
build_buildclean() {

}

# To build a raspbian image with qt and config script
build_rpiimg() {

}

# === PROCEDURE ===

# --- Parse arguments

while [ "$#" -gt 0 ]; do
    case $1 in
    

    esac
    shift
done

# --- Build CMakeLists.txt

echo "CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)"                                   >  $cmakeof
echo "PROJECT(project_botjs)"                                                   >> $cmakeof

echo -e "\n\n"                                                                  >> $cmakeof

echo "SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $qt_cmake_path)"               >> $cmakeof

# Debug/Release check
if $flag_debug
    then
    if $flag_release
        then
        echo "Error: cannot set debug and release flags in the configuration"
        exit(1);
    fi
fi

# Append debug flag
if $flag_debug
    then
    echo "SET(CMAKE_CXX_FLAGS_DEBUG \"${CMAKE_CXX_FLAGS_DEBUG} -Wall\")"        >> $cmakeof
fi

# Append release flag
if $flag_release
    then
    echo "SET(CMAKE_CXX_FLAGS_RELEASE \"${CMAKE_CXX_FLAGS_RELEASE} -Wall\")"    >> $cmakeof
    echo "ADD_DEFINITIONS( -DQT_NO_DEBUG_OUTPUT )"                              >> $cmakeof
fi



# Search for BotJs Install
# MESSAGE("-- BotJs searching includes in $ENV{HOME}/opt")
# FIND_PATH( 
#     BOTJS_INCLUDE_DIR
#     BotBlock.hpp
#     PATHS $ENV{HOME}/opt
#     )
# MESSAGE("-- BotJs found includes: ${BOTJS_INCLUDE_DIR}")




# --- Build.sh

echo "#!/bin/bash"                                                              >  $buildof

echo "# Parallel compilation"                                                   >> $buildof
echo "CPU_NUMBER=16"                                                            >> $buildof

echo "# Create build directory"                                                 >> $buildof
echo "mkdir build"                                                              >> $buildof
echo "cd build"                                                                 >> $buildof

# Execute cmake
cmake -DCMAKE_INSTALL_PREFIX=$prefix/botjs ..

# Make and install
make -j$CPU_NUMBER
make install


# End of file
