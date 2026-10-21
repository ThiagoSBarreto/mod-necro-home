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
    - Configurable wich profession will the player start with
- **Inventory Bags:** Start with bags.
    - The initial bags can be changed or set to `0`, so nome will be equiped
- **Bank Bags:** Unlock all bank bag slots and receive bags.
    - The equiped bag can be changed or set to `0`, so nome will be equiped
- **Starting Mount:** Learn riding and receive a racial mount.
    - All initial mounts can be configured by race
- **Start with Tools:** Player can start with professions tools
    - Configurable wich tools the player start with
- **Starting Gold:** Players can start with gold.
    - Configurable wich ammount of gold player start with
- **SQL Scripts:**
    - Incress Cloth, Ore and Skins drop ammount
    - Incress item stack-size to 5000
    - Set all quest items to have 100% drop chance
    - Includes backup original values
    - Includes rollback scripts

> [!NOTE]
> If you don't want those SQL updates, remove them from the ```data``` folder

> [!NOTE]
> To restore all SQL modifications, run the Rollback.sql (root of the repo)

> [!NOTE]
> Nome of this works for Bots or Headless clients

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

### 2.1. Welcome Message

Configure which professions characters learn when created.

```ini
NecroHome.ShowWelcomeMessage = 1
```

- `0`: Disables the welcome message displayed when a player logs in.
- `1` (default): Displays the message "This server uses NecroHome module" when a player logs in.

### 2.2. All Professions

Each profession can be enabled or disabled independently.

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

- `0`: The character does not receive the corresponding profession spells.
- `1` (default): The character learns the corresponding profession spells when created.

> [!NOTE]
> This feature teaches the configured spells. It does not automatically grant maximum profession skill, every recipe, or every specialization.

### 2.3. Inventory Bags

```ini
NecroHome.StartWithAllBags = 1
NecroHome.BagItemId = 23162
```

**StartWithAllBags**

- `0`: Characters do not receive additional inventory bags.
- `1` (default): Characters receive bags in all four inventory bag slots.

**BagItemId**

Defines the item ID of the bag equipped in the inventory bag slots.

- `23162` (default): Foror's Crate of Endless Resist Gear Storage.
- `0`: No bag will be equipped.

Change the item ID to use a different bag.

### 2.4. Bank Bags

```ini
NecroHome.StartWithAllBankBags = 1
NecroHome.BankBagItemId = 23162
```

**StartWithAllBankBags**

- `0`: Characters do not receive additional bank bag slots or bags.
- `1` (default): Characters unlock all bank bag slots and receive bags.

**BankBagItemId**

Defines the item ID of the bag equipped in the bank bag slots.

- `23162` (default): Foror's Crate of Endless Resist Gear Storage.
- `0`: No bag will be equipped.

Change the item ID to use a different bag.

### 2.5. Starting Mount

```ini
NecroHome.StartWithMount = 1
```

- `0`: Characters do not receive the additional riding spell or racial mount.
- `1` (default): Characters learn the configured riding spell and receive a mount based on their race.

The mount IDs can be configured independently for each supported race.

```ini
NecroHome.StartMountIdHuman = 458
NecroHome.StartMountIdOrc = 459
NecroHome.StartMountIdDwarf = 6899
NecroHome.StartMountIdNightelf = 10789
NecroHome.StartMountIdUndead = 17462
NecroHome.StartMountIdTauren = 18990
NecroHome.StartMountIdGnome = 17453
NecroHome.StartMountIdTroll = 17464
NecroHome.StartMountIdBloodelf = 34795
NecroHome.StartMountIdDraenei = 34406
```

| Race | Default Mount |
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

Change the corresponding mount ID to use a different mount for a race.

### 2.6. Starting Tools

Each starting tool can be enabled or disabled independently.

```ini
NecroHome.StartWithMiningPink = 1
NecroHome.StartWithSkinningKnife = 1
NecroHome.StartWithFishingPole = 1
NecroHome.StartWithBlacksmithHammer = 1
NecroHome.StartWithFlintAndTinder = 1
```

- `0`: The character does not receive the corresponding tool.
- `1` (default): The character receives the corresponding tool when created.

Available tools:

- Mining Pick
- Skinning Knife
- Fishing Pole
- Blacksmith Hammer
- Flint and Tinder

### 2.7. Starting Simple Wood

```ini
NecroHome.StartWithSimpleWood = 1
NecroHome.SimpleWoodStartAmmount = 5000
```

**StartWithSimpleWood**

- `0`: Characters do not receive Simple Wood.
- `1` (default): Characters receive Simple Wood when created.

**SimpleWoodStartAmmount**

Defines how many Simple Wood items the character receives.

- `5000` (default): Characters start with 5000 Simple Wood.

### 2.8. Starting Gold

```ini
NecroHome.StartGoldAmmount = 5000
```

Defines the amount of gold characters receive when created.

- `5000` (default): Characters start with 5000 gold.

Change the value to set a different starting amount.
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
