#include "MultiTargetSkill.h"

#include <iostream>

#include "Unit.h"

MultiTargetSkill::MultiTargetSkill(const std::string& flavorName)
    : Action(flavorName, MP_COST) {}

void MultiTargetSkill::execute(Unit* user, const std::vector<Unit*>& targets) {
    if (targets.empty()) return;

    std::cout << "  " << user->getName() << " unleashes " << name
              << " on the entire enemy team!\n";

    user->spendMp(getMpCost());

    for (Unit* target : targets) {
        if (!target->isAlive()) continue;
        int damage = computeDamage(user->getPow(), COEFFICIENT, target->getVit());
        target->takeDamage(damage);
        std::cout << "  >> " << target->getName() << " takes " << damage
                  << " damage. ("
                  << target->getHp() << "/" << target->getMaxHp() << " HP)\n";
    }
}
