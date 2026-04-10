# Turn-Based Combat — Horde vs Alliance

A 3v3 turn-based console RPG written in C++17. Play the **Horde** against an
AI-controlled **Alliance** in a Warcraft III-themed skirmish. Built as a school
quiz project (CSB Quiz 04) with strict OOP — every action and unit is a
polymorphic class, every game object is heap-allocated and properly cleaned up.

```
+--------------------------------------------+
|         WARCRAFT III: TURN-BASED           |
|         HORDE   vs   ALLIANCE              |
+--------------------------------------------+
```

## Features

- 3v3 turn-based combat with turn order decided by AGI
- Four polymorphic action types: Basic Attack, Single-Target, Multi-Target, Heal
- Player menu input with full validation (bad input and out-of-MP both rejected)
- Enemy AI: 50% chance to use a random affordable skill, otherwise basic attack
- **Manual targeting** for player skills (bonus feature) — pick exactly who to hit or heal
- Crit (20% chance, +20% damage) and miss (clamped 20–80% hit rate) on basic attacks
- Multi-target damage re-randomized per target
- Dead units removed from the turn order, win/lose detected on team wipe
- All `Unit` and `Action` objects allocated with `new` and freed on shutdown

## Roster

**Horde (you)**

| Unit | Class | Skill |
|---|---|---|
| Cairne Bloodhoof | Tauren Chieftain | *Shockwave* (multi-target) |
| Grom Hellscream | Blademaster | *Mirror Image Strike* (single-target) |
| Vol'jin | Shadow Hunter | *Healing Wave* (heal) |

**Alliance (AI)**

| Unit | Class | Skill |
|---|---|---|
| Jaina Proudmoore | Archmage | *Blizzard* (multi-target) |
| Muradin Bronzebeard | Mountain King | *Storm Bolt* (single-target) |
| Uther Lightbringer | Paladin | *Holy Light* (heal) |

## Requirements

- A C++17 compiler (`g++` 7+, `clang++` 5+, or MSVC 2017+)
- `make` (only if you want to use the included Makefile)
- Git (only if you want to clone the repo)

That's it. No external libraries, no dependencies, no package manager.

## Get the code

```bash
git clone https://github.com/Nyrrine/marlee.git
cd marlee
```

Or download the ZIP from GitHub and extract it anywhere.

## Build & run

### Linux / macOS / WSL (recommended)

Install a compiler if you don't already have one:

```bash
# Ubuntu / Debian / WSL
sudo apt install g++ make

# Fedora
sudo dnf install gcc-c++ make

# macOS (installs the Xcode command line tools)
xcode-select --install
```

Then build and play:

```bash
make
./turn-based-combat
```

Or in one step: `make run`.

To clean compiled files: `make clean`.

### Windows (MinGW-w64)

1. Install [MSYS2](https://www.msys2.org/) and run `pacman -S mingw-w64-ucrt-x86_64-gcc make`.
2. Open the **UCRT64** shell from the MSYS2 menu.
3. `cd` into the project folder and run `make`.
4. Run `./turn-based-combat.exe`.

### Windows (Visual Studio)

1. Open Visual Studio → **File → New → Project From Existing Code** → C++ → point it at this folder.
2. Add every `.cpp` file under `src/` to the project.
3. Set the **C++ Language Standard** to ISO C++17 (Project Properties → C/C++ → Language).
4. Build → Run.

### Manual one-liner (no make, no IDE)

```bash
g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o turn-based-combat
./turn-based-combat
```

## How to play

On each Horde unit's turn you'll see a menu of actions:

```
  -- Grom Hellscream (Blademaster), choose your action --
    1) Hellscream Slash
    2) Mirror Image Strike  (MP: 5)
  >
```

Type the number of the action you want and press Enter. If you pick a single-target
skill or a heal, you'll get a follow-up prompt to choose the target from a list of
alive units. Multi-target skills hit everyone automatically. Basic attacks pick a
random opposing unit (per spec).

Bad input is rejected and re-prompted. If you don't have enough MP for a skill,
you'll be told and asked to pick again. The game ends as soon as one team is wiped.

**Win condition:** wipe the Alliance. **Lose condition:** the Alliance wipes you.

## Project layout

```
.
├── Makefile               # build script (g++ -std=c++17 -Wall -Wextra)
├── README.md
├── .gitignore
└── src/
    ├── main.cpp            # team setup, allocates units with `new`, runs Combat
    ├── Combat.h / .cpp     # battle loop, turn order, win check
    ├── Unit.h / .cpp       # abstract base — stats + virtual chooseAction/chooseTargets
    ├── PlayerUnit.h / .cpp # menu-driven player input + manual targeting
    ├── EnemyUnit.h / .cpp  # AI: 50% skill / basic attack, lowest-HP targeting
    ├── Action.h / .cpp     # abstract base — name, mpCost, virtual execute()
    ├── BasicAttack.h / .cpp        # crit + miss, no MP
    ├── SingleTargetSkill.h / .cpp  # coeff 2.2, 5 MP
    ├── MultiTargetSkill.h / .cpp   # coeff 0.9, 4 MP, re-rolled per target
    ├── HealSkill.h / .cpp          # 30% max HP, 3 MP
    └── Util.h / .cpp       # rng, clamp, prompt helpers
```

## Game rules (in case you want to balance it)

- **Damage:** `floor(randomizedPow * coefficient) - defenderVit`, minimum 1
- **Randomized POW:** uniform in `[POW, POW + floor(0.2*POW) - 1]`
- **Hit rate:** `clamp(DEX_attacker * 100 / AGI_defender, 20, 80)` percent
- **Basic Attack:** coefficient 1.0, 20% crit chance for +20% damage, 0 MP
- **Single-Target Skill:** coefficient 2.2, no crit/miss, 5 MP
- **Multi-Target Skill:** coefficient 0.9, no crit/miss, 4 MP
- **Heal:** restores 30% of target's max HP (min 1), 3 MP

Stats live in `src/main.cpp` — tweak the constructor calls and rebuild.

## Troubleshooting

- **`g++: command not found`** — install a compiler (see Requirements).
- **`make: command not found` on Windows** — use the manual one-liner above, or install MSYS2.
- **`error: 'std::stoi' was not declared`** — your compiler is too old. You need C++11 at minimum; the project targets C++17.
- **Game looks garbled in cmd.exe** — use Windows Terminal, PowerShell, or any modern terminal that handles UTF-8.

## License

Coursework. Do whatever you want with it.
