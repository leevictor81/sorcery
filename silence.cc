#include <string>
#include "silence.h"
#include "owner.h"

using namespace std;

Silence::Silence(string name, int cost, string description, Monster* component) : Enchantments(name, cost, description, component){}

void Silence::notify(Owner* me, Owner* opponent, string &event) {
}

void Silence::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
}

void Silence::play(Owner* me, Owner* opponent) {
  throw string("NeedIndex");
}

void Silence::play(int fieldIndex, Owner* player) {
  Silence* temp = new Silence(*this);
  player->playEnchantment(fieldIndex, temp);
}

void Silence::changeHasAttacked(bool hasAttacked){
  this->component->changeHasAttacked(hasAttacked);
}

bool Silence::getHasAttacked() const{
  return this->component->getHasAttacked();
}

string Silence::getCompName() const {
  return this->component->getCompName();
}

int Silence::getCompCost() const {
  return this->component->getCompCost();
}

string Silence::getCompDescription() const {
  return "SILENCED";
}


int Silence::getAttack() const{
  return this->component->getAttack();
}

int Silence::getDefense() const{
  return this->component->getDefense();
}

TriggerType Silence::getTriggerType() const{
  return TriggerType::None;
}

void Silence::changeStats(int attChange, int defChange) {
  this->component->changeStats(attChange, defChange);
}

void Silence::activate(Owner* me, Owner* opponent) {
  throw string("NoEffect");
}

void Silence::activate(int fieldIndex, Owner* player) {
  throw string("NoEffect");
}

int Silence::getEffectCost() const{
  return 0;
}


Effect* Silence::getEffect() const{
  return nullptr;
}

card_template_t Silence::makeTemplate() const{
  return display_enchantment(Card::getName(), Card::getCost(), Card::getDescription());
}

vector<vector<card_template_t>> Silence::makeCompleteTemplate() const {
  vector<vector<card_template_t>> compComplete = this->component->makeCompleteTemplate();
  card_template_t thisTemplate = this->makeTemplate();
  if (compComplete.size() == 1 || compComplete[compComplete.size() - 1].size() == 5) {
    vector<card_template_t> lineNew { thisTemplate };
    compComplete.push_back(lineNew);
    return compComplete;
  } else {
    compComplete[compComplete.size() - 1].push_back(thisTemplate);
    return compComplete;
  }
}

