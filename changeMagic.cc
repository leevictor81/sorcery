#include "changeMagic.h"
#include "owner.h"

using namespace std;

ChangeMagic::ChangeMagic(int magicChange): magicChange{magicChange}{}

ChangeMagic::~ChangeMagic(){}

ChangeMagic* ChangeMagic::copyCtor() const{
  return new ChangeMagic(*this);
}

int ChangeMagic::getMagicChange() const{
  return this->magicChange;
}

void ChangeMagic::activate(Owner *me, Owner *opponent) {
  me->activate(this);
}

void ChangeMagic::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

