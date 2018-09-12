#include <iostream>
#include <string>
#include "card.h"

using namespace std;

Card::Card(string name, int cost, string description) : name{name}, cost{cost}, description{description} {}

Card::~Card() {}

string Card::getName() const{
  return name;
}

int Card::getCost() const{
  return cost;
}

string Card::getDescription() const{
  return description;
}


