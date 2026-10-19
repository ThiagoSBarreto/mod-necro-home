# NecroHome Module

A bunch of quality-of-life improvements and shenanigans to save time while playing solo or enjoying a more casual gameplay experience.

[![GitHub Sponsors](https://img.shields.io/badge/GitHub%20Sponsors-support-ff69b4?logo=github)](https://github.com/sponsors/ThiagoSBarreto)
[![Buy Me a Coffee](https://img.shields.io/badge/Buy%20me%20a%20coffee-FFDD00?logo=buymeacoffee&logoColor=black&style=flat)](https://buymeacoffee.com/thiagosbarreto)
![World of Warcraft Client](https://img.shields.io/badge/World%20of%20Warcraft%20Client-3.3.5a-blue)

---

## Description

NecroHome is a collection of quality-of-life improvements and gameplay tweaks for AzerothCore, designed to save time and make solo play or casual gameplay more enjoyable.

The goal is to reduce some of the repetitive tasks and limitations that can slow down the experience, especially when playing alone.

Features can be enabled or disabled individually through the module configuration file.

---

## Features

- **All Professions:** Learn all supported primary and secondary profession spells when creating a character.
- **Bank Bags:** Unlock all bank bag slots and receive 36-slot bags.
- **Starting Mount:** Learn riding and receive a racial mount.
- **Starting Gold:** Players can start with gold.
- **SQL Scripts:** 
    - Starts with 4 36-slot bags
    - Starts with all basic professions tools
    - Incress Cloth, Ore and Skins drop ammount
    - Incress item stack-size to 5000
    - Set all quest items to have 100% drop chance
    - Includes backup original values
    - Includes rollback scripts
> [!NOTE]
> If you don't want those SQL updates, remove them from the ```data/sql/world/base```
> To restore all SQL modifications, run the Rollback.sql (root of the repo)

---

## 1. Installation

### 1.1. Clone the Module

Clone this repository into the `modules` directory of your AzerothCore source tree.

Example:

```bash
cd /path/to/azerothcore/modules

git clone https://github.com/NecroHome/mod-necro-home.git
```

### 1.2. Rebuild AzerothCore

After cloning the module, rebuild AzerothCore.

### 1.3. Install the Module Configuration

The repository includes a default configuration template:

```text
mod-necro-home.conf.dist
```

Copy it into your AzerothCore module configuration directory and rename it to:

```text
mod-necro-home.conf
```

Example:

```bash
cp /path/to/azerothcore/modules/mod-necro-home.conf.dist \
   /path/to/azerothcore/env/dist/etc/modules/mod-necro-home.conf
```

If your AzerothCore installation automatically copies module configuration files, verify whether the file has already been installed.

### 1.4. Configure the Module

Edit `mod-necro-home.conf` and enable the features you want.

Restart `worldserver` after changing the configuration.

---

## 2. Configuration

Each feature can be enabled independently.

### 2.1. All Professions

```ini
StartWithAllProfessions = 0
```

- `0` (default): Characters do not receive the additional profession spells.
- `1`: Characters learn all configured profession spells when created.

The configured spells include:

- Alchemy
- Blacksmithing
- Enchanting
- Engineering
- Herbalism
- Inscription
- Jewelcrafting
- Leatherworking
- Mining
- Skinning
- Tailoring
- Cooking
- First Aid
- Fishing

> [!NOTE]
> This feature teaches the configured spells. It does not automatically grant maximum profession skill, every recipe, or every specialization.

### 2.2. Bank Bags

```ini
StartWithAllBankBags = 0
```

- `0` (default): Characters do not receive additional bank bags.
- `1`: Characters unlock all bank bag slots and receive 36-slot bags.

This feature is intended to reduce inventory management and storage limitations.

### 2.3. Starting Mount

```ini
StartWithMount = 0
```

- `0` (default): Characters do not receive the additional riding spell or racial mount.
- `1`: Characters learn the configured riding spell and receive a mount based on their race.

Supported races:

| Race | Mount |
|---|---|
| Human | Brown Horse |
| Orc | Brown Wolf |
| Dwarf | Brown Ram |
| Night Elf | Spotted Frostsaber |
| Undead | Red Skeletal Horse |
| Tauren | Brown Kodo |
| Gnome | Green Mechanostrider |
| Troll | Brown Raptor |
| Blood Elf | Red Hawkstrider |
| Draenei | Brown Elekk |

---

## 3. Notes

- Features are controlled independently through the configuration file.
- The default configuration leaves all features disabled.
- The module is intended for AzerothCore with the World of Warcraft 3.3.5a client.
- The current implementation handles starting bonuses during character creation.
- Existing characters are not automatically updated by the character-creation hook.

> [!WARNING]
> Test the module on a development server before enabling it on a live realm.

---

## 4. Author

**ThiagoSBarreto**

LesmaSamuray

---

## 5. Credits

Thanks to the AzerothCore team and community for maintaining the project and providing the foundation for custom modules.

---

## 6. Update

To update the module:

1. Navigate to the modules directory:

   ```bash
   cd /path/to/azerothcore/modules/mod-necro-home
   ```

2. Pull the latest changes:

   ```bash
   git pull
   ```

3. Rebuild AzerothCore if the module source has changed.
4. Review any changes to the configuration file.
5. Restart `worldserver`.

---

