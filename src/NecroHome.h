#pragma once

#include "Player.h"
#include "ScriptMgr.h"

class NecroHome : public PlayerScript
{
public: NecroHome();

    void OnPlayerCreate(Player* player) override;
};