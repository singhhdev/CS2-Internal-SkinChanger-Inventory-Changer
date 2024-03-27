#include <vector>

#include "skin_changer.hpp"

#include "../../sdk/interfaces/interfaces.hpp"

static std::vector<uint64_t> g_vecAddedItemsIDs;
enum loadout_slot_t {
    LOADOUT_SLOT_C4 = 1,
    LOADOUT_SLOT_CLOTHING_APPEARANCE = 46,
    LOADOUT_SLOT_CLOTHING_CUSTOMPLAYER = 38,
    LOADOUT_SLOT_CLOTHING_EYEWEAR = 42,
    LOADOUT_SLOT_CLOTHING_FACEMASK = 40,
    LOADOUT_SLOT_CLOTHING_HANDS = 41,
    LOADOUT_SLOT_CLOTHING_HAT = 43,
    LOADOUT_SLOT_CLOTHING_LOWERBODY = 44,
    LOADOUT_SLOT_CLOTHING_TORSO = 45,
    LOADOUT_SLOT_COUNT = 57,
    LOADOUT_SLOT_EQUIPMENT0 = 32,
    LOADOUT_SLOT_EQUIPMENT1 = 33,
    LOADOUT_SLOT_EQUIPMENT2 = 34,
    LOADOUT_SLOT_EQUIPMENT3 = 35,
    LOADOUT_SLOT_EQUIPMENT4 = 36,
    LOADOUT_SLOT_EQUIPMENT5 = 37,
    LOADOUT_SLOT_FIRST_ALL_CHARACTER = 54,
    LOADOUT_SLOT_FIRST_AUTO_BUY_WEAPON = 0,
    LOADOUT_SLOT_FIRST_COSMETIC = 41,
    LOADOUT_SLOT_FIRST_PRIMARY_WEAPON = 8,
    LOADOUT_SLOT_FIRST_WHEEL_EQUIPMENT = 32,
    LOADOUT_SLOT_FIRST_WHEEL_GRENADE = 26,
    LOADOUT_SLOT_FIRST_WHEEL_WEAPON = 2,
    LOADOUT_SLOT_FLAIR0 = 55,
    LOADOUT_SLOT_GRENADE0 = 26,
    LOADOUT_SLOT_GRENADE1 = 27,
    LOADOUT_SLOT_GRENADE2 = 28,
    LOADOUT_SLOT_GRENADE3 = 29,
    LOADOUT_SLOT_GRENADE4 = 30,
    LOADOUT_SLOT_GRENADE5 = 31,
    LOADOUT_SLOT_HEAVY0 = 20,
    LOADOUT_SLOT_HEAVY1 = 21,
    LOADOUT_SLOT_HEAVY2 = 22,
    LOADOUT_SLOT_HEAVY3 = 23,
    LOADOUT_SLOT_HEAVY4 = 24,
    LOADOUT_SLOT_HEAVY5 = 25,
    LOADOUT_SLOT_INVALID = 4294967295,
    LOADOUT_SLOT_LAST_ALL_CHARACTER = 56,
    LOADOUT_SLOT_LAST_AUTO_BUY_WEAPON = 1,
    LOADOUT_SLOT_LAST_COSMETIC = 41,
    LOADOUT_SLOT_LAST_PRIMARY_WEAPON = 25,
    LOADOUT_SLOT_LAST_WHEEL_EQUIPMENT = 37,
    LOADOUT_SLOT_LAST_WHEEL_GRENADE = 31,
    LOADOUT_SLOT_LAST_WHEEL_WEAPON = 25,
    LOADOUT_SLOT_MELEE = 0,
    LOADOUT_SLOT_MISC0 = 47,
    LOADOUT_SLOT_MISC1 = 48,
    LOADOUT_SLOT_MISC2 = 49,
    LOADOUT_SLOT_MISC3 = 50,
    LOADOUT_SLOT_MISC4 = 51,
    LOADOUT_SLOT_MISC5 = 52,
    LOADOUT_SLOT_MISC6 = 53,
    LOADOUT_SLOT_MUSICKIT = 54,
    LOADOUT_SLOT_PET = 39,
    LOADOUT_SLOT_PROMOTED = 4294967295,
    LOADOUT_SLOT_RIFLE0 = 14,
    LOADOUT_SLOT_RIFLE1 = 15,
    LOADOUT_SLOT_RIFLE2 = 16,
    LOADOUT_SLOT_RIFLE3 = 17,
    LOADOUT_SLOT_RIFLE4 = 18,
    LOADOUT_SLOT_RIFLE5 = 19,
    LOADOUT_SLOT_SECONDARY0 = 2,
    LOADOUT_SLOT_SECONDARY1 = 3,
    LOADOUT_SLOT_SECONDARY2 = 4,
    LOADOUT_SLOT_SECONDARY3 = 5,
    LOADOUT_SLOT_SECONDARY4 = 6,
    LOADOUT_SLOT_SECONDARY5 = 7,
    LOADOUT_SLOT_SMG0 = 8,
    LOADOUT_SLOT_SMG1 = 9,
    LOADOUT_SLOT_SMG2 = 10,
    LOADOUT_SLOT_SMG3 = 11,
    LOADOUT_SLOT_SMG4 = 12,
    LOADOUT_SLOT_SMG5 = 13,
    LOADOUT_SLOT_SPRAY0 = 56
};





