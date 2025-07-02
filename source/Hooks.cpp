#include "Hooks.h"

namespace Addresses
{
    struct ProcessHit
    {
        static bool Call(
            RE::Projectile* aProjectile,
            RE::TESObjectREFR* aReference,
            RE::NiPoint3* aLocation,
            RE::hkVector4* aUnknown,
            RE::COL_LAYER aCollisionLayer,
            RE::MATERIAL_ID aMaterialID,
            bool* aHandled)
        {
            if (aCollisionLayer == RE::COL_LAYER::kTrigger) {
                *aHandled = true;

                return false;
            }

            return Callback(aProjectile, aReference, aLocation, aUnknown, aCollisionLayer, aMaterialID, aHandled);
        }
        static inline REL::Relocation<decltype(Call)> Callback;
    };

    void Hook()
    {
        REL::Relocation process_hit{ RELOCATION_ID(43013, 44204), REL::Relocate(0x251, 0x21F) };
        stl::write_thunk_call<ProcessHit>(process_hit.address());

        INFO("Hooked Address(es)!");
    }
}
