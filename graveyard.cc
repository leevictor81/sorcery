#include <string>
#include <vector>
#include "graveyard.h"

using namespace std;

Graveyard::Graveyard() {
  this->numOfCards = 0;
}

Graveyard::~Graveyard() {}

void Graveyard::addToGraveyard(string cardName) {
  this->numOfCards++;
  this->graveyard.push_back(cardName);
}

void Graveyard::deleteCard(){
  this->graveyard.pop_back();
  this->numOfCards--;
}

string Graveyard::returnCard() const{
  if (this->numOfCards == 0) {
    throw string("No cards in graveyard");
  } else {
    string cardName = this->graveyard[this->numOfCards - 1];
    return cardName;
  }
}

int Graveyard::size() const {
  return this->numOfCards;
}

