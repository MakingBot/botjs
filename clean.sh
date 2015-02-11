#!/bin/bash

BOTJS_DIR=$(pwd)

#
# Build function
#
function clean_project {

    # An argument must be passed
    if [ $# -eq 0 ]; then
        echo "* No arguments provided to clean_project"
        exit 1
    fi
    project_path=$1
    echo "-- $project_path"

    cd $project_path
    if [ -d build ]; then
        rm -r build
    fi

    cd $BOTJS_DIR
}

clean_project core
clean_project block/spy
clean_project block/shell
clean_project block/viewer3d

clean_project block/link_joint
clean_project block/kinasm
clean_project block/robot

echo '-- Clean OK'
