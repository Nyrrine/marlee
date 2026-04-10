#include "Combat.h"

#include <algorithm>
#include <iostream>

#include "Action.h"
#include "Unit.h"
#include "Util.h"

Combat::Combat(const std::string& playerTeamName,
               const std::vector<Unit*>& playerTeam,
               const std::string& enemyTeamName,
               const std::vector<Unit*>& enemyTeam)
    : playerTeamName(playerTeamName),
      enemyTeamName(enemyTeamName),
      playerTeam(playerTeam),
      enemyTeam(enemyTeam) {}

// Spec: turn order built once, sorted by AGI descending.
void Combat::buildTurnOrder() {
    turnOrder.clear();
    for (Unit* u : playerTeam) turnOrder.push_back(u);
    for (Unit* u : enemyTeam)  turnOrder.push_back(u);

    std::sort(turnOrder.begin(), turnOrder.end(),
              [](const Unit* a, const Unit* b) {
                  return a->getAgi() > b->getAgi();
              });
}

void Combat::printTurnOrder() const {
    std::cout << "\n=========== TURN ORDER ===========\n";
    for (size_t i = 0; i < turnOrder.size(); ++i) {
        const Unit* u = turnOrder[i];
        std::cout << "  " << (i + 1) << ". " << u->getName()
                  << " (AGI " << u->getAgi() << ")"
                  << (u->isPlayerControlled() ? "  [Horde]" : "  [Alliance]")
                  << "\n";
    }
    std::cout << "==================================\n";
}

void Combat::printTeamStatus() const {
    std::cout << "\n--- " << playerTeamName << " ---\n";
    for (Unit* u : playerTeam) u->printStatusLine();
    std::cout << "--- " << enemyTeamName << " ---\n";
    for (Unit* u : enemyTeam) u->printStatusLine();
}

bool Combat::teamWiped(const std::vector<Unit*>& team) const {
    for (Unit* u : team) {
        if (u->isAlive()) return false;
    }
    return true;
}

const std::vector<Unit*>& Combat::alliesOf(const Unit* unit) const {
    return unit->isPlayerControlled() ? playerTeam : enemyTeam;
}

const std::vector<Unit*>& Combat::enemiesOf(const Unit* unit) const {
    return unit->isPlayerControlled() ? enemyTeam : playerTeam;
}

bool Combat::run() {
    std::cout << "\n##############################################\n";
    std::cout << "#  " << playerTeamName << "  VS  " << enemyTeamName << "\n";
    std::cout << "##############################################\n";

    buildTurnOrder();
    printTurnOrder();

    int round = 1;
    while (!teamWiped(playerTeam) && !teamWiped(enemyTeam)) {
        std::cout << "\n========== ROUND " << round << " ==========\n";
        printTeamStatus();

        for (Unit* current : turnOrder) {
            // Dead units are skipped (and removed at end of round).
            if (!current->isAlive()) continue;
            if (teamWiped(playerTeam) || teamWiped(enemyTeam)) break;

            std::cout << "\n>>> Current Turn: [" << current->getName() << "] <<<\n";

            const std::vector<Unit*>& allies  = alliesOf(current);
            const std::vector<Unit*>& enemies = enemiesOf(current);

            Action* action = current->chooseAction(allies, enemies);
            if (!action) {
                std::cout << "  " << current->getName() << " has no usable action.\n";
                continue;
            }
            std::vector<Unit*> targets = current->chooseTargets(action, allies, enemies);
            if (targets.empty()) {
                std::cout << "  " << current->getName()
                          << " has no valid target and skips the turn.\n";
                continue;
            }

            action->execute(current, targets);

            if (current->isPlayerControlled()) {
                util::pauseForEnter();
            }
        }

        // Remove dead units from the turn order so they never act again.
        turnOrder.erase(
            std::remove_if(turnOrder.begin(), turnOrder.end(),
                           [](Unit* u) { return !u->isAlive(); }),
            turnOrder.end());

        ++round;
    }

    std::cout << "\n##############################################\n";
    bool playerWon = !teamWiped(playerTeam);
    if (playerWon) {
        std::cout << "#  VICTORY! " << playerTeamName << " wins!\n";
    } else {
        std::cout << "#  DEFEAT... " << enemyTeamName << " wins!\n";
    }
    std::cout << "##############################################\n";
    printTeamStatus();
    return playerWon;
}
