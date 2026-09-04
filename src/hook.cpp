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
            body->IncRefCount();
            SKSE::log::info("Pin");
        }
        return body;
    }
}
