[![CMake](https://github.com/mwinters-stuff/toy-robot-game-test/actions/workflows/cmake.yml/badge.svg)](https://github.com/mwinters-stuff/toy-robot-game-test/actions/workflows/cmake.yml)

# toy-robot-game-test

## Build Instructions


### Docker

To build and run in docker, the following scripts can be used.
```
./build-in-docker.sh
./run-game-in-docker.sh
./run-tests-in-docker.sh
```
If running windows, and docker-desktop is installed to use WSL2, the following scripts can be used
```
./build-in-docker.cmd
./run-game-in-docker.cmd
./run-tests-in-docker.cmd
```

### Linux

```
./build.sh
```

## Running tests
``` 
./build/robot-test-tests
```
or
```
./run-tests-in-docker.sh
```

## Playing game
```
./build/robot-test
```
or 
```
./run-game-in-docker.sh
```

### Game commands
* PLACE x,y,direction

  Places robot on table, at location `x`, `y` and facing `NORTH|EAST|SOUTH|WEST`

* MOVE

  Moves the robot one step in the direction it is facing.

* ROTATE LEFT|RIGHT

  Rotates the robot `LEFT` or `RIGHT` so it is facing a new direction.

* REPORT

  Reports the robots current position.


## Editing in VSCODE

The project is setup to use a devcontainer with all requirements installed. Upon
opening the folder for the first time, vscode will ask to open in the devcontainer
you should answer "yes" and it will build the container and install the required
plugins.

From there you can use the cmake extension to set build and debug targets
and the test extension will show the tests in the test explorer.



