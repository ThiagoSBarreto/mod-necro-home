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

- **All Professions:** Learn configured primary and secondary profession spells when creating a character.
  - Each profession can be enabled or disabled individually.
- **Bank Bags:** Unlock all bank bag slots and configure which bag item will be equipped.
  - The equipped bag can be changed by configuring its item ID.
- **Starting Mount:** Learn riding and receive a racial mount.
  - All initial mounts can be configured by race.
- **Starting Gold:** Players can start with a configurable amount of gold.
- **SQL Scripts:**
  - Starts with 4 36-slot bags.
  - Starts with all basic professions tools.
  - Increase Cloth, Ore and Skins drop amount.
  - Increase item stack-size to 5000.
  - Set all quest items to have 100% drop chance.
  - Includes backup original values.
  - Includes rollback scripts.

> [!NOTE]
> If you don't want those SQL updates, remove them from the `data` folder.

> [!NOTE]
> To restore all SQL modifications, run the `Rollback.sql` (root of the repo).

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

Each feature can be enabled or disabled independently through the configuration file.

### 2.1. All Professions

Configure which professions characters learn when created.

```ini
StartWithAlchemy = 1
StartWithBlacksmithing = 1
StartWithEnchanting = 1
StartWithEngineering = 1
StartWithHerbalism = 1
StartWithInscription = 1
StartWithJewelcrafting = 1
StartWithLeatherworking = 1
StartWithMining = 1
StartWithSkinning = 1
StartWithTailoring = 1
StartWithCooking = 1
StartWithFirstAid = 1
StartWithFishing = 1
```

Each setting accepts:

- `0`: The character does not receive the corresponding profession spells.
- `1`: The character learns the corresponding profession spells when created.

The configurable professions and secondary skills include:

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
StartWithAllBankBags = 1
BankBagItemId = 23162
```

**`StartWithAllBankBags`**

- `0`: Characters do not receive the additional bank bag slots.
- `1`: Characters unlock all bank bag slots.

**`BankBagItemId`**

Defines the item ID of the bag equipped in the unlocked bank slots.

Default: `23162` (Foror's Crate of Endless Resist Gear Storage).

You can change this value to use a different bag item. Set it to `0` if you do not want a bag equipped in those slots.

### 2.3. Starting Mount

```ini
StartWithMount = 1
```

- `0`: Characters do not receive the additional riding skill or starting mount.
- `1`: Characters learn the configured riding skill and receive a mount based on their race.

The mount IDs can be configured individually for each playable race.

| Race | Configuration | Default Mount ID | Mount |
|---|---|---:|---|
| Human | `StartMountIdHuman` | 458 | Brown Horse |
| Orc | `StartMountIdOrc` | 459 | Brown Wolf |
| Dwarf | `StartMountIdDwarf` | 6899 | Brown Ram |
| Night Elf | `StartMountIdNightelf` | 10789 | Spotted Frostsaber |
| Undead | `StartMountIdUndead` | 17462 | Red Skeletal Horse |
| Tauren | `StartMountIdTauren` | 18990 | Brown Kodo |
| Gnome | `StartMountIdGnome` | 17453 | Green Mechanostrider |
| Troll | `StartMountIdTroll` | 17464 | Brown Raptor |
| Blood Elf | `StartMountIdBloodelf` | 34795 | Red Hawkstrider |
| Draenei | `StartMountIdDraenei` | 34406 | Brown Elekk |

Example configuration:

```ini
StartMountIdHuman = 458
StartMountIdOrc = 459
StartMountIdDwarf = 6899
StartMountIdNightelf = 10789
StartMountIdUndead = 17462
StartMountIdTauren = 18990
StartMountIdGnome = 17453
StartMountIdTroll = 17464
StartMountIdBloodelf = 34795
StartMountIdDraenei = 34406
```

Change any mount ID to customize the starting mount for that race.

### 2.4. Starting Gold

```ini
StartGoldAmmount = 5000
```

Sets the amount of gold a character receives when created.

Set the value to `0` if you do not want to grant starting gold.

---

### 2.5. Welcome Message

```ini
ShowWelcomeMessage = 1
```

Controls whether the module displays the welcome message when a player logs in.

- `0`: Disable the welcome message.
- `1`: Enable the welcome message.

---

## 3. Notes

- Features are controlled independently through the configuration file.
- The default configuration enables the listed features and welcome message with the values shown above.
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
