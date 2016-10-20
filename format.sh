#!/bin/bash -e

astyle "*.h" "*.cpp" "*.hpp" -r --options=astylerc
find -name "*.orig" -delete
