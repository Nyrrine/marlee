#ifndef MULTI_TARGET_SKILL_H
#define MULTI_TARGET_SKILL_H

#include "Action.h"

// Hits every alive opposing unit; damage is rolled fresh for each target.
class MultiTargetSkill : public Action {
public:
    explicit MultiTargetSkill(const std::string& flavorName);
    void execute(Unit* user, const std::vector<Unit*>& targets) override;
    bool isMultiEnemyTarget() const override { return true; }

private:
    static constexpr double COEFFICIENT = 0.9;
    static constexpr int MP_COST = 4;
};

#endif
