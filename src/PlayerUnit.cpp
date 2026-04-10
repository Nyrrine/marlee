#include "PlayerUnit.h"

#include <iostream>

#include "Action.h"
#include "Util.h"

PlayerUnit::PlayerUnit(const std::string& name,
                       const std::string& title,
                       int hp, int mp, int pow, int vit, int agi, int dex)
    : Unit(name, title, hp, mp, pow, vit, agi, dex) {}

namespace {
    // Builds a list of alive units from the given side.
    std::vector<Unit*> aliveOnly(const std::vector<Unit*>& side) {
        std::vector<Unit*> out;
        for (Unit* u : side) {
            if (u && u->isAlive()) out.push_back(u);
        }
        return out;
    }
}

Action* PlayerUnit::chooseAction(const std::vector<Unit*>& /*allies*/,
                                 const std::vector<Unit*>& /*enemies*/) {
    while (true) {
        std::cout << "\n  -- " << name << " (" << title << "), choose your action --\n";
        for (size_t i = 0; i < actions.size(); ++i) {
            Action* a = actions[i];
            std::cout << "    " << (i + 1) << ") " << a->getName();
            if (a->getMpCost() > 0) {
                std::cout << "  (MP: " << a->getMpCost() << ")";
            }
            if (!a->canCast(*this)) {
                std::cout << "  [NOT ENOUGH MP]";
            }
            std::cout << "\n";
        }

        int choice = util::promptIntInRange("  > ", 1, static_cast<int>(actions.size()));
        Action* picked = actions[choice - 1];
        if (!picked->canCast(*this)) {
            std::cout << "  >> " << name << " doesn't have enough MP for "
                      << picked->getName() << ". Pick another action.\n";
            continue;
        }
        return picked;
    }
}

// Manual targeting: prompt for the appropriate side, list alive units only.
// Multi-target hits all alive enemies (no prompt). Basic attack stays random
// per spec (also no prompt).
std::vector<Unit*> PlayerUnit::chooseTargets(Action* action,
                                             const std::vector<Unit*>& allies,
                                             const std::vector<Unit*>& enemies) {
    if (action->isMultiEnemyTarget()) {
        return aliveOnly(enemies);
    }

    if (action->isSingleEnemyTarget()) {
        std::vector<Unit*> options = aliveOnly(enemies);
        std::cout << "\n  -- Choose a target for " << action->getName() << " --\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << "    " << (i + 1) << ") " << options[i]->getName()
                      << "  (" << options[i]->getHp() << "/"
                      << options[i]->getMaxHp() << " HP)\n";
        }
        int pick = util::promptIntInRange("  > ", 1, static_cast<int>(options.size()));
        return { options[pick - 1] };
    }

    if (action->isSingleAllyTarget()) {
        std::vector<Unit*> options = aliveOnly(allies);
        std::cout << "\n  -- Choose an ally to heal --\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << "    " << (i + 1) << ") " << options[i]->getName()
                      << "  (" << options[i]->getHp() << "/"
                      << options[i]->getMaxHp() << " HP)\n";
        }
        int pick = util::promptIntInRange("  > ", 1, static_cast<int>(options.size()));
        return { options[pick - 1] };
    }

    // BasicAttack: random opposing unit (spec).
    std::vector<Unit*> alive = aliveOnly(enemies);
    if (alive.empty()) return {};
    return { alive[util::randomInt(0, static_cast<int>(alive.size()) - 1)] };
}
