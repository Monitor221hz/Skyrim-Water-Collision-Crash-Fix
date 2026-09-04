#pragma once
#include <safetyhook.hpp>
#include "RE/B/BGSWaterCollisionManager.h"

namespace WCCF
{
    // Up	p	TESObjectREFR__sub_1402917F0+802	call    sub_14029D510
    // AE 	p	sub_1402E57B0+898	call    sub_1402F1640
    using bhkPlaceableWater = RE::BGSWaterCollisionManager::bhkPlaceableWater;
    class WaterRigidBodyHook
    {
    public:
        static void Install()
        {
            REL::Relocation<std::uintptr_t> target{REL::RelocationID(19309, 19736), REL::Relocate(0x802, 0x898)};
            auto &trampoline = SKSE::GetTrampoline();
            _SetWaterRigidBody = trampoline.write_call<5>(target.address(), SetWaterRigidBody);
        }

    private:
        static RE::bhkRigidBody *SetWaterRigidBody(char *a_mem, void *a_params);
        static inline REL::Relocation<decltype(SetWaterRigidBody)> _SetWaterRigidBody;
    };

    class DeleteWaterHook
    {
        // 14029ED90, 1402F2E40
    public:
        static void Install()
        {
            REL::Relocation<std::uintptr_t> target{REL::RelocationID(19520, 19946)};
            _Delete = safetyhook::create_inline(target.address(), &Delete);
        }

    private:
        static int64_t Delete(bhkPlaceableWater *self, char deleteFlags);
        static inline SafetyHookInline _Delete;
    };

    static void InstallHooks()
    {
        SKSE::AllocTrampoline(0x10);
        WaterRigidBodyHook::Install();
        DeleteWaterHook::Install();
    }
}