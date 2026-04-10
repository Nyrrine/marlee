#include "Action.h"

#include "Unit.h"
#include "Util.h"

Action::Action(const std::string& name, int mpCost)
    : name(name), mpCost(mpCost) {}

bool Action::canCast(const Unit& user) const {
    return user.getMp() >= mpCost;
}

// Spec: 20% variance on POW. POW=100 => randomized in [100, 119].
int Action::randomizedPow(int basePow) {
    int variance = (basePow * 20) / 100;
    if (variance <= 0) return basePow;
    return util::randomInt(basePow, basePow + variance - 1);
}

// damage = (randomizedPow * coeff) - vit, clamped to a minimum of 1.
int Action::computeDamage(int basePow, double coefficient, int defenderVit) {
    int rolled = randomizedPow(basePow);
    int raw = static_cast<int>(rolled * coefficient) - defenderVit;
    if (raw < 1) raw = 1;
    return raw;
}

int Action::computeHitPercent(int attackerDex, int defenderAgi) {
    if (defenderAgi <= 0) return 80;
    int hit = (attackerDex * 100) / defenderAgi;
    return util::clampInt(hit, 20, 80);
}
