#include "NecroHome.h"

#include "Config.h"
#include "DatabaseEnv.h"
#include "Item.h"
#include "Log.h"

namespace
{
    void LearnAllProfessionsForNewPlayer(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("StartWithAllProfessions", false))
        {
            return;
        }

        static constexpr uint32 professionSpells[] =
        {
            2259,   // Alchemy
            2018,   // Blacksmithing
            7411,   // Enchanting
            4036,   // Engineering
            2366,   // Herbalism
            45357,  // Inscription
            25229,  // Jewelcrafting
            2108,   // Leatherworking
            2575,   // Mining
            8613,   // Skinning
            3908,   // Tailoring
            2550,   // Cooking
            3273,   // First Aid
            7620    // Fishing
        };

        for (uint32 spellId : professionSpells)
        {
            if (!player->IsInWorld())
            {
                player->addSpell(spellId, SPEC_MASK_ALL, true);
            }
            else
            {
                player->learnSpell(spellId);
            }
        }
    }

    void GivePlayerBankBagsForNewPlayer(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("StartWithAllBankBags", false))
        {
            return;
        }

        constexpr uint32 bagEntry = 23162;

        player->SetBankBagSlotCount(BANK_SLOT_BAG_END - BANK_SLOT_BAG_START);

        CharacterDatabaseTransaction trans =
            CharacterDatabase.BeginTransaction();

        for (uint8 slot = BANK_SLOT_BAG_START;
             slot < BANK_SLOT_BAG_END;
             ++slot)
        {
            Item* bag = Item::CreateItem(bagEntry, 1, player);

            if (!bag)
            {
                continue;
            }

            bag->SaveToDB(trans);
            player->EquipItem(slot, bag, true);
        }

        CharacterDatabase.CommitTransaction(trans);
    }

    void LearnInitialMountForNewPlayer(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("StartWithMount", false))
        {
            return;
        }

        constexpr uint32 ridingSpellId = 33388;

        if (!player->IsInWorld())
        {
            player->addSpell(ridingSpellId, SPEC_MASK_ALL, true);
        }
        else
        {
            player->learnSpell(ridingSpellId);
        }

        uint32 mountSpellId = 0;

        switch (player->getRace())
        {
            case RACE_HUMAN:
                mountSpellId = 458;     // Brown Horse
                break;

            case RACE_ORC:
                mountSpellId = 459;     // Brown Wolf
                break;

            case RACE_DWARF:
                mountSpellId = 6899;    // Brown Ram
                break;

            case RACE_NIGHTELF:
                mountSpellId = 10789;   // Spotted Frostsaber
                break;

            case RACE_UNDEAD_PLAYER:
                mountSpellId = 17462;   // Red Skeletal Horse
                break;

            case RACE_TAUREN:
                mountSpellId = 18990;   // Brown Kodo
                break;

            case RACE_GNOME:
                mountSpellId = 17453;   // Green Mechanostrider
                break;

            case RACE_TROLL:
                mountSpellId = 17464;   // Brown Raptor
                break;

            case RACE_BLOODELF:
                mountSpellId = 34795;   // Red Hawkstrider
                break;

            case RACE_DRAENEI:
                mountSpellId = 34406;   // Brown Elekk
                break;

            default:
                break;
        }

        if (mountSpellId == 0)
        {
            return;
        }

        if (!player->IsInWorld())
        {
            player->addSpell(mountSpellId, SPEC_MASK_ALL, true);
        }
        else
        {
            player->learnSpell(mountSpellId);
        }
    }
}

NecroHome::NecroHome()
    : PlayerScript("NecroHome")
{
}

void NecroHome::OnPlayerCreate(Player* player)
{
    LearnAllProfessionsForNewPlayer(player);
    LearnInitialMountForNewPlayer(player);
    GivePlayerBankBagsForNewPlayer(player);
}

void AddSC_mod_necro_home()
{
    new NecroHome();
}