#include <string>
#include "summon.h"
#include "owner.h"

using namespace std;


Summon::Summon(string monsterName, int amount): monsterName{monsterName}, amount{amount} {}

Summon::~Summon() {}

Summon* Summon::copyCtor() const{
  return new Summon(*this);
}

string Summon::getName() const{
  return this->monsterName;
}

int Summon::getAmount() const{
  return this->amount;
}

void Summon::activate(Owner *me, Owner *opponent) {
  me->activate(this);
}

void Summon::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

