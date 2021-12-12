REM capture the path to $0 ie this script
set mypath=%~dp0

docker run -it --rm -host -v %mypath%:/workspaces/toy-robot-game -u=1000 -w="/workspaces/toy-robot-game"  robot-game  ./build/toy-robot-game-tests
