#include <string>
#include "magicFatigue.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;

MagicFatigue::MagicFatigue(string name, int cost, string description, Monster* component, int costChange): Enchantments(name, cost, description, component), costChange{costChange}{}

void MagicFatigue::notify(Owner* me, Owner* opponent, string &event) {
  if(this->component->getEffect()) this->component->getEffect()->activate(me, opponent);
}

void MagicFatigue::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  if(this->component->getEffect()){
    if (whoSummon == 1) {
      this->component->getEffect()->activate(fieldIndex, me);
    } else {
      this->component->getEffect()->activate(fieldIndex, opponent);
    }
  }
}


void MagicFatigue::play(Owner* me, Owner* opponent) {
  throw string("NeedIndex");
}

void MagicFatigue::play(int fieldIndex, Owner* player) {
  MagicFatigue* temp = new MagicFatigue(*this); //copy ctor
  player->playEnchantment(fieldIndex, temp);
}

void MagicFatigue::changeHasAttacked(bool hasAttacked){
  this->component->changeHasAttacked(hasAttacked);
}

bool MagicFatigue::getHasAttacked() const{
  return this->component->getHasAttacked();
}

string MagicFatigue::getCompName() const {
  return this->component->getCompName();
}

int MagicFatigue::getCompCost() const {
  return this->component->getCompCost();
}

string MagicFatigue::getCompDescription() const {
  return this->component->getCompDescription();
}


int MagicFatigue::getAttack() const{
  return this->component->getAttack();
}

int MagicFatigue::getDefense() const{
  return this->component->getDefense();
}

TriggerType MagicFatigue::getTriggerType() const{
  return this->component->getTriggerType();
}

void MagicFatigue::changeStats(int attChange, int defChange) {
  this->component->changeStats(attChange, defChange);
}

void MagicFatigue::activate(Owner* me, Owner* opponent) {
  this->component->activate(me, opponent);
}

void MagicFatigue::activate(int fieldIndex, Owner* player) {
  this->component->activate(fieldIndex, player);
}

int MagicFatigue::getEffectCost() const{
  int i = this->component->getEffectCost() + this->costChange;
  cout << i << endl;
  return this->component->getEffectCost() + this->costChange;
}

Effect* MagicFatigue::getEffect() const{
  return this->component->getEffect();
}

card_template_t MagicFatigue::makeTemplate() const{
  return display_enchantment(Card::getName(), Card::getCost(), Card::getDescription());
}

vector<vector<card_template_t>> MagicFatigue::makeCompleteTemplate() const {
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

