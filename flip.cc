#include <string>
#include <iostream>
#include "triggerType.h"
#include "flip.h"
#include "owner.h"

using namespace std;

Flip::Flip(Effect* effect) {
  this->effect = effect;
}

Flip::~Flip() {
  delete this->effect;
}

Flip* Flip::copyCtor() const {
  Effect* temp = this->effect->copyCtor();
  Flip *temp2 = new Flip(temp);
  return temp2;
}

void Flip::activate(Owner *me, Owner *opponent) {
  int i = rand() % 2;
  string event;
  if (i == 0) {
    event = "Heads";
    this->effect->activate(me, opponent);
    me->notifyObservers(TriggerType::Xwindow, me, opponent, event);
    cout << "Heads Flipped" << endl;
  } else {
    cout << "Tails Flipped" << endl;
    event = "Tails";
    me->notifyObservers(TriggerType::Xwindow, me, opponent, event);
  }
}

void Flip::activate(int fieldIndex, Owner *player) {
  int i = rand() % 2;
  string event;
  if (i == 0) {
    cout << "Heads Flipped" << endl;
    event = "Heads";
    player->notifyObservers(TriggerType::Xwindow, player, player, event);
    this->effect->activate(fieldIndex, player);
  } else {
    cout << "Tails Flipped" << endl;
    event = "Tails";
    player->notifyObservers(TriggerType::Xwindow, player, player, event);
  }
}

