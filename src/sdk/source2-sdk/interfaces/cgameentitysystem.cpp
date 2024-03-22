#include "cgameentitysystem.hpp"

#include "../../interfaces/interfaces.hpp"

CGameEntitySystem* CGameEntitySystem::GetInstance() {
    if (!interfaces::pGameResourceService) return nullptr;
    return interfaces::pGameResourceService->GetGameEntitySystem();
}

CCSPlayerController* CGameEntitySystem::GetLocalPlayerController() {
    const int nIndex = interfaces::pEngine->GetLocalPlayer();
    return interfaces::pGameResourceService->GetGameEntitySystem()
        ->GetBaseEntity<CCSPlayerController>(nIndex);
}
