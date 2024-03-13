#pragma once

#include "../../virtual.hpp"

class CEngineClient {
   public:
    auto IsInGame() { return CALL_VIRTUAL(bool, 32, this); }
    auto GetLocalPlayer() {
        int nIndex = -1;

        CALL_VIRTUAL(void, 44, this, std::ref(nIndex), 0);

        return nIndex + 1;
    }
};
