#pragma once

#include <glm/glm.hpp>

#include <dearVRCore/CoordinateSystem.h>

namespace rp::curtis
{
    inline glm::vec3 toVec3(const CoordinateSystem& coordinateSystem)
    {
        return glm::vec3(coordinateSystem.getX(), coordinateSystem.getY(), coordinateSystem.getZ());
    }

    inline CoordinateSystem toRightHandSystem(const CoordinateSystem& leftHandCoordinate)
    {
        return CoordinateSystem::cartesian(leftHandCoordinate.getX(), leftHandCoordinate.getY(), -leftHandCoordinate.getZ());
    }

}
