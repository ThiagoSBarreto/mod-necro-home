#include "NecroHome.h"

#include "Player.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Item.h"
#include "Log.h"

namespace
{
    template <typename Session>
    bool IsBotSession(Session const *session)
    {
        if constexpr (requires { session->IsBot(); })
        {
            return session->IsBot();
        }
        else
        {
            return false;
        }
    }

    template <typename Session>
    bool IsHeadlessClientSession(Session const *session)
    {
        if constexpr (requires { session->IsHeadlessClient(); })
        {
            return session->IsHeadlessClient();
        }
        else
        {
            return false;
        }
    }

    void GivePlayerInitialProfessions(Player *player)
    {
        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithAlchemy", false))
        {
            player->learnSpell(2259);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithBlacksmithing", false))
        {
            player->learnSpell(2018);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithEnchanting", false))
        {
            player->learnSpell(7411);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithEngineering", false))
        {
            player->learnSpell(4036);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithHerbalism", false))
        {
            player->learnSpell(2366);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithInscription", false))
        {
            player->learnSpell(45357);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithJewelcrafting", false))
        {
            player->learnSpell(25229);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithLeatherworking", false))
        {
            player->learnSpell(2108);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithMining", false))
        {
            player->learnSpell(2575);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithSkinning", false))
        {
            player->learnSpell(8613);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithTailoring", false))
        {
            player->learnSpell(3908);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithCooking", false))
        {
            player->learnSpell(2550);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithFirstAid", false))
        {
            player->learnSpell(3273);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithFishing", false))
        {
            player->learnSpell(7620);
        }
    }

    void GivePlayerInitialBags(Player *player)
    {
        if (!sConfigMgr->GetOption<bool>("NecroHome.StartWithAllBags", false))
        {
            return;
        }

        uint32 bagEntry = sConfigMgr->GetOption<uint32>("NecroHome.BagItemId", 0);

        if (bagEntry <= 0)
        {
            return;
        }

        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

        for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
        {
            Item *bag = Item::CreateItem(bagEntry, 1, player);
            if (!bag)
            {
                continue;
            }

            bag->SaveToDB(trans);
            player->EquipItem(slot, bag, true);
        }

        CharacterDatabase.CommitTransaction(trans);
    }

    void GivePlayerInitialTools(Player *player)
    {
        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithMiningPick", false))
        {
            player->AddItem(2901, 1);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithSkinningKnife", false))
        {
            player->AddItem(7005, 1);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithFishingPole", false))
        {
            player->AddItem(6256, 1);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithBlacksmithHammer", false))
        {
            player->AddItem(5956, 1);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithFlintAndTinder", false))
        {
            player->AddItem(4471, 1);
        }

        if (sConfigMgr->GetOption<bool>("NecroHome.StartWithSimpleWood", false))
        {
            uint32 simpleWoodStartAmount =
                sConfigMgr->GetOption<uint32>("NecroHome.SimpleWoodStartAmmount", 0);

            if (simpleWoodStartAmount > 0)
            {
                player->AddItem(4470, simpleWoodStartAmount);
            }
        }
    }

    void GivePlayerInitialBankBags(Player *player)
    {
        if (!sConfigMgr->GetOption<bool>("NecroHome.StartWithAllBankBags", false))
        {
            return;
        }

        uint32 bagEntry = sConfigMgr->GetOption<uint32>("NecroHome.BankBagItemId", 0);

        if (bagEntry <= 0)
        {
            return;
        }

        player->SetBankBagSlotCount(BANK_SLOT_BAG_END - BANK_SLOT_BAG_START);

        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

        for (uint8 slot = BANK_SLOT_BAG_START; slot < BANK_SLOT_BAG_END; ++slot)
        {
            Item *bag = Item::CreateItem(bagEntry, 1, player);

            if (!bag)
            {
                continue;
            }

            bag->SaveToDB(trans);
            player->EquipItem(slot, bag, true);
        }

        CharacterDatabase.CommitTransaction(trans);
    }

    void GivePlayersInitialMounts(Player *player)
    {
        if (!sConfigMgr->GetOption<bool>("NecroHome.StartWithMount", false))
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
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdHuman", 0);
            break;

        case RACE_ORC:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdOrc", 0);
            break;

        case RACE_DWARF:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdDwarf", 0);
            break;

        case RACE_NIGHTELF:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdNightelf", 0);
            break;

        case RACE_UNDEAD_PLAYER:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdUndead", 0);
            break;

        case RACE_TAUREN:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdTauren", 0);
            break;

        case RACE_GNOME:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdGnome", 0);
            break;

        case RACE_TROLL:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdTroll", 0);
            break;

        case RACE_BLOODELF:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdBloodelf", 0);
            break;

        case RACE_DRAENEI:
            mountSpellId = sConfigMgr->GetOption<uint32>("NecroHome.StartMountIdDraenei", 0);
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

    void GivePlayerInitialGold(Player *player)
    {
        uint32 initialGold = sConfigMgr->GetOption<uint32>("NecroHome.StartGoldAmmount", 0);
        constexpr uint32 copperPerGold = 10000;

        player->ModifyMoney(initialGold * copperPerGold);
    }
}

NecroHome::NecroHome()
    : PlayerScript("NecroHome")
{
}

void NecroHome::OnPlayerFirstLogin(Player *player)
{

    if (player->GetSession() && (IsBotSession(player->GetSession()) || IsHeadlessClientSession(player->GetSession())))
    {
        return;
    }

    GivePlayerInitialProfessions(player);
    GivePlayerInitialBags(player);
    GivePlayerInitialTools(player);
    GivePlayerInitialBankBags(player);
    GivePlayersInitialMounts(player);
    GivePlayerInitialGold(player);
}

void NecroHome::OnPlayerLogin(Player *player)
{
    if (!sConfigMgr->GetOption<bool>("NecroHome.ShowWelcomeMessage", false))
    {
        return;
    }

    ChatHandler(player->GetSession()).PSendSysMessage("This server uses NecroHome module");
}

void Addmod_necro_homeScripts()
{
    new NecroHome();
}