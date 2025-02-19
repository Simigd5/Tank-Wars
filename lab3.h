#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        glm::vec2 projectilePosition;
        glm::vec2 projectileVelocity;
        bool isProjectileActive;
        float gravity;
        float  cloudOffsetX;
        float launchMagnitude; 
        float g; 
        float rotationAngle; 
        float projectileRadius;
        float projectile2Radius;
        int tank2HitCount = 0;
        int tank1HitCount = 0;
        glm::vec2 projectile2Position;
        glm::vec2 projectile2Velocity;
        bool isProjectile2Active;
        bool isProjectile1Visible;
        bool isProjectile2Visible;
        bool tank2Hit;
        bool checkTankCollision;
        int numPoints;
        std::vector<glm::vec3> terrainVertices; 
        std::vector<unsigned int> terrainIndices;
        std::vector<float> heightMap;
        glm::vec3 tankPosition;
        glm::vec3 tank2BodyPosition;;
        glm::vec3 tank1Position;
        glm::vec3 circle1Position;
        glm::vec3 circle2Position;
        glm::vec3 circleCenter; 
        glm::vec3 rectanglePosition;
        glm::vec3 tank2Position;
        glm::vec3 bar1Position;
        glm::vec3 bar2Position;
        bool tank2Visible = true; 
        bool tank1Visible = true;
        bool bara = true;
     
        int tank1Health = 5;
        int tank2Health = 5; 
        float turretAngle2;
        float circleRadius;           
        float turretAngle1 = 0.0f; 
        float rotationRadius; 
        float barWidth = 100.0f;
        

    };
} 
