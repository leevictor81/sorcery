#ifndef _BASE_MONSTER_H_
#define _BASE_MONSTER_H_
#include <string>
#include <vector>
#include "monster.h"
#include "triggerType.h"

class Effect;

//SHOULD WE HAVE INHERIT FROM CARD???
class BaseMonster : public Monster{
  int attack;
  int defense;
  TriggerType Trigger;
  Effect* effect;
  int effectCost;
  bool hasAttacked;
public:
  BaseMonster(std::string name, int cost, std::string description, int att, int def, TriggerType t, Effect* e, int effectCost);
  ~BaseMonster();
  BaseMonster(const BaseMonster &other); // Copy Constructor
  BaseMonster(BaseMonster &&other); //Move Constructor
  BaseMonster &operator=(const BaseMonster &other); //Copy Assignment
  BaseMonster &operator=(BaseMonster &&other); //Move Assignment

  void play(Owner* me, Owner* opponent) override;
  void play(int fieldIndex, Owner* player) override;

  void changeHasAttacked(bool hasAttacked) override;
  bool getHasAttacked() const override;
  std::string getCompName() const override;
  int getCompCost() const override;
  std::string getCompDescription() const override;
  int getAttack() const override;
  int getDefense() const override;
  TriggerType getTriggerType() const override;
  void changeStats(int attChange, int defChange) override;
  void activate(Owner* me, Owner* opponent) override;
  void activate(int fieldIndex, Owner* player) override;
  int getEffectCost() const override;
  Effect* getEffect() const override;
  Monster* getComponent() override;
  void notify(Owner* me, Owner* opponent, std::string &event) override;
  void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) override;
  void disenchant() override;
  card_template_t makeTemplate() const override;
  card_template_t getMonsterTemplate() const override;
  std::vector<std::vector<card_template_t>> makeCompleteTemplate() const override;
};

#endif

