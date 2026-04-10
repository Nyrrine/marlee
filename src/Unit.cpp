#include "Unit.h"

#include <iomanip>
#include <iostream>

#include "Action.h"

Unit::Unit(const std::string& name,
           const std::string& title,
           int hp, int mp, int pow, int vit, int agi, int dex)
    : name(name), title(title),
      maxHp(hp), hp(hp),
      maxMp(mp), mp(mp),
      pow(pow), vit(vit), agi(agi), dex(dex) {}

Unit::~Unit() {
    for (Action* a : actions) {
        delete a;
    }
    actions.clear();
}

void Unit::addAction(Action* action) {
    actions.push_back(action);
}

void Unit::takeDamage(int amount) {
    if (amount < 0) amount = 0;
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Unit::heal(int amount) {
    if (amount < 1) amount = 1;
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}

void Unit::spendMp(int amount) {
    if (amount < 0) amount = 0;
    mp -= amount;
    if (mp < 0) mp = 0;
}

void Unit::printStatusLine() const {
    std::cout << "  " << std::left << std::setw(22) << name
              << " HP " << std::setw(4) << hp << "/" << std::setw(4) << maxHp
              << " MP " << std::setw(3) << mp << "/" << std::setw(3) << maxMp;
    if (!isAlive()) std::cout << "  [DEAD]";
    std::cout << "\n";
}
