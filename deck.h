#ifndef __DECK_H__
#define __DECK_H__
#include <string>
#include <vector>

class Deck {
  std::vector<std::string> deck;
  int numOfCards;

  public:
    Deck();
    ~Deck();

    std::string draw();
    
    void shuffle();

    void putToBottom(std::string cardName);

    int size() const;
};

#endif     

