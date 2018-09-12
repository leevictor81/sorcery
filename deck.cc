#include <string>
#include <iostream>
#include <vector>
#include "deck.h"

using namespace std;

Deck::Deck() {
  numOfCards = 0;
}

Deck::~Deck() {}

string Deck::draw() {
  if (this->numOfCards == 0) {
    throw string("NoCards");
  } else {
    string cardName = this->deck[0];
    this->deck.erase(this->deck.begin());
    this->numOfCards--;
    return cardName;
  }
}

void Deck::shuffle() {
  if (this->numOfCards > 1) {
    for (int i = 1; i < this->numOfCards ; i++) {
      swap(this->deck[i], this->deck[rand() % i]);
    }
  }
}

void Deck::putToBottom(string cardName) {
  this->deck.push_back(cardName);
  this->numOfCards++;
}

int Deck::size() const {
  return this->numOfCards;
}

