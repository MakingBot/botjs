#!/bin/bash

#
INSTALL_PATH="$HOME/opt/botjs"

# 
BOTJS_DIR=$(pwd)

# Parallel compilation
CPU_NUMBER=4

# Release or Debug
BUILD_TYPE="Release"

#
# Build function
#
function build_cmake_project {

    # An argument must be passed
    if [ $# -eq 0 ]; then
        echo "* No arguments provided to build_project"
        exit 1
    fi
    project_path=$1
    echo ""
    echo "-------------"
    echo "++ $project_path"
    echo "-------------"

    # The argument must be a directory
    if [[ ! -d $project_path ]]; then
        echo "* [$project_path] must be a directory"
        exit 1
    fi
    cd $project_path

    # Check the build directory
    if [ ! -d build ]; then
        mkdir build
    fi
    cd build

    # Cmake execution
    cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    if [ $? -ne 0 ]; then
        echo "* Cmake fail"
        exit 1
    fi

    # make
    make -j$CPU_NUMBER
    if [ $? -ne 0 ]; then
        echo "* Make fail"
        exit 1
    fi

    # install
    make install
    if [ $? -ne 0 ]; then
        echo "* Install fail"
        exit 1
    fi

    cd $BOTJS_DIR
}

# ===================
# === Build steps ===

build_cmake_project core
build_cmake_project block/spy
build_cmake_project block/shell
build_cmake_project block/viewer3d

build_cmake_project block/joint
build_cmake_project block/kinasm
build_cmake_project block/robot

echo '-- Build OK'
