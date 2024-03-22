#pragma once

#include "../../virtual.hpp"

class CCSPlayerInventory;

class CCSInventoryManager {
   public:
    static CCSInventoryManager* GetInstance();

    auto EquipItemInLoadout(int iTeam, int iSlot, uint64_t iItemID) {
        return CALL_VIRTUAL(bool, 54, this, iTeam, iSlot, iItemID);
    }

    auto GetLocalInventory() {
        return CALL_VIRTUAL(CCSPlayerInventory*, 57, this);
    }
};
