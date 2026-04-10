#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

class Unit;

// Abstract base for every action a unit can perform.
// Polymorphic execute() lets Combat dispatch any action without type-checks.
class Action {
public:
    Action(const std::string& name, int mpCost);
    virtual ~Action() = default;

    const std::string& getName() const { return name; }
    int getMpCost() const { return mpCost; }

    bool canCast(const Unit& user) const;

    // Targets are decided by the Unit (player prompt or AI) before execute is called.
    virtual void execute(Unit* user, const std::vector<Unit*>& targets) = 0;

    // True for skills that target one opposing unit (drives manual targeting UI).
    virtual bool isSingleEnemyTarget() const { return false; }
    virtual bool isMultiEnemyTarget()  const { return false; }
    virtual bool isSingleAllyTarget()  const { return false; }

protected:
    std::string name;
    int mpCost;

    // Shared damage helpers used by every damaging subclass.
    static int randomizedPow(int basePow);
    static int computeDamage(int basePow, double coefficient, int defenderVit);
    static int computeHitPercent(int attackerDex, int defenderAgi);
};

#endif
