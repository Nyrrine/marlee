#include "BasicAttack.h"

#include <iostream>

#include "Unit.h"
#include "Util.h"

BasicAttack::BasicAttack(const std::string& flavorName)
    : Action(flavorName, 0) {}

void BasicAttack::execute(Unit* user, const std::vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = targets.front();

    std::cout << "  " << user->getName() << " uses " << name
              << " on " << target->getName() << "!\n";

    int hit = computeHitPercent(user->getDex(), target->getAgi());
    if (!util::rollChance(hit)) {
        std::cout << "  >> " << user->getName() << "'s attack missed! ("
                  << hit << "% hit chance)\n";
        return;
    }

    int damage = computeDamage(user->getPow(), 1.0, target->getVit());

    bool crit = util::rollChance(20);
    if (crit) {
        damage += damage / 5; // +20%
        std::cout << "  >> CRITICAL HIT! ";
    } else {
        std::cout << "  >> ";
    }

    target->takeDamage(damage);
    std::cout << target->getName() << " takes " << damage << " damage. ("
              << target->getHp() << "/" << target->getMaxHp() << " HP)\n";
}
