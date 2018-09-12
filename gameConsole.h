#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H
#include <string>
#include "window.h"

class GameConsole{
  Owner player1{true};
  Owner player2{false};
public:
  GameConsole();
  ~GameConsole();
  void initializeDeck1(std::istream &deckStream);
  void initializeDeck2(std::istream &deckStream);
  void game(bool deck1, bool deck2, bool n1, bool n2, std::string name1, std::string name2, bool testing, bool bonus, std::string input);
};

#endif

