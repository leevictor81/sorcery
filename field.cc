#include <iostream>
#include <string>
#include <vector>
#include "field.h"

using namespace std;

Field::Field() {
  this->ritual = nullptr;
  this->numOfCards = 0;
}

Field::~Field() {
  for (int i = 0; i < this->numOfCards; i++) {
    delete this->field[i];
  }
  delete this->ritual;
}

int Field::getAttack(int fieldIndex) const {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    return this->field[fieldIndex]->getAttack();
  }
}

int Field::getDefense(int fieldIndex) const {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    return this->field[fieldIndex]->getDefense();
  }
}

string Field::getName(int fieldIndex) const {
  if(fieldIndex == 5 && this->ritual != nullptr){
    return this->ritual->getName();
  }
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    return this->field[fieldIndex]->getCompName();
  }
}

void Field::changeStats(int fieldIndex, int attChange, int defChange) {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    this->field[fieldIndex]->changeStats(attChange, defChange);
  }
}

void Field::activate(int fieldIndex, Owner* target, int targFieldIndex) {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    this->field[fieldIndex]->activate(targFieldIndex, target);
  }
}

void Field::activate(int fieldIndex, Owner* owner, Owner* opponent) {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    this->field[fieldIndex]->activate(owner, opponent);
  }
}

Ritual* Field::getRitual() const{
  if(!this->ritual){
    throw string("NoRitual");
  }else{
    return this->ritual;
  }
}

void Field::summon(Monster* monster) {
  if (this->numOfCards == 5) {
    delete monster;
    throw string("FieldMaxed");
  } else {
    this->field.push_back(monster);
    this->numOfCards++;
  }
}

void Field::playRitual(Ritual *r){
  if(this->ritual){
    delete this->ritual;
  }
  this->ritual = r;
}

void Field::playEnchantment(int fieldIndex, Enchantments* enchantment){
  if(fieldIndex >= this->numOfCards || fieldIndex < 0){
    delete enchantment;
    if(fieldIndex == 5){
      if(this->ritual) throw string("UsedOnRitual");
    }else{
      throw string("FieldOutOfScope");
    }
  }else{
    enchantment->addComponent(field[fieldIndex]);
    field[fieldIndex] = enchantment;
  }
}

void Field::increaseCharge(int chargeChange) {
  if(this->ritual){
    this->ritual->increaseCharge(chargeChange);
    cout << "charge increased by " << chargeChange << endl;
  }else{
    throw string("NoRitual");
  }
}

string Field::destroy(int fieldIndex) {
  if (fieldIndex >= this->numOfCards || fieldIndex < 0) {
    throw string("FieldOutOfScope");
  } else {
    string monsterName = this->field[fieldIndex]->getCompName();
    this->numOfCards--;
    delete this->field[fieldIndex];
    this->field.erase(this->field.begin() + fieldIndex);
    cout << monsterName << " was sent to the Graveyard" << endl;
    return monsterName;
  }
}

void Field::disenchant(int fieldIndex) {
  Monster* temp = this->field[fieldIndex]->getComponent();
  this->field[fieldIndex]->disenchant();
  delete this->field[fieldIndex];
  this->field.erase(this->field.begin() + fieldIndex);
  this->numOfCards--;
  this->summon(temp);
}

int Field::size() const {
  return this->numOfCards;
}

Monster* Field::getMonster(int fieldIndex) const{
  if(fieldIndex >= this->numOfCards || fieldIndex < 0){
    throw string("FieldOutOfScope");
  }else{
    return field[fieldIndex];
  }
}

card_template_t Field::getMonsterTemplate(int fieldIndex) const{
  return field[fieldIndex]->getMonsterTemplate();
}

vector<vector<card_template_t>> Field::makeCompleteTemplate(int fieldIndex) const{
  return field[fieldIndex]->makeCompleteTemplate();
}

