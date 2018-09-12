#ifndef _HAND_H
#define _HAND_H
#include <iostream>
#include <string>
#include <vector>

class Hand {
  std::vector<std::string> hand;
  int numOfCards;

  public:
    Hand();
    ~Hand();

    void destroyCard(int handIndex);

    std::string getCardName(int handIndex) const;

    void addCard(std::string cardName);

    void addToPos(std::string cardName, int handIndex);

    int size() const;

    void discard(int handIndex);
};

#endif

