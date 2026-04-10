#ifndef COMBAT_H
#define COMBAT_H

#include <string>
#include <vector>

class Unit;

// Owns the battle loop. Does NOT own the unit pointers (main does);
// it just operates on the supplied teams.
class Combat {
public:
    Combat(const std::string& playerTeamName,
           const std::vector<Unit*>& playerTeam,
           const std::string& enemyTeamName,
           const std::vector<Unit*>& enemyTeam);

    // Runs until one side is wiped. Returns true if the player side won.
    bool run();

private:
    void buildTurnOrder();
    void printTurnOrder() const;
    void printTeamStatus() const;
    bool teamWiped(const std::vector<Unit*>& team) const;

    // Returns the side opposite the given unit.
    const std::vector<Unit*>& alliesOf(const Unit* unit) const;
    const std::vector<Unit*>& enemiesOf(const Unit* unit) const;

    std::string playerTeamName;
    std::string enemyTeamName;
    std::vector<Unit*> playerTeam;
    std::vector<Unit*> enemyTeam;
    std::vector<Unit*> turnOrder;
};

#endif
