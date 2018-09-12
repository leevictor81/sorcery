#include <iostream>
#include <string>
#include "ritual.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;

Ritual::Ritual(string name, int cost, string description, int charge, TriggerType t, Effect *e, int effectCost) : Card(name, cost, description), charge{charge}, Trigger{t}, effect{e}, effectCost{effectCost} {}

Ritual::~Ritual() {
  delete effect;
}

Ritual::Ritual(const Ritual &other) : Card(other), charge{other.charge}, Trigger{other.Trigger}, effectCost{other.effectCost} {
  Effect* temp = other.effect->copyCtor();
  effect = temp;
}

void Ritual::notify(Owner* me, Owner* opponent, string &event) {
  this->activate(me, opponent);
}

void Ritual::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  if (whoSummon == 1) {
    this->activate(fieldIndex, me);
  } else {
    this->activate(fieldIndex, opponent);
  }
}

void Ritual::play(Owner* me, Owner* opponent) {
  Ritual* temp = new Ritual(*this);
  me->playRitual(temp);
}

void Ritual::play(int fieldIndex, Owner* player) {
  throw string("NoNeedIndex");
}

TriggerType Ritual::getTriggerType() const{
  return Trigger;
}

void Ritual::activate(Owner* me, Owner* opponent) {
  if (this->effect == nullptr) {
    throw string("NoEffect");
  } else if (this->effectCost > this->charge) {
    cerr << "Not enough charges for" << Card::getName() << "'s effect" << endl;
  } else {
    this->effect->activate(me, opponent);
    this->charge -= this->effectCost;
  }
}

void Ritual::activate(int fieldIndex, Owner* player) {
  if (this->effect == nullptr) {
    throw string("NoEffect");
  } else if (this->effectCost > this->charge) {
    cerr << "Not enough charges for" << Card::getName() << "'s effect" << endl;
  } else {
    this->effect->activate(fieldIndex, player);
    this->charge -= this->effectCost;
  }
}

void Ritual::increaseCharge(int amount) {
  charge += amount;
}

card_template_t Ritual::makeTemplate() const {
  return display_ritual(Card::getName(), Card::getCost(), this->effectCost, Card::getDescription(), this->charge);
}

