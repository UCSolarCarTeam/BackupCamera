#!/bin/bash -e

astyle "src/*.h" "src/*.cpp" "src/*.hpp" -r --options=astylerc
find -name "*.orig" -delete
