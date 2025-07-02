#include "Hooks.h"

namespace Addresses
{
    struct ProcessHit
    {
        static bool Call(
            RE::Projectile* apProjectile,
            RE::TESObjectREFR* apReference,
            RE::NiPoint3* apLocation,
            RE::hkVector4* apVector,
            std::uint32_t auCollisionFilter,
            RE::MATERIAL_ID auMaterialID,
            bool* apHandled)
        {
            if (auCollisionFilter == 0xC) {
                *apHandled = true;

                return false;
            }

            return Callback(apProjectile, apReference, apLocation, apVector, auCollisionFilter, auMaterialID, apHandled);
        }
        static inline REL::Relocation<decltype(Call)> Callback;
    };

    void Hook()
    {
        REL::Relocation process_hit{ RELOCATION_ID(43013, 44204), REL::Relocate(0x251 ,0x21F) };
        stl::write_thunk_call<ProcessHit>(process_hit.address());

        INFO("Hooked Address(es)!");
    }
}
