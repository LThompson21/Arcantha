# Arcantha - Game Concept

Arcantha is envisioned as a captivating 2D Action Platformer that blends tactical Hack & Slash combat with deep Metroidvania and Roguelike progression elements. Set in a dark fantasy world brimming with political intrigue and ancient magic, players embark on a journey of self-discovery.

## Table of Contents

* [Game Overview](#game-overview)
* [Core Gameplay Loop](#core-gameplay-loop)
* [Progression & Currencies](#progression--currencies)
* [World & Lore Highlights](#world--lore-highlights)
* [Technical Foundation](#technical-foundation)
* [Building Instructions](#building-instructions)

## Game Overview

Arcantha is a 2D Action Platformer that fuses:
* **Genre Fusion:** Action Platformer & Tactical Combat & Metroidvania/Roguelike
* **Core Premise:** A young protagonist with a hidden magical lineage confronts a tyrannical god-king to reclaim forgotten magic.
* **Target Audience:** Players craving challenging combat, rich lore, and meaningful character progression.

## Core Gameplay Loop

The heart of Arcantha beats with a dynamic cycle of exploration, combat, character growth, and unfolding narrative. Each element seamlessly feeds into the next, creating an engaging and rewarding player experience.

**Exploration & Discovery ➔ Tactical Combat Encounters ➔ Progression & Upgrades ➔ Narrative Advancement ➔ Exploration & Discovery**

This loop repeats, with the expanding hub world and procedural levels offering continuous novelty.

### Key Gameplay Elements:

* **Dynamic Movement:** Emphasis on agility with double jumps, dashes (evolving into magical dashes), wall clings, and ledge grabs.
    * **Acute Perception:** A unique ability (tied to ADHD & magic) allowing for "bullet time" and "pre-exploration" of areas.
* **Tactical Combat:** Switch between swords, spears, and shields. Master light/heavy attacks, blocks, and parries.
    * **Stamina System:** All actions consume stamina, requiring strategic resource management.
* **Evolving Magic System:** Protagonist's magic (purple electricity) vs. Royal "stolen" magic (red/gold lightning) vs. Wild magic (green/blue).
    * **Utility:** Silencing footsteps, healing.
    * **Offensive:** Lightning bolts, arcane waves, summoned weapons.
    * **Defensive:** Arcane shields, teleportation.
    * **Ultimate:** Summoned allies, shape-shifting.

## Progression & Currencies

Arcantha features a hybrid progression system, blending the immediate, run-based gains of Roguelikes with the long-term, persistent unlocks of Metroidvanias. This is fueled by a multi-layered currency system.

* **Essence:**
    * **Type:** Per-Run Resource
    * **Acquisition:** Defeated enemies, minor environmental objects.
    * **Usage:** Temporary stat boosts within current mission at Waypoints.
    * **Note:** Lost upon mission completion or failure.
* **Souls:**
    * **Type:** Persistent Magical Resource
    * **Acquisition:** Tougher enemies, mini-bosses, hidden chests.
    * **Usage:** Minor persistent magical upgrades, unlocking smaller new spells, upgrading Acute Perception.
    * **Note:** Retained with penalty on failure; no penalty on success.
* **Ancient Runes:**
    * **Type:** Rare Metroidvania Unlock Currency
    * **Acquisition:** Bosses, unique challenges, major secrets.
    * **Usage:** Major persistent abilities (Magical Dash, Wall Cling), powerful spells, ultimate abilities, significant stat boosts.
    * **Note:** Never lost upon death.
* **Gold:**
    * **Type:** Common Transactional Currency
    * **Acquisition:** Most enemies, common chests, selling items.
    * **Usage:** Consumables, basic weapon unlocks, cosmetics, hub services.
    * **Note:** Portion lost on mission failure.

## World & Lore Highlights

The world of Arcantha is steeped in ancient history, divine conflicts, and cyclical prophecies. The narrative explores themes of stolen power, true magical lineage, and the fight against millennia-old tyranny.

### Historical Timeline:

* **10,000 Years Ago:** God-King's original theft and corruption of magic.
* **Cyclical Rebellions:** Every few thousand years, a new leader is reincarnated to challenge the God-King.
* **2,000 Years Ago:** The last, most violent ancient war. Believed to be the eradication of true magic.
* **Year 1172 (Present):** The game's events unfold in the "Golden Age" (royal propaganda).

### Key Factions & Entities:

* **Arcantha (Sentient Magic):** The embodiment of true magic. Strict, witty, guides the protagonist. Motivations: spread true magic, eliminate the corrupt royal family.
* **The God-King & Malazor Religion:** Millennia-old tyrant using stolen, corrupted magic (red/gold lightning). His rule is justified by "The Divine Edict of Malazor," which demonizes true magic and preaches his divine right.
* **The Protagonist:** An 18-year-old with undiagnosed ADHD, whose unique perceptions are tied to his latent magical abilities and reincarnation from a line of rebel leaders.

### The Cycle of Rebellion: A Core Narrative Theme

A central theme in Arcantha is the recurring cycle of rebellion against the God-King's oppressive regime. Every few thousand years, a figure destined to challenge the established order is reincarnated. The protagonist is the latest in this long line, carrying the weight of past failures and the hope for a definitive change. The game's narrative will explore this legacy, with the "We Will Be Back" incantation from the last great war serving as a powerful, literal promise fulfilled through the protagonist.

## Technical Foundation

Arcantha is planned with a robust technical foundation to support its dynamic gameplay and rich world. The choice of C++ and specialized libraries aims for performance and flexibility.

* **Language:** C++
* **Windowing:** GLFW & OpenGL
* **Physics:** Box2D
* **Audio:** OpenAL
* **Debug GUI:** Dear ImGui
* **Assets:** stb_image
* **Math:** glm
* **Build:** MSVC & CMake
* **Version Control:** Git

## Building Instructions

This project uses CMake for its build system. All necessary external libraries are included directly within the `external` folder, so no additional dependencies need to be installed system-wide.

To build the project, follow these steps:

1.  **Clone the repository:**
    ```bash
    git clone [repository_url]
    cd [repository_name]
    ```

2.  **Create a build directory:**
    It's good practice to build outside the source directory.
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure CMake:**
    Run CMake to generate the build files for your chosen compiler (e.g., Visual Studio on Windows, Makefiles on Linux/macOS).
    ```bash
    cmake ..
    ```
    If you are on Windows using Visual Studio, you might specify the generator:
    ```bash
    cmake .. -G "Visual Studio 17 2022" # Or your specific VS version
    ```

4.  **Build the project:**
    After configuration, compile the project.
    ```bash
    cmake --build .
    ```
    This command will build all targets defined in the CMakeLists.txt.

5.  **Run the executable:**
    Once built, the executable will be located in a subdirectory within your `build` folder (e.g., `build/Debug` or `build/Release` on Windows, `build` on Linux/macOS). Navigate to that directory and run the game.

    Example (Linux/macOS):
    ```bash
    ./Arcantha
    ```
    Example (Windows - assuming `Arcantha.exe` is the output):
    ```bash
    .\Debug\Arcantha.exe
    ```
    (Path might vary based on your CMake configuration and build type)

---

© 2025 Arcantha Game Concept. All ideas presented are part of a fictional game development document.