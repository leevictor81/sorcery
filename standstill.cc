#include <string>
#include "standstill.h"
#include "owner.h"

using namespace std;

Standstill::Standstill() {}

Standstill::~Standstill() {}

Standstill* Standstill::copyCtor() const{
  return new Standstill(*this);
}

void Standstill::activate(Owner *me, Owner *opponent) {
  throw string("NeedIndex");
}

void Standstill::activate(int fieldIndex, Owner *player) {
  player->activate(this, fieldIndex);
}

