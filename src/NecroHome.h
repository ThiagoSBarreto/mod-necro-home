#pragma once

#include "Player.h"
#include "ScriptMgr.h"
#include "Chat.h"

class Player;

class NecroHome : public PlayerScript
{
public: 
    NecroHome();
    void OnPlayerFirstLogin(Player* player) override;
    void OnPlayerLogin(Player* player) override;
};

void Addmod_necro_homeScripts();