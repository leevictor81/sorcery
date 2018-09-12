#ifndef _CARD_H_
#define _CARD_H_
#include <iostream>
#include <string>
#include "ascii_graphics.h"

class Owner;

class Card {
  std::string name;
  int cost;
  std::string description;
  bool isPlayed = false;
 public:
   Card(std::string name, int cost, std::string description);
   std::string getName() const;
   int getCost() const;
   std::string getDescription() const;
   virtual ~Card();
   virtual void play(Owner* me, Owner* opponent) = 0;
   virtual void play(int fieldIndex, Owner* player) = 0;
   virtual card_template_t makeTemplate() const = 0;
};

#endif