void skin_changer::OnFrameStageNotify(int frameStage)
{
    if (frameStage != 6 || !interfaces::pEngine->IsInGame()) return;

    CCSPlayerInventory* pInventory = CCSPlayerInventory::GetInstance();
    if (!pInventory) return;

    CGameEntitySystem* pEntitySystem = CGameEntitySystem::GetInstance();
    if (!pEntitySystem) return;

    const uint64_t steamID = pInventory->GetOwner().m_id;

    CCSPlayerController* pLocalPlayerController =
        CGameEntitySystem::GetLocalPlayerController();
    if (!pLocalPlayerController) return;

    C_CSPlayerPawn* pLocalPawn =
        pLocalPlayerController->m_hPawn().Get<C_CSPlayerPawn>();
    if (!pLocalPawn) return;

    CCSPlayer_ViewModelServices* pViewModelServices = pLocalPawn->m_pViewModelServices();
    if (!pViewModelServices)
        return;
    C_CSGOViewModel* pViewModel = pViewModelServices->m_hViewModel()[0].Get<C_CSGOViewModel>();
    if (!pViewModel)
        return;

   /* C_EconItemView* pItemViewLoadout = pInventory->GetItemInLoadout(pLocalPlayerController->m_iTeamNum(), LOADOUT_SLOT_C4);
    if (!pItemViewLoadout)
        return;*/


    int highestIndex = pEntitySystem->GetHighestEntityIndex();
    for (int i = MAX_PLAYERS + 1; i <= highestIndex; ++i) {
        C_BaseEntity* pEntity = pEntitySystem->GetBaseEntity(i);
        if (!pEntity || !pEntity->IsBasePlayerWeapon()) continue;

        C_CSWeaponBase* pWeapon = reinterpret_cast<C_CSWeaponBase*>(pEntity);
        if (pWeapon->GetOriginalOwnerXuid() != steamID) continue;

        C_AttributeContainer* pAttributeContainer =
            pWeapon->m_AttributeManager();
        if (!pAttributeContainer) continue;

        C_EconItemView* pWeaponItemView = pAttributeContainer->m_Item();
        if (!pWeaponItemView) continue;
        CEconItemDefinition* pWeaponDefinition =
            pWeaponItemView->GetStaticData();
        if (!pWeaponDefinition) continue;

        CGameSceneNode* pWeaponSceneNode = pWeapon->m_pGameSceneNode();
        if (!pWeaponSceneNode) continue;
        int id = pAttributeContainer->m_Item()->m_iItemDefinitionIndex();
        if (id == 43 || id == 44 || id == 45 || id == 46 ||id == 47 || id == 48 || id == 49 ) continue;
        // No idea how to check this faster with the new loadout system.
        C_EconItemView* pWeaponInLoadoutItemView = nullptr;
        if (pWeaponDefinition->IsWeapon()) {
            for (int i = 0; i <= 56; ++i) {
                C_EconItemView* pItemView = pInventory->GetItemInLoadout(
                    pWeapon->m_iOriginalTeamNumber(), i);
                if (!pItemView) continue;

                if (pItemView->m_iItemDefinitionIndex() ==
                    pWeaponDefinition->m_nDefIndex) {
                    pWeaponInLoadoutItemView = pItemView;
                    break;
                }
            }
        }
        else {
            pWeaponInLoadoutItemView = pInventory->GetItemInLoadout(
                pWeapon->m_iOriginalTeamNumber(),
                pWeaponDefinition->GetLoadoutSlot());
        }
        if (!pWeaponInLoadoutItemView) continue;

        // Check if skin is added by us.
        auto it =
            std::find(g_vecAddedItemsIDs.cbegin(), g_vecAddedItemsIDs.cend(),
                pWeaponInLoadoutItemView->m_iItemID());
        if (it == g_vecAddedItemsIDs.cend()) continue;

        CEconItemDefinition* pWeaponInLoadoutDefinition =
            pWeaponInLoadoutItemView->GetStaticData();
        if (!pWeaponInLoadoutDefinition) continue;

        // Example: Will not equip FiveSeven skin on CZ. Not applies for knives.
        const bool isKnife = pWeaponInLoadoutDefinition->IsKnife(false);
        const bool isGlove = pWeaponInLoadoutDefinition->IsGlove(false);
        if (!isKnife && pWeaponInLoadoutDefinition->m_nDefIndex !=
            pWeaponDefinition->m_nDefIndex)
            continue;

        pWeaponItemView->m_bDisallowSOC() = false; // <--- the fix

        pWeaponItemView->m_iItemID() = pWeaponInLoadoutItemView->m_iItemID();
        pWeaponItemView->m_iItemIDHigh() =
            pWeaponInLoadoutItemView->m_iItemIDHigh();
        pWeaponItemView->m_iItemIDLow() =
            pWeaponInLoadoutItemView->m_iItemIDLow();
        pWeaponItemView->m_iAccountID() = uint32_t(steamID);

        // Displays nametag and stattrak on the gun.
        // Found by: https://www.unknowncheats.me/forum/members/2377851.html
        if (!pWeapon->m_bUIWeapon()) {
            pWeapon->AddStattrakEntity();
            pWeapon->AddNametagEntity();
        }
        CHandle hWeapon = pWeapon->GetRefEHandle();

        if (isKnife) {


            pWeaponItemView->m_iItemDefinitionIndex() =
                pWeaponInLoadoutDefinition->m_nDefIndex;

            const char* knifeModel = pWeaponInLoadoutDefinition->GetModelName();



            pWeapon->SetModel(knifeModel);
            if (pViewModel && pViewModel->m_hWeapon() == hWeapon)
                pViewModel->SetModel(knifeModel);
            pViewModel->pAnimationGraphInstance->pAnimGraphNetworkedVariables = nullptr;

        }
        else {
            // Use legacy weapon models only for skins that require them.
            // Probably need to cache this if you really care that much about
            // performance.
            auto paintKit =
                interfaces::pClient->GetEconItemSystem()
                ->GetEconItemSchema()
                ->GetPaintKits()
                .FindByKey(
                    pWeaponInLoadoutItemView->GetCustomPaintKitIndex());

            const bool usesOldModel =
                paintKit.has_value() && paintKit.value()->UsesLegacyModel();

            pWeaponSceneNode->SetMeshGroupMask(1 + usesOldModel);
            if (pViewModel && pViewModel->m_hWeapon() == hWeapon) {
                CGameSceneNode* pViewModelSceneNode =
                    pViewModel->m_pGameSceneNode();

                if (pViewModelSceneNode)
                    pViewModelSceneNode->SetMeshGroupMask(1 + usesOldModel);
            }
        }

    }

}




