#include "EntityHelper.hpp"
#include "Core/DataComponents/MovementData.hpp"
#include "Core/World/IWorldContext.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/Systems/NavGridSystem.hpp"

EntityHelper::EntityHelper()
{

}

bool EntityHelper::updateEntityPosition(IWorldContext &ctx, EntityID id, const Position &pos)
{
    auto entityHandle = ctx.getEntityManager().getEntityByID(id);
    if (auto entity = entityHandle.lock())
    {
        CellFlag cellOccupyType = CellFlag::OCCUPY;
        if(const auto& movementData = entity->getComponentByType<MovementData>())
        {
            cellOccupyType = movementData->cellOccupyType;
        }

        auto currentPos = entity->getPosition();
        bool result = ctx.getEntityManager().updateEntityPosition(id, pos);
        result = result && ctx.getGrid().updatePosition(id, currentPos, pos, cellOccupyType);
        return result;
    }

    return false;
}

bool EntityHelper::updateEntityPosition(IWorldContext &ctx, EntityHandle handle, const Position &pos)
{
    return updateEntityPosition(ctx, handle.getId(), pos);
}

EntityHandle EntityHelper::createEntity(IWorldContext &ctx, const std::string &name, EntityID id, Position pos, const UnitParams &params)
{
    auto entity = ctx.getEntityManager().createEntity(name, id, pos, params, ctx.getSharedContext());
    updateEntityPosition(ctx, entity.getId(), pos);
    return entity;
}

