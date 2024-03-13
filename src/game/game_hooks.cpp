#include "../sdk/interfaces/interfaces.hpp"
#include "../api/hook/hook.hpp"

#include "skins/skin_changer.hpp"
#include "menu/menu.hpp"

static CHook<bool __fastcall(void*)> g_mouseInputEnabled;
static bool __fastcall hkMouseInputEnabled(void* rcx) {
    if (menu::IsOpen()) return false;
    return g_mouseInputEnabled(rcx);
}

static CHook<void __fastcall(void*, int)> g_frameStageNotify;
static void __fastcall hkFrameStageNotify(void* rcx, int frameStage) {
    skin_changer::OnFrameStageNotify(frameStage);
    return g_frameStageNotify(rcx, frameStage);
}

static CHook<bool __fastcall(void*, CGameEvent*, bool)> g_fireEventClientSide;
static bool __fastcall hkFireEventClientSide(void* rcx, CGameEvent* event,
                                             bool bServerOnly) {
    skin_changer::OnPreFireEvent(event);
    return g_fireEventClientSide(rcx, event, bServerOnly);
}

static CHook<bool __fastcall(void*, int, int, uint64_t)> g_equipItemInLoadout;
static bool __fastcall hkEquipItemInLoadout(void* rcx, int iTeam, int iSlot,
                                            uint64_t iItemID) {
    skin_changer::OnEquipItemInLoadout(iTeam, iSlot, iItemID);
    return g_equipItemInLoadout(rcx, iTeam, iSlot, iItemID);
}

static CHook<void* __fastcall(C_BaseModelEntity*, const char*)> g_setModel;
static void* __fastcall hkSetModel(C_BaseModelEntity* rcx, const char* model) {
    skin_changer::OnSetModel(rcx, model);
    return g_setModel(rcx, model);
}

void CS2_HookGameFunctions() {
    g_mouseInputEnabled.Hook(memory::fnMouseInputEnabled,
                             HOOK_FUNCTION(hkMouseInputEnabled));
    g_frameStageNotify.HookVirtual(interfaces::pClient, 33,
                                   HOOK_FUNCTION(hkFrameStageNotify));
    g_fireEventClientSide.Hook(memory::fnFireEventClientSide,
                               HOOK_FUNCTION(hkFireEventClientSide));
    g_equipItemInLoadout.HookVirtual(CCSInventoryManager::GetInstance(), 52,
                                     HOOK_FUNCTION(hkEquipItemInLoadout));
    g_setModel.Hook(memory::fnSetModel, HOOK_FUNCTION(hkSetModel));

    
}

void CS2_UnhookGameFunctions() { skin_changer::Shutdown(); }
