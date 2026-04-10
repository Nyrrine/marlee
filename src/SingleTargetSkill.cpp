#include "SingleTargetSkill.h"

#include <iostream>

#include "Unit.h"

SingleTargetSkill::SingleTargetSkill(const std::string& flavorName)
    : Action(flavorName, MP_COST) {}

void SingleTargetSkill::execute(Unit* user, const std::vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = targets.front();

    std::cout << "  " << user->getName() << " channels " << name
              << " at " << target->getName() << "!\n";

    int damage = computeDamage(user->getPow(), COEFFICIENT, target->getVit());
    target->takeDamage(damage);
    user->spendMp(getMpCost());

    std::cout << "  >> " << target->getName() << " is struck for "
              << damage << " damage. ("
              << target->getHp() << "/" << target->getMaxHp() << " HP)\n";
}
