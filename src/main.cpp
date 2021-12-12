// main for the robot game
// replxx is used for input handling
// the input string is passed to the game.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>

#include "repl-handler.h"
#include "replxx.hxx"
#include "toy-robot-game.h"

#define TABLE_WIDTH 5
#define TABLE_HEIGHT 5

// matches for replxx
std::vector<std::string> examples{"PLACE",  "MOVE",   "LEFT",  "RIGHT",
                                  "REPORT", "ROTATE", "NORTH", "SOUTH",
                                  "EAST",   "WEST",   ".exit"};
using cl = replxx::Replxx::Color;
keyword_highlight_t word_color{
    // commands
    {"PLACE", cl::BRIGHTGREEN}, {"MOVE", cl::BRIGHTBLUE},
    {"ROTATE", cl::BRIGHTRED},  {"REPORT", cl::BRIGHTMAGENTA},
    {"LEFT", cl::YELLOW},       {"RIGHT", cl::YELLOW},
    {"NORTH", cl::YELLOW},      {"SOUTH", cl::YELLOW},
    {"EAST", cl::YELLOW},       {"WEST", cl::YELLOW},
    {"exit", cl::GREEN}};
syntax_highlight_t regex_color{
    // numbers
    {"[\\-|+]{0,1}[0-9]+", cl::YELLOW}, // integers
};

int main(int argc_, char **argv_) {

  // create a game instance, inject table and robot.
  ToyRobotGame::Game game(std::make_shared<ToyRobotGame::Table>(
      TABLE_WIDTH, TABLE_HEIGHT, std::make_shared<ToyRobotGame::Robot>()));

  // init replxx
  replxx::Replxx rx;
  replInit(rx);

  // set the callbacks
  using namespace std::placeholders;
  rx.set_completion_callback(
      std::bind(&hook_completion, _1, _2, cref(examples), true));
  rx.set_highlighter_callback(
      std::bind(&hook_color, _1, _2, cref(regex_color), cref(word_color)));
  rx.set_hint_callback(std::bind(&hook_hint, _1, _2, _3, cref(examples), true));

  // display initial welcome message
  std::cout << "Welcome to toy-robot\n"
            << "Press 'tab' to view autocompletions\n"
            << "Commands: \n"
            << "    PLACE X,Y,[NORTH|SOUTH|EAST|WEST]\n"
            << "    MOVE\n"
            << "    ROTATE [LEFT|RIGHT]\n"
            << "    REPORT\n"
            << ".exit' to exit\n\n";

  std::string prompt = "\x1b[1;32mtoy-robot\x1b[0m> ";

  // this is the repl loop.
  for (;;) {
    char const *cinput{nullptr};

    do {
      cinput = rx.input(prompt);
    } while ((cinput == nullptr) && (errno == EAGAIN));

    // no input - interrupt.
    if (cinput == nullptr) {
      break;
    }

    std::string input{cinput};

    if (!input.empty()) {
      if (input.compare(0, 5, ".exit") == 0) {
        break;
      } else {
        rx.history_add(input);

        // pass the input to the game.
        game.doCommandString(input);
      }
    }
  }

  std::cout << "\nExiting toy-robot\n";

  return 0;
}