#pragma once

#include "c_csplayerpawnbase.hpp"

class C_CSPlayerPawn : public C_CSPlayerPawnBase {
   public:
    bool IsEnemyWithTeam(int team);
    SCHEMA_FIELD(m_EconGloves, "C_CSPlayerPawn", "m_EconGloves", C_EconItemView*);
    SCHEMA_FIELD(m_bNeedToReApplyGloves, "C_CSPlayerPawn", "m_bNeedToReApplyGloves", bool);
};
