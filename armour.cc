#include <string>
#include "armour.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;


Armour::Armour(string name, int cost, string description, Monster* component, int damageShielded) : Enchantments(name, cost, description, component), damageShielded(damageShielded) {}

void Armour::notify(Owner* me, Owner* opponent, string &event) {
  if(this->component->getEffect()) this->component->getEffect()->activate(me, opponent);
}

void Armour::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  if(this->component->getEffect()){
    if (whoSummon == 1) {
      this->component->getEffect()->activate(fieldIndex, me);
    } else {
      this->component->getEffect()->activate(fieldIndex, opponent);
    }
  }
}

void Armour::play(Owner* me, Owner* opponent) {
  throw string("NeedIndex");
}

void Armour::play(int fieldIndex, Owner* player) {
  Armour* temp = new Armour(*this); //copy ctor
  player->playEnchantment(fieldIndex, temp);
}

void Armour::changeHasAttacked(bool hasAttacked){
  this->component->changeHasAttacked(hasAttacked);
}

bool Armour::getHasAttacked() const{
  return this->component->getHasAttacked();
}

string Armour::getCompName() const {
  return this->component->getCompName();
}

int Armour::getCompCost() const {
  return this->component->getCompCost();
}

string Armour::getCompDescription() const {
  return this->component->getCompDescription();
}

int Armour::getAttack() const{
  return this->component->getAttack();
}

int Armour::getDefense() const{
  return this->component->getDefense();
}

TriggerType Armour::getTriggerType() const{
  return this->component->getTriggerType();
}

void Armour::changeStats(int attChange, int defChange) {
  if (defChange >= 0) {
  this->component->changeStats(attChange, defChange);
  } else {
    this->component->changeStats(attChange, defChange + 1);
  }
}

void Armour::activate(Owner* me, Owner* opponent) {
  this->component->activate(me, opponent);
}

void Armour::activate(int fieldIndex, Owner* player) {
  this->component->activate(fieldIndex, player);
}

int Armour::getEffectCost() const{
  return this->component->getEffectCost();
}

Effect* Armour::getEffect() const{
  return this->component->getEffect();
}

card_template_t Armour::makeTemplate() const{
  return display_enchantment(Card::getName(), Card::getCost(), Card::getDescription());
}

vector<vector<card_template_t>> Armour::makeCompleteTemplate() const {
  vector<vector<card_template_t>> compComplete = this->component->makeCompleteTemplate();
  card_template_t thisTemplate = this->makeTemplate();
  if (compComplete.size() == 1 || compComplete[compComplete.size() - 1].size() == 5) {
    vector<card_template_t> lineNew;
    lineNew.push_back(thisTemplate);
    compComplete.push_back(lineNew);
    return compComplete;
  } else {
    compComplete[compComplete.size() - 1].push_back(thisTemplate);
    return compComplete;
  }
}