void skin_changer::OnPreFireEvent(CGameEvent* pEvent) {
    if (!pEvent) return;

    const char* eventName = pEvent->GetName();
    if (!eventName) return;

    static constexpr auto player_death = hash_32_fnv1a_const("player_death");
    if (hash_32_fnv1a_const(eventName) != player_death) return;

    CCSPlayerController* pControllerWhoKilled =
        pEvent->GetPlayerController("attacker");
    CCSPlayerController* pControllerWhoDied =
        pEvent->GetPlayerController("userid");
    if (pControllerWhoKilled == pControllerWhoDied) return;

    CCSPlayerController* pLocalPlayerController =
        CGameEntitySystem::GetLocalPlayerController();
    if (!pLocalPlayerController ||
        pControllerWhoKilled != pLocalPlayerController)
        return;

    C_CSPlayerPawn* pLocalPawn =
        pLocalPlayerController->m_hPawn().Get<C_CSPlayerPawn>();
    if (!pLocalPawn) return;

    CPlayer_WeaponServices* pWeaponServices = pLocalPawn->m_pWeaponServices();
    if (!pWeaponServices) return;

    C_CSWeaponBase* pActiveWeapon =
        pWeaponServices->m_hActiveWeapon().Get<C_CSWeaponBase>();
    if (!pActiveWeapon) return;

    C_AttributeContainer* pAttributeContainer =
        pActiveWeapon->m_AttributeManager();
    if (!pAttributeContainer) return;

    C_EconItemView* pWeaponItemView = pAttributeContainer->m_Item();
    if (!pWeaponItemView) return;

    CEconItemDefinition* pWeaponDefinition = pWeaponItemView->GetStaticData();
    if (!pWeaponDefinition || !pWeaponDefinition->IsKnife(true)) return;

    pEvent->SetString("weapon", pWeaponDefinition->GetSimpleWeaponName());
}

