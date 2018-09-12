#include <string>
#include "draw.h"
#include "owner.h"

using namespace std;

Draw::Draw(int cards) {
  this->cardsDrawn = cards;
}

Draw::~Draw() {}

Draw* Draw::copyCtor() const {
  return new Draw(*this);
}

int Draw::getCards() const {
  return this->cardsDrawn;
}

void Draw::activate(Owner *me, Owner *opponent) {
  me->activate(this, this->cardsDrawn);
}

void Draw::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

