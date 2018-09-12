#ifndef _SILENCE_H_
#define _SILENCE_H_
#include <string>
#include <vector>
#include "enchantments.h"
#include "triggerType.h"

class Silence : public Enchantments {
public:
  Silence(std::string name, int cost, std::string description, Monster* component);
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
  void notify(Owner* me, Owner* opponent, std::string &event) override;
  void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) override;
  card_template_t makeTemplate() const override;
  std::vector<std::vector<card_template_t>> makeCompleteTemplate() const override;
};

#endif

