#ifndef HEAL_SKILL_H
#define HEAL_SKILL_H

#include "Action.h"

// Restores 30% of an ally's max HP. Auto-targets the lowest-HP ally unless
// the player is manually targeting.
class HealSkill : public Action {
public:
    explicit HealSkill(const std::string& flavorName);
    void execute(Unit* user, const std::vector<Unit*>& targets) override;
    bool isSingleAllyTarget() const override { return true; }

private:
    static constexpr int HEAL_PERCENT = 30;
    static constexpr int MP_COST = 3;
};

#endif
