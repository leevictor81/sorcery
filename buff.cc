#include <string>
#include "buff.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;


Buff::Buff(string name, int cost, string description, Monster* component, int attackChange, int defenseChange) : Enchantments(name, cost, description, component), attackChange{attackChange}, defenseChange{defenseChange} {}

void Buff::notify(Owner* me, Owner* opponent, string &event) {
  if(this->component->getEffect()) this->component->getEffect()->activate(me, opponent);
}

void Buff::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  if(this->component->getEffect()){
    if (whoSummon == 1) {
      this->component->getEffect()->activate(fieldIndex, me);
    } else {
      this->component->getEffect()->activate(fieldIndex, opponent);
    }
  }
}

void Buff::play(Owner* me, Owner* opponent) {
  throw string("NeedIndex");
}

void Buff::play(int fieldIndex, Owner* player) {
  Buff* temp = new Buff(*this); //copy ctor
  player->playEnchantment(fieldIndex, temp);
}

void Buff::changeHasAttacked(bool hasAttacked){
  this->component->changeHasAttacked(hasAttacked);
}

bool Buff::getHasAttacked() const{
  return this->component->getHasAttacked();
}

string Buff::getCompName() const {
  return this->component->getCompName();
}

int Buff::getCompCost() const {
  return this->component->getCompCost();
}

string Buff::getCompDescription() const {
  return this->component->getCompDescription();
}

int Buff::getAttack() const{
  return this->component->getAttack() + this->attackChange;
}

int Buff::getDefense() const{
  return this->component->getDefense() + this->defenseChange;
}

TriggerType Buff::getTriggerType() const{
  return this->component->getTriggerType();
}

void Buff::changeStats(int attChange, int defChange) {
  this->component->changeStats(attChange, defChange);
}

void Buff::activate(Owner* me, Owner* opponent) {
  this->component->activate(me, opponent);
}

void Buff::activate(int fieldIndex, Owner* player) {
  this->component->activate(fieldIndex, player);
}

int Buff::getEffectCost() const{
  return this->component->getEffectCost();
}

Effect* Buff::getEffect() const{
  return this->component->getEffect();
}

card_template_t Buff::makeTemplate() const{
  string attack = to_string(attackChange);
  string defense = to_string(defenseChange);
  if(attackChange > 0) attack = "+" + attack;
  if(defenseChange > 0) defense = "+" + defense;
  return display_enchantment_attack_defence(Card::getName(), Card::getCost(), Card::getDescription(), attack, defense);
}

vector<vector<card_template_t>> Buff::makeCompleteTemplate() const {
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

