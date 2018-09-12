#ifndef _ENCHANTMENTS_H_
#define _ENCHANTMENTS_H_
#include <iostream>
#include <string>
#include <vector>
#include "monster.h"

class Owner;

class Enchantments : public Monster{
protected:
  Monster *component;

public:
  Enchantments(std::string name, int cost, std::string description, Monster *component);
  virtual ~Enchantments();
  virtual void play(Owner* me, Owner* opponent) = 0;
  virtual void play(int fieldIndex, Owner* player) = 0;
  virtual void changeHasAttacked(bool hasAttacked) = 0;
  virtual bool getHasAttacked() const = 0;
  std::string getCompName() const  = 0;
  int getCompCost() const = 0;
  std::string getCompDescription() const = 0;
  virtual int getAttack() const = 0;
  virtual int getDefense() const = 0;
  virtual TriggerType getTriggerType() const = 0;
  virtual void changeStats(int attChange, int defChange) = 0;
  virtual void activate(Owner* me, Owner* opponent) = 0;
  virtual void activate(int fieldIndex, Owner* player) = 0;
  void addComponent(Monster* m);
  Monster* getComponent() override;
  virtual int getEffectCost() const = 0;
  virtual void notify(Owner* me, Owner* opponent, std::string &event) = 0;
  virtual void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) = 0;
  virtual card_template_t makeTemplate() const = 0;
  card_template_t getMonsterTemplate() const;
  void disenchant() override;
  virtual std::vector<std::vector<card_template_t>> makeCompleteTemplate() const = 0;
};

#endif

