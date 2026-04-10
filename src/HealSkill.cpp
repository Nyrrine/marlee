#include "HealSkill.h"

#include <iostream>

#include "Unit.h"

HealSkill::HealSkill(const std::string& flavorName)
    : Action(flavorName, MP_COST) {}

void HealSkill::execute(Unit* user, const std::vector<Unit*>& targets) {
    if (targets.empty()) return;
    Unit* target = targets.front();

    int healAmount = (target->getMaxHp() * HEAL_PERCENT) / 100;
    if (healAmount < 1) healAmount = 1;

    std::cout << "  " << user->getName() << " calls down " << name
              << " on " << target->getName() << "!\n";

    target->heal(healAmount);
    user->spendMp(getMpCost());

    std::cout << "  >> " << target->getName() << " is healed for "
              << healAmount << " HP. ("
              << target->getHp() << "/" << target->getMaxHp() << " HP)\n";
}
