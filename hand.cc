#include <iostream>
#include <string>
#include <vector>
#include "hand.h"

using namespace std;

Hand::Hand() {
  this->numOfCards = 0;
}

Hand::~Hand() {}

void Hand::destroyCard(int handIndex){
  if (handIndex <= 5) {
    this->hand.erase(this->hand.begin() + handIndex);
    this->numOfCards--;
  }
}

string Hand::getCardName(int handIndex) const{
  if (handIndex >= this->numOfCards || handIndex < 0) {
    throw string("HandOutOfScope");
  } else {
    return hand[handIndex];
  }
}

void Hand::addCard(string cardName) {
  if (this->numOfCards < 5) {
    this->hand.push_back(cardName);
    numOfCards++;
  } else {
    cout << cardName << " discarded, too many cards in hand" << endl;
  }
}

void Hand::addToPos(std::string cardName, int handIndex){
  if (this->numOfCards < 5) {
    hand.insert(hand.begin() + handIndex, cardName);
    numOfCards++;
  } else {
    cout << cardName << " discarded, too many cards in hand" << endl;
  }
}

int Hand::size() const {
  return this->numOfCards;
}

void Hand::discard(int handIndex) {
  if (handIndex >= this->numOfCards || handIndex < 0) {
    throw string("HandOutOfScope");
  } else {
    this->hand.erase(this->hand.begin() + handIndex);
    this->numOfCards--;
  }
}

