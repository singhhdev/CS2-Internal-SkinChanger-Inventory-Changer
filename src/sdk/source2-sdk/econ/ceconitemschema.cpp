#include "ceconitemschema.hpp"

#include "../../memory/memory.hpp"

bool CPaintKit::UsesLegacyModel() {
    return static_cast<bool>(reinterpret_cast<std::uintptr_t>(this) + 0xB2);
}
