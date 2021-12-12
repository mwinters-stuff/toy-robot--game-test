#!/bin/bash

mkdir build
cmake --no-warn-unused-cli \
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
  -DCMAKE_BUILD_TYPE:STRING=Debug \
  -H$(pwd) \
  -B$(pwd)/build \
  -G "Unix Makefiles"
cmake --build build --config Debug --target toy-robot-game -j 18 --
cmake --build build --config Debug --target toy-robot-game-tests -j 18 --