#ifndef SINGLE_TARGET_SKILL_H
#define SINGLE_TARGET_SKILL_H

#include "Action.h"

// Heavy single-target damage. Auto-targets the lowest HP enemy unless the
// player is manually targeting. Cannot crit, cannot miss.
class SingleTargetSkill : public Action {
public:
    explicit SingleTargetSkill(const std::string& flavorName);
    void execute(Unit* user, const std::vector<Unit*>& targets) override;
    bool isSingleEnemyTarget() const override { return true; }

private:
    static constexpr double COEFFICIENT = 2.2;
    static constexpr int MP_COST = 5;
};

#endif
