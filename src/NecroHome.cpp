#include "NecroHome.h"

#include "Player.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Item.h"
#include "Log.h"

namespace
{
    void LearnAllProfessionsForNewPlayer(Player* player)
    {
        /*
        2259    Alchemy
        2018    Blacksmithing
        7411    Enchanting
        4036    Engineering
        2366    Herbalism
        45357   Inscription
        25229   Jewelcrafting
        2108    Leatherworking
        2575    Mining
        8613    Skinning
        3908    Tailoring
        2550    Cooking
        3273    First Aid
        7620    Fishing
        */

        if (sConfigMgr->GetOption<bool>("StartWithAlchemy", false)) {
            player->learnSpell(2259);
        }

        if (sConfigMgr->GetOption<bool>("StartWithBlacksmithing", false)) {
            player->learnSpell(2018);
        }

        if (sConfigMgr->GetOption<bool>("StartWithEnchanting", false)) {
            player->learnSpell(7411);
        }

        if (sConfigMgr->GetOption<bool>("StartWithEngineering", false)) {
            player->learnSpell(4036);
        }

        if (sConfigMgr->GetOption<bool>("StartWithHerbalism", false)) {
            player->learnSpell(2366);
        }

        if (sConfigMgr->GetOption<bool>("StartWithInscription", false)) {
            player->learnSpell(45357);
        }

        if (sConfigMgr->GetOption<bool>("StartWithJewelcrafting", false)) {
            player->learnSpell(25229);
        }

        if (sConfigMgr->GetOption<bool>("StartWithLeatherworking", false)) {
            player->learnSpell(2108);
        }

        if (sConfigMgr->GetOption<bool>("StartWithMining", false)) {
            player->learnSpell(2575);
        }

        if (sConfigMgr->GetOption<bool>("StartWithSkinning", false)) {
            player->learnSpell(8613);
        }

        if (sConfigMgr->GetOption<bool>("StartWithTailoring", false)) {
            player->learnSpell(3908);
        }

        if (sConfigMgr->GetOption<bool>("StartWithCooking", false)) {
            player->learnSpell(2550);
        }

        if (sConfigMgr->GetOption<bool>("StartWithFirstAid", false)) {
            player->learnSpell(3273);
        }
        
        if (sConfigMgr->GetOption<bool>("StartWithFishing", false)) {
            player->learnSpell(7620);
        }
    }

    void GivePlayerBankBagsForNewPlayer(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("StartWithAllBankBags", false))
        {
            return;
        }

        uint32 bagEntry = sConfigMgr->GetOption<uint32>("BankBagItemId", 0);

        if (bagEntry <= 0) {
            return;
        }

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
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdHuman", 0);
                break;

            case RACE_ORC:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdOrc", 0);
                break;

            case RACE_DWARF:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdDwarf", 0);
                break;

            case RACE_NIGHTELF:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdNightelf", 0);
                break;

            case RACE_UNDEAD_PLAYER:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdUndead", 0);
                break;

            case RACE_TAUREN:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdTauren", 0);
                break;

            case RACE_GNOME:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdGnome", 0);
                break;

            case RACE_TROLL:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdTroll", 0);
                break;

            case RACE_BLOODELF:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdBloodelf", 0);
                break;

            case RACE_DRAENEI:
                mountSpellId = sConfigMgr->GetOption<uint32>("StartMountIdDraenei", 0);
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

    void GiveInitialGold(Player* player)
    {
        uint32 initialGold = sConfigMgr->GetOption<uint32>("StartGoldAmmount", 0);
        constexpr uint32 copperPerGold = 10000;

        player->ModifyMoney(initialGold * copperPerGold);
    }
}

NecroHome::NecroHome()
    : PlayerScript("NecroHome")
{
}

void NecroHome::OnPlayerFirstLogin(Player* player)
{
    LearnAllProfessionsForNewPlayer(player);
    LearnInitialMountForNewPlayer(player);
    GivePlayerBankBagsForNewPlayer(player);
    GiveInitialGold(player);
}

void NecroHome::OnPlayerLogin(Player* player) 
{
    if (!sConfigMgr->GetOption<bool>("ShowWelcomeMessage", false)) {
        return;
    }
    
    ChatHandler(player->GetSession()).PSendSysMessage("This server uses NecroHome module");
}

void Addmod_necro_homeScripts()
{
    new NecroHome();
}