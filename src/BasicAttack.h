#ifndef BASIC_ATTACK_H
#define BASIC_ATTACK_H

#include "Action.h"

// Universal attack: random opposing unit, can crit, can miss, no MP cost.
class BasicAttack : public Action {
public:
    explicit BasicAttack(const std::string& flavorName);
    void execute(Unit* user, const std::vector<Unit*>& targets) override;
};

#endif
