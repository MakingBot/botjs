#!/bin/bash

# Installation path
INSTALL_PATH="$HOME/opt/botjs"

# Parallel compilation
CPU_NUMBER=16

# Release or Debug
BUILD_TYPE="Debug"

# === BUILD ===

# Create build directory
mkdir build
cd build

# Execute cmake
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Make and install
make -j$CPU_NUMBER
make install
