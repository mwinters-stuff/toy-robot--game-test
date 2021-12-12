#!/usr/bin/env bash

docker run \
  -it \
  --rm \
  -host\
  -v $(pwd):/workspaces/toy-robot-game \
  -u=$UID\
  -w="/workspaces/toy-robot-game" \
  robot-game \
  ./build/toy-robot-game-tests

