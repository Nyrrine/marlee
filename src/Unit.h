#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Action;

// Abstract battle participant. Stats are POD; behavior (input/AI) is virtual.
class Unit {
public:
    Unit(const std::string& name,
         const std::string& title,
         int hp, int mp, int pow, int vit, int agi, int dex);
    virtual ~Unit();

    // Stat accessors
    const std::string& getName()  const { return name; }
    const std::string& getTitle() const { return title; }
    int getHp()    const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getMp()    const { return mp; }
    int getMaxMp() const { return maxMp; }
    int getPow()   const { return pow; }
    int getVit()   const { return vit; }
    int getAgi()   const { return agi; }
    int getDex()   const { return dex; }
    bool isAlive() const { return hp > 0; }

    // Mutators used by Action subclasses
    void takeDamage(int amount);
    void heal(int amount);
    void spendMp(int amount);

    const std::vector<Action*>& getActions() const { return actions; }

    // Each unit owns its actions and deletes them on destruction.
    void addAction(Action* action);

    // Polymorphic input strategy. Combat calls these on the active unit.
    virtual Action* chooseAction(const std::vector<Unit*>& allies,
                                 const std::vector<Unit*>& enemies) = 0;
    virtual std::vector<Unit*> chooseTargets(Action* action,
                                             const std::vector<Unit*>& allies,
                                             const std::vector<Unit*>& enemies) = 0;

    virtual bool isPlayerControlled() const = 0;

    void printStatusLine() const;

protected:
    std::string name;
    std::string title;
    int maxHp, hp;
    int maxMp, mp;
    int pow, vit, agi, dex;

    std::vector<Action*> actions;
};

#endif
