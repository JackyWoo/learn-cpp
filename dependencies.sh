#!/bin/bash

cmake --graphviz=cmake-build-debug/dependencies.dot -B cmake-build-debug
dot -Tpng -o dependencies.png  cmake-build-debug/dependencies.dot