#include <iostream>
#include <vector>

#include "BasicAttack.h"
#include "Combat.h"
#include "EnemyUnit.h"
#include "HealSkill.h"
#include "MultiTargetSkill.h"
#include "PlayerUnit.h"
#include "SingleTargetSkill.h"
#include "Unit.h"
#include "Util.h"

namespace {

    // Builds the Horde — player-controlled.
    // Stat budget tuned so neither side dominates and games last 4-7 rounds.
    std::vector<Unit*> buildHorde() {
        std::vector<Unit*> team;

        // Cairne Bloodhoof — Tauren Chieftain — Multi-target tank.
        Unit* cairne = new PlayerUnit(
            "Cairne Bloodhoof", "Tauren Chieftain",
            /*hp*/ 220, /*mp*/ 12, /*pow*/ 32, /*vit*/ 18, /*agi*/ 18, /*dex*/ 24);
        cairne->addAction(new BasicAttack("Totem Smash"));
        cairne->addAction(new MultiTargetSkill("Shockwave"));
        team.push_back(cairne);

        // Grom Hellscream — Blademaster — single-target striker.
        Unit* grom = new PlayerUnit(
            "Grom Hellscream", "Blademaster",
            /*hp*/ 170, /*mp*/ 14, /*pow*/ 42, /*vit*/ 12, /*agi*/ 30, /*dex*/ 32);
        grom->addAction(new BasicAttack("Hellscream Slash"));
        grom->addAction(new SingleTargetSkill("Mirror Image Strike"));
        team.push_back(grom);

        // Vol'jin — Shadow Hunter — healer.
        Unit* voljin = new PlayerUnit(
            "Vol'jin", "Shadow Hunter",
            /*hp*/ 160, /*mp*/ 16, /*pow*/ 26, /*vit*/ 14, /*agi*/ 22, /*dex*/ 26);
        voljin->addAction(new BasicAttack("Voodoo Hex"));
        voljin->addAction(new HealSkill("Healing Wave"));
        team.push_back(voljin);

        return team;
    }

    // Builds the Alliance — AI-controlled.
    std::vector<Unit*> buildAlliance() {
        std::vector<Unit*> team;

        // Jaina Proudmoore — Archmage — multi-target nuker.
        Unit* jaina = new EnemyUnit(
            "Jaina Proudmoore", "Archmage",
            /*hp*/ 160, /*mp*/ 14, /*pow*/ 36, /*vit*/ 10, /*agi*/ 20, /*dex*/ 26);
        jaina->addAction(new BasicAttack("Arcane Bolt"));
        jaina->addAction(new MultiTargetSkill("Blizzard"));
        team.push_back(jaina);

        // Muradin Bronzebeard — Mountain King — single-target hammer.
        Unit* muradin = new EnemyUnit(
            "Muradin Bronzebeard", "Mountain King",
            /*hp*/ 210, /*mp*/ 12, /*pow*/ 38, /*vit*/ 16, /*agi*/ 16, /*dex*/ 24);
        muradin->addAction(new BasicAttack("Hammer Swing"));
        muradin->addAction(new SingleTargetSkill("Storm Bolt"));
        team.push_back(muradin);

        // Uther the Lightbringer — Paladin — healer.
        Unit* uther = new EnemyUnit(
            "Uther Lightbringer", "Paladin",
            /*hp*/ 180, /*mp*/ 16, /*pow*/ 28, /*vit*/ 18, /*agi*/ 24, /*dex*/ 26);
        uther->addAction(new BasicAttack("Hammer of Justice"));
        uther->addAction(new HealSkill("Holy Light"));
        team.push_back(uther);

        return team;
    }

    // Frees a team allocated with new. Unit destructor cleans up its actions.
    void deleteTeam(std::vector<Unit*>& team) {
        for (Unit* u : team) {
            delete u;
        }
        team.clear();
    }

    void printIntro() {
        std::cout << "+--------------------------------------------+\n";
        std::cout << "|         WARCRAFT III: TURN-BASED           |\n";
        std::cout << "|         HORDE   vs   ALLIANCE              |\n";
        std::cout << "+--------------------------------------------+\n";
        std::cout << "  3v3 turn-based combat. AGI decides turn order.\n";
        std::cout << "  Wipe the enemy team to claim victory.\n\n";
    }
}

int main() {
    util::seedRng();
    printIntro();

    std::vector<Unit*> horde    = buildHorde();
    std::vector<Unit*> alliance = buildAlliance();

    Combat battle("Horde", horde, "Alliance", alliance);
    battle.run();

    deleteTeam(horde);
    deleteTeam(alliance);

    std::cout << "\nThanks for playing! Lok'tar ogar!\n";
    return 0;
}
