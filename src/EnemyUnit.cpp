#include "EnemyUnit.h"

#include <iostream>

#include "Action.h"
#include "Util.h"

EnemyUnit::EnemyUnit(const std::string& name,
                     const std::string& title,
                     int hp, int mp, int pow, int vit, int agi, int dex)
    : Unit(name, title, hp, mp, pow, vit, agi, dex) {}

namespace {
    std::vector<Unit*> aliveOnly(const std::vector<Unit*>& side) {
        std::vector<Unit*> out;
        for (Unit* u : side) {
            if (u && u->isAlive()) out.push_back(u);
        }
        return out;
    }

    // Returns the unit with the lowest HP from the supplied (already alive) list.
    Unit* lowestHp(const std::vector<Unit*>& units) {
        Unit* best = nullptr;
        for (Unit* u : units) {
            if (!best || u->getHp() < best->getHp()) best = u;
        }
        return best;
    }
}

// Spec: 50% chance to use a skill (if it can afford one), otherwise basic attack.
Action* EnemyUnit::chooseAction(const std::vector<Unit*>& /*allies*/,
                                const std::vector<Unit*>& /*enemies*/) {
    Action* basicAttack = nullptr;
    std::vector<Action*> affordableSkills;

    for (Action* a : actions) {
        if (a->getMpCost() == 0) {
            basicAttack = a;
        } else if (a->canCast(*this)) {
            affordableSkills.push_back(a);
        }
    }

    bool wantsSkill = util::rollChance(50);
    if (wantsSkill && !affordableSkills.empty()) {
        int idx = util::randomInt(0, static_cast<int>(affordableSkills.size()) - 1);
        return affordableSkills[idx];
    }
    return basicAttack;
}

// AI targeting mirrors the spec defaults: lowest-HP enemy for single target,
// lowest-HP ally for heal, random for basic attack, all for multi.
std::vector<Unit*> EnemyUnit::chooseTargets(Action* action,
                                            const std::vector<Unit*>& allies,
                                            const std::vector<Unit*>& enemies) {
    if (action->isMultiEnemyTarget()) {
        return aliveOnly(enemies);
    }
    if (action->isSingleEnemyTarget()) {
        Unit* t = lowestHp(aliveOnly(enemies));
        if (!t) return {};
        return { t };
    }
    if (action->isSingleAllyTarget()) {
        Unit* t = lowestHp(aliveOnly(allies));
        if (!t) return {};
        return { t };
    }
    // Basic attack: random opposing unit.
    std::vector<Unit*> alive = aliveOnly(enemies);
    if (alive.empty()) return {};
    return { alive[util::randomInt(0, static_cast<int>(alive.size()) - 1)] };
}
