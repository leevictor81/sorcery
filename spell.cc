#include <iostream>
#include <string>
#include "spell.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;

Spell::Spell(string name, int cost, string description, Effect *e) : Card(name, cost, description), effect{e} {}

Spell::~Spell(){
  delete effect;
}

void Spell::play(Owner* me, Owner* opponent) {
  this->effect->activate(me, opponent);
}

void Spell::play(int fieldIndex, Owner* player) {
  this->effect->activate(fieldIndex, player);
}

card_template_t Spell::makeTemplate() const {
  return display_spell(Card::getName(), Card::getCost(), Card::getDescription());
}

