#include <iostream>
#include <string>
#include "monster.h"

using namespace std;

Monster::Monster(string name, int cost, string description): Card(name, cost, description){}

Monster::~Monster(){}

