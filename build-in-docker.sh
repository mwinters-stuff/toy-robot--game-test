#!/usr/bin/env bash
docker build  -t robot-game .devcontainer/

docker run \
  -it \
  --rm \
  -host\
  -v $(pwd):/workspaces/toy-robot-game \
  -u=$UID\
  -w="/workspaces/toy-robot-game"\
  robot-game \
  ./build.sh

