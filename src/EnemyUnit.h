#ifndef ENEMY_UNIT_H
#define ENEMY_UNIT_H

#include "Unit.h"

class EnemyUnit : public Unit {
public:
    EnemyUnit(const std::string& name,
              const std::string& title,
              int hp, int mp, int pow, int vit, int agi, int dex);

    Action* chooseAction(const std::vector<Unit*>& allies,
                         const std::vector<Unit*>& enemies) override;

    std::vector<Unit*> chooseTargets(Action* action,
                                     const std::vector<Unit*>& allies,
                                     const std::vector<Unit*>& enemies) override;

    bool isPlayerControlled() const override { return false; }
};

#endif
