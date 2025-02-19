#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D
{
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle1(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateTank(const std::string& name, glm::vec3 position, glm::vec3 color);
    Mesh* CreateTank1(const std::string& name, glm::vec3 position, glm::vec3 color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateLine(const std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
    Mesh* CreateTerrain(const std::string& name, int numPoints, float frequency, float amplitude, float spacing, float baseY, const glm::vec3& color);
}