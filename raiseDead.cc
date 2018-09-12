#include <string>
#include "raiseDead.h"
#include "owner.h"

using namespace std;

RaiseDead::RaiseDead(int numOfRaises) :
numOfRaises{numOfRaises} {}

RaiseDead::~RaiseDead() {}

RaiseDead* RaiseDead::copyCtor() const{
  return new RaiseDead(*this);
}

int RaiseDead::getNumOfRaises() const{
  return this->numOfRaises;
}

void RaiseDead::activate(Owner *me, Owner *opponent) {
  me->activate(this);
}

void RaiseDead::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

