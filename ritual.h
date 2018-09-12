#ifndef _RITUAL_H_
#define _RITUAL_H_
#include <iostream>
#include <string>
#include "card.h"
#include "triggerType.h"
#include "observer.h"
#include "effect.h"
#include "subject.h"

class Ritual : public Card, public Observer {
  int charge;
  TriggerType Trigger;
  Effect* effect;
  int effectCost;
 public:
   Ritual(std::string name, int cost, std::string description, int charge, TriggerType t, Effect *e, int effectCost);
   ~Ritual();
   Ritual(const Ritual &other);
   void play(Owner* me, Owner* opponent) override;
   void play(int fieldIndex, Owner* player) override;
   TriggerType getTriggerType() const override;
   void activate(Owner* me, Owner* opponent);
   void activate(int fieldIndex, Owner* player);
   void increaseCharge(int amount);
   void notify(Owner* me, Owner* opponent, std::string &event) override;
   void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) override;
   card_template_t makeTemplate() const override;
};

#endif

