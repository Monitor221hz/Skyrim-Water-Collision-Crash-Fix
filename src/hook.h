#pragma once
#include <safetyhook.hpp>
#include "RE/B/BGSWaterCollisionManager.h"

namespace WCCF
{

    using bhkPlaceableWater = RE::BGSWaterCollisionManager::bhkPlaceableWater;
    using BGSWaterUpdateI = RE::BGSWaterCollisionManager::BGSWaterUpdateI;
    using bhkWaterfall = RE::BGSWaterCollisionManager::bhkWaterfall;

    static BGSWaterUpdateI *Unlink(BGSWaterUpdateI *a_this)
    { // 1404C0FA0
        using func_t = decltype(Unlink);
        REL::Relocation<func_t> func{REL::VariantID(31303, 32087, 0x4D10F0)}; // ok for 1.7.99
        return func(a_this);
    }
    static int32_t SetInert(BGSWaterUpdateI *a_this, bool a_inert)
    { // 1404C0F80
        using func_t = decltype(SetInert);
        REL::Relocation<func_t> func{REL::VariantID(31302, 32086, 0x4D10D0)}; // ok for 1.7.99
        return func(a_this, a_inert);
    }
    class WaterStoreHook
    {
        public:
        static void Install()
        {
            REL::Relocation<std::uintptr_t> target{REL::VariantID(11938, 12077, 0x138050)}; // ok for 1.7.99
            _Store = safetyhook::create_inline(target.address(), &Store);
        }
        private:
        static void Store(RE::ExtraDataList* a_extraDataList, bhkPlaceableWater* a_water);
        static inline SafetyHookInline _Store;


    };
    class WaterFallStoreHook
    {
        public:
        static void Install()
        {
            // sub_140127CB0
            // AE 14016E820
            REL::Relocation<std::uintptr_t> target {REL::VariantID(11940, 12079, 0x2A4C50)}; 
            _Store = safetyhook::create_inline(target.address(), &Store);

        }
        static void Store(RE::ExtraDataList* a_extraDataList, bhkWaterfall* a_waterfall);
        static inline SafetyHookInline _Store;
    };
    class WaterFallRigidBodyHook
    {
        public:
        static void Install()
        {
            //Up	p	TESObjectREFR__sub_140293540+45D	call    sub_14029D510
            // AE Up	p	sub_1402E6BA0+39F	call    sub_1402F1640
            //Up	p	sub_1402ED130+184	call    sub_1402F7B70
            REL::Relocation<std::uintptr_t> target{REL::VariantID(19313, 19738, 0x2A4C50), REL::Module::IsAtLeast(REL::Version("1.7.99")) ? 0x184 : REL::Relocate(0x45D, 0x39F, 0x45D) };
            auto& trampoline = SKSE::GetTrampoline();
            _SetWaterFallRigidBody = trampoline.write_call<5>(target.address(), SetWaterFallRigidBody);
        }
        static RE::bhkRigidBody *SetWaterFallRigidBody(char *a_mem, void *a_params);
        static inline REL::Relocation<decltype(SetWaterFallRigidBody)> _SetWaterFallRigidBody;
    };
    class WaterRigidBodyHook
    {    // Up	p	TESObjectREFR__sub_1402917F0+802	call    sub_14029D510
    // AE 	p	sub_1402E57B0+898	call    sub_1402F1640
    // 1.7 	p	sub_1402EBD20+8A9	call    sub_1402F7C40
    public:
        static void Install()
        {
            REL::Relocation<std::uintptr_t> target{REL::VariantID(19309, 19736, 0x2A2F00), REL::Module::IsAtLeast(REL::Version("1.7.99")) ? 0x8A9 : REL::Relocate(0x802, 0x898, 0x802) };
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
            REL::Relocation<std::uintptr_t> target{REL::VariantID(19520, 19946, 0x2B0500)}; // ok for 1.7.99
            _Delete = safetyhook::create_inline(target.address(), &Delete);
        }

    private:
        static int64_t Delete(bhkPlaceableWater *self, char deleteFlags);
        static inline SafetyHookInline _Delete;
    };



    static void InstallHooks()
    {
        SKSE::AllocTrampoline(0x20);
        WaterFallRigidBodyHook::Install();
        WaterFallStoreHook::Install();
        WaterRigidBodyHook::Install();
        DeleteWaterHook::Install();
        WaterStoreHook::Install();
    }
}