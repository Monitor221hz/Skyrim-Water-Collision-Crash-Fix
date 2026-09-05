#include "hook.h"
namespace WCCF
{
    int64_t DeleteWaterHook::Delete(bhkPlaceableWater *self, char deleteFlags)
    {
        auto *body = self->updateI.body;
        if (body)
        {
            body->DecRefCount();
            SKSE::log::info("Unpin");
        }
        return _Delete.call<int64_t>(self, deleteFlags);
    }
    RE::bhkRigidBody *WaterRigidBodyHook::SetWaterRigidBody(char *a_mem, void *a_params)
    {
        auto *body = _SetWaterRigidBody(a_mem, a_params);
        if (body)
        {
            auto refCount = body->GetRefCount();
            body->IncRefCount();
            SKSE::log::info("Pin {} -> {}", refCount, body->GetRefCount());
        }
        return body;
    }
    void WaterStoreHook::Store(RE::ExtraDataList *a_extraDataList, bhkPlaceableWater *a_water)
    {
        bhkPlaceableWater* old = nullptr; 
        if (auto wd = a_extraDataList->GetByType<RE::ExtraWaterData>())
        {
            old = wd->unk18 ? reinterpret_cast<bhkPlaceableWater*>(wd->unk18.get()) : nullptr;
        }
        const bool retire = old && old != a_water;
        if (retire)
        {
            old->AddReference();
        }
        _Store.call(a_extraDataList, a_water);

        if (retire)
        {
            auto& waterUpdate = old->updateI;
            Unlink(&waterUpdate);
            SetInert(&waterUpdate, true);
            if (auto* body = waterUpdate.body)
            {
                auto refCount = body->GetRefCount();
                body->DecRefCount();
                waterUpdate.body = nullptr;
                SKSE::log::info("Unpin RefCount: {} -> {}", refCount, body->GetRefCount());
            }
            old->RemoveReference();
        }

    }
}
