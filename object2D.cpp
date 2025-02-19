#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateTerrain(const std::string& name, int numPoints, float frequency, float amplitude, float spacing, float baseY, const glm::vec3& color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < numPoints; i++) {
        float x = i * spacing;
        float y = baseY + amplitude * sin(frequency * i) + amplitude * 0.5f * sin(frequency * 2 * i);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color)); 
        vertices.push_back(VertexFormat(glm::vec3(x, 0, 0), color)); 
    }

    for (int i = 0; i < numPoints * 2; i++) {
        indices.push_back(i);
    }

    Mesh* terrain = new Mesh(name);
    terrain->InitFromData(vertices, indices);
    terrain->SetDrawMode(GL_TRIANGLE_STRIP);
    return terrain;
}

Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int triangleCount = 100;

    for (int i = 0; i <= triangleCount; i++) {
        float angle = 2.0f * glm::pi<float>() * i / triangleCount;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
        indices.push_back(i);
    }

    indices.push_back(0); 
    Mesh* circle = new Mesh(name);

    if (fill) {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    
    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

   
    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);  
    }
    else {
        
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateLine(const std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color)
{
    std::vector<VertexFormat> vertices = {
        VertexFormat(start, color),
        VertexFormat(end, color)
    };
    std::vector<unsigned int> indices = { 0, 1 };

    Mesh* line = new Mesh(name);
    line->SetDrawMode(GL_LINES);
    line->InitFromData(vertices, indices);

    return line;
}

Mesh* object2D::CreateTank(const std::string& name, glm::vec3 position, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Cod pentru a crea structura tancului
    float baseWidth = 80.0f;
    float topWidth = 120.0f;
    float height = 30.0f;

    vertices.push_back(VertexFormat(position + glm::vec3(-baseWidth / 2, 0, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(baseWidth / 2, 0, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(-topWidth / 2, height, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(topWidth / 2, height, 0), color));


    indices.insert(indices.end(), { 0, 1, 2, 1, 2, 3 });

    Mesh* tank = new Mesh(name);
    tank->InitFromData(vertices, indices);
    return tank;
}

Mesh* object2D::CreateTank1(const std::string& name, glm::vec3 position, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Cod pentru a crea structura tancului
    float baseWidth1 = 150.0f;
    float topWidth1 = 100.0f;
    float height1 = 35.0f;

    vertices.push_back(VertexFormat(position + glm::vec3(-baseWidth1 / 2, 0, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(baseWidth1 / 2, 0, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(-topWidth1 / 2, height1, 0), color));
    vertices.push_back(VertexFormat(position + glm::vec3(topWidth1 / 2, height1, 0), color));


    indices.insert(indices.end(), { 0, 1, 2, 1, 2, 3 });

    Mesh* tank1 = new Mesh(name);
    tank1->InitFromData(vertices, indices);
    return tank1;
}


Mesh* object2D::CreateCircle1(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int triangleCount = 100;

    for (int i = 0; i <= triangleCount; i++) {
        float angle = 2.0f * glm::pi<float>() * i / triangleCount;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
        indices.push_back(i);
    }

    indices.push_back(0);
    Mesh* circle1 = new Mesh(name);

    if (fill) {
        circle1->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        circle1->SetDrawMode(GL_LINE_LOOP);
    }

    circle1->InitFromData(vertices, indices);
    return circle1;
}

