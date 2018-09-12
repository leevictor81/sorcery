#ifndef _MONSTER_H_
#define _MONSTER_H_
#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "triggerType.h"
#include "observer.h"

class Effect;

class Owner;

class Monster : public Card , public Observer{
public:
  Monster(std::string name, int cost, std::string description);
  virtual ~Monster();
  virtual void play(Owner* me, Owner* opponent) = 0;
  virtual void play(int fieldIndex, Owner* player) = 0;
  virtual void changeHasAttacked(bool hasAttacked) = 0;
  virtual bool getHasAttacked() const = 0;
  virtual std::string getCompName() const = 0;
  virtual int getCompCost() const = 0;
  virtual std::string getCompDescription() const = 0;
  virtual int getAttack() const = 0;
  virtual int getDefense() const = 0;
  virtual TriggerType getTriggerType() const = 0;
  virtual void changeStats(int attChange, int defChange) = 0;
  virtual void activate(Owner* me, Owner* opponent) = 0;
  virtual void activate(int fieldIndex, Owner* player) = 0;
  virtual Monster* getComponent() = 0;
  virtual int getEffectCost() const = 0;
  virtual Effect* getEffect() const = 0;
  virtual void notify(Owner* me, Owner* opponent, std::string &event) = 0;
  virtual void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) = 0;
  virtual void disenchant() = 0;
  virtual card_template_t makeTemplate() const = 0;
  virtual card_template_t getMonsterTemplate() const = 0;
  virtual std::vector<std::vector<card_template_t>> makeCompleteTemplate() const = 0;
};

#endif

