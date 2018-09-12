#ifndef _FIELD_H
#define _FIELD_H
#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "monster.h"
#include "ritual.h"
#include "enchantments.h"

class Owner;

class Field {
  std::vector<Monster*> field;
  Ritual* ritual;
  int numOfCards;

  public:
    Field();
    ~Field();

    int getAttack(int fieldIndex) const;

    int getDefense(int fieldIndex) const;

    std::string getName(int fieldIndex) const;

    void changeStats(int fieldIndex, int attChange, int defChange);

    void activate(int fieldIndex, Owner* target, int targFieldIndex);

    void activate(int fieldIndex, Owner* owner, Owner* opponent);

    Ritual* getRitual() const;

    void summon(Monster* monster);

    void playRitual(Ritual *r);
   
    void increaseCharge(int chargeChange);

    void playEnchantment(int fieldIndex, Enchantments* enchantment);

    void disenchant(int fieldIndex);
    
    std::string destroy(int fieldIndex);

    int size() const;

    Monster* getMonster(int fieldIndex) const;

    card_template_t getMonsterTemplate(int fieldIndex) const;

    std::vector<std::vector<card_template_t>> makeCompleteTemplate(int fieldIndex) const;
};

#endif

