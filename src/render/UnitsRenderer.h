#ifndef UNITSRENDERER_H
#define UNITSRENDERER_H

#include "core/Types.h"

#include <memory>
#include <vector>

class IRenderTarget;
struct Entity;
struct MoveTargetMarker;
struct Player;
struct VisibilityMap;
class UnitManager;

class UnitsRenderer
{
public:
    void render(const std::shared_ptr<IRenderTarget> &renderTarget, const std::vector<std::weak_ptr<Entity>> &visible);

    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);
    void setVisibilityMap(const std::weak_ptr<VisibilityMap> &visibilityMap) { m_visibilityMap = visibilityMap; }

private:
    std::weak_ptr<VisibilityMap> m_visibilityMap;
    std::shared_ptr<IRenderTarget> m_outlineOverlay;
    std::weak_ptr<Player> m_player;
    std::weak_ptr<UnitManager> m_unitManager;
    MapPos m_previousCameraPos;
};

#endif // UNITSRENDERER_H