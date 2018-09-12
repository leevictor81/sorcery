#ifndef __GRAVEYARD_H__
#define __GRAVEYARD_H__
#include <string>
#include <vector>

class Graveyard {
  std::vector<std::string> graveyard;
  int numOfCards;

  public:
    Graveyard();
    ~Graveyard();

    void addToGraveyard(std::string cardName);

    void deleteCard();

    std::string returnCard() const;

    int size() const;
};

#endif