void skin_changer::OnEquipItemInLoadout(int team, int slot, uint64_t itemID) {
    auto it =
        std::find(g_vecAddedItemsIDs.begin(), g_vecAddedItemsIDs.end(), itemID);
    if (it == g_vecAddedItemsIDs.end()) return;

    CCSInventoryManager* pInventoryManager = CCSInventoryManager::GetInstance();
    if (!pInventoryManager) return;

    CCSPlayerInventory* pInventory = CCSPlayerInventory::GetInstance();
    if (!pInventory) return;

    C_EconItemView* pItemViewToEquip = pInventory->GetItemViewForItem(*it);
    if (!pItemViewToEquip) return;

    C_EconItemView* pItemInLoadout = pInventory->GetItemInLoadout(team, slot);
    if (!pItemInLoadout) return;

    CEconItemDefinition* pItemInLoadoutStaticData =
        pItemInLoadout->GetStaticData();
    if (!pItemInLoadoutStaticData) return;

    if (pItemInLoadoutStaticData->IsGlove(false) ||
        pItemInLoadoutStaticData->IsKnife(false) ||
        pItemInLoadoutStaticData->m_nDefIndex ==
        pItemViewToEquip->m_iItemDefinitionIndex())
        return;

    // Equip default item. If you would have bought Deagle and you previously
    // had R8 equipped it will now give you a Deagle.
    const uint64_t defaultItemID =
        (std::uint64_t(0xF) << 60) | pItemViewToEquip->m_iItemDefinitionIndex();
    pInventoryManager->EquipItemInLoadout(team, slot, defaultItemID);

    CEconItem* pItemInLoadoutSOCData = pItemInLoadout->GetSOCData();
    if (!pItemInLoadoutSOCData) return;

    // Mark old item as unequipped.
    pInventory->SOUpdated(pInventory->GetOwner(),
        (CSharedObject*)pItemInLoadoutSOCData,
        eSOCacheEvent_Incremental);
}

void skin_changer::OnSetModel(C_BaseModelEntity* pEntity, const char*& model) {
    // When you're lagging you may see the default knife for one second and this
    // function fixes that.
    if (!pEntity || !pEntity->IsViewModel()) return;

    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pEntity;

    CCSPlayerInventory* pInventory = CCSPlayerInventory::GetInstance();
    if (!pInventory) return;

    const uint64_t steamID = pInventory->GetOwner().m_id;

    C_CSWeaponBase* pWeapon = pViewModel->m_hWeapon().Get<C_CSWeaponBase>();
    if (!pWeapon || !pWeapon->IsBasePlayerWeapon() ||
        pWeapon->GetOriginalOwnerXuid() != steamID)
        return;

    C_AttributeContainer* pAttributeContainer = pWeapon->m_AttributeManager();
    if (!pAttributeContainer) return;

    C_EconItemView* pWeaponItemView = pAttributeContainer->m_Item();
    if (!pWeaponItemView) return;

    CEconItemDefinition* pWeaponDefinition = pWeaponItemView->GetStaticData();
    if (!pWeaponDefinition) return;

    C_EconItemView* pWeaponInLoadoutItemView = pInventory->GetItemInLoadout(
        pWeapon->m_iOriginalTeamNumber(), pWeaponDefinition->GetLoadoutSlot());
    if (!pWeaponInLoadoutItemView) return;

    // Check if skin is added by us.
    auto it = std::find(g_vecAddedItemsIDs.cbegin(), g_vecAddedItemsIDs.cend(),
        pWeaponInLoadoutItemView->m_iItemID());
    if (it == g_vecAddedItemsIDs.cend()) return;

    CEconItemDefinition* pWeaponInLoadoutDefinition =
        pWeaponInLoadoutItemView->GetStaticData();
    if (!pWeaponInLoadoutDefinition ||
        !pWeaponInLoadoutDefinition->IsKnife(true))
        return;

    model = pWeaponInLoadoutDefinition->GetModelName();
}

void skin_changer::AddEconItemToList(CEconItem* pItem) {
    g_vecAddedItemsIDs.emplace_back(pItem->m_ulID);
}

void skin_changer::Shutdown() {
    CCSPlayerInventory* pInventory = CCSPlayerInventory::GetInstance();
    if (!pInventory) return;

    for (uint64_t id : g_vecAddedItemsIDs) {
        pInventory->RemoveEconItem(pInventory->GetSOCDataForItem(id));
    }
}
