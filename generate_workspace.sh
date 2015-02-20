#!/bin/bash




mkdir workspace
cd workspace
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 ..

#-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE
