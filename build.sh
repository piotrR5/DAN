#!/bin/bash
echo -e "[build.sh]  \033[1;37mcompiling\033[0m"
g++ src/DAN.cpp src/ui.cpp src/core.cpp -o dan -Wall
if [  -f dan ]; then
    echo -e "[build.sh]  \033[0;32mcompilation succesfull\033[0m"
else
    echo -e "[build.sh]  \033[0;31mcompilation failed, aborting\033[0m"
    exit 0
fi
echo done
