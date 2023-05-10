#!/bin/bash

# In order to run this script, open a Terminal session
# to the same directory and type "chmod u+x comprun.sh"
# without the quotes once to update permissions. Then to
# run the script, from the same Terminal type "./comprun.sh"

# this worked for me on MacOS 12.4 Monterey, using SDL2 version 2.24.0

# exit script at first error
set -u -e

# Compile it and output to executable called 'app'
clang++ -std=c++17 -stdlib=libc++ app.cpp other.cpp -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_image -o app

# runs the app
./app