#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;



Lab3::Lab3(): cloudOffsetX(0)
{
}

Lab3::~Lab3()
{
}

void Lab3::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    Mesh* line = object2D::CreateLine("line", glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0.4f, 0.7f, 0.3f));
    AddMeshToList(line);
    int numPoints = 50;
    float frequency = 0.22f;
    float amplitude = 50.0f;
    float spacing = 27.0f;
    float baseY = 200.0f;
    float barHeight = 10.0f; 
    float healthPercent1=tank1Health/5.0f;
    float healthPercent2 = tank2Health / 5.0f;
    float currentBarWidth1 = barWidth * healthPercent1;
    float currentBarWidth2 = barWidth * healthPercent2;
   
    tankPosition = glm::vec3(0, 0, 0);
    turretAngle1 = 0.0f;
    projectileRadius = 10.0f;
    projectile2Radius = 10.0f;
    gravity = 200.0f;
    bool tank2Visible = true;
    bool tank1Visible = true;
    bool isProjectile1Visible=true;
    bool isProjectile2Visible = true;
    isProjectileActive = false;
    Mesh* projectile = object2D::CreateCircle("circle", glm::vec3(0, 72.5, 0), projectileRadius, glm::vec3(0, 0, 0), true);
    AddMeshToList(projectile);
    isProjectile2Active = false;
    Mesh* projectile2 = object2D::CreateCircle("circle", glm::vec3(0, 72.5, 0), projectile2Radius, glm::vec3(0, 0, 0), true);
    AddMeshToList(projectile2);
    gravity = 200.0f;
    tank2Position = glm::vec3(0, 0, 0); 
    turretAngle2 = 0.0f;
    glm::vec3 projectilePosition = glm::vec3(0.0f, 0.0f, 0.0f);  
    glm::vec2 projectileVelocity = glm::vec2(0.0f, 0.0f);  
    glm::vec3 projectile2Position = glm::vec3(0.0f, 0.0f, 0.0f);  
    glm::vec2 projectile2Velocity = glm::vec2(0.0f, 0.0f);  
    // Inițializăm punctele terenului
    for (int i = 0; i < numPoints; i++) {
        float x = i * spacing;
        float y = baseY + amplitude * sin(frequency * i) + amplitude * 0.5f * sin(frequency * 2 * i);
        terrainVertices.push_back(glm::vec3(x, y, 0)); 
    }

    // Creare tanc și alte mesh-uri
    glm::vec3 tankColor = glm::vec3(0.5f, 0.1f, 0.6f);
    glm::vec3 tank1Color = glm::vec3(0.7f, 0.3f, 0.8f);
    glm::vec3 tank1Position = tankPosition + glm::vec3(0, 30, 0);
    glm::vec3 circle1Position = tank1Position + glm::vec3(0, 35, 0);
    glm::vec3 rectangleColor = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 terrainColor = glm::vec3(0.73f, 0.16f, 0.96f);
    glm::vec3 tank2BodyPosition = tank2Position + glm::vec3(0, 30, 0);
    glm::vec3 circle2Position = tank2BodyPosition + glm::vec3(0, 35, 0);
    glm::vec3 bar1Position = tank1Position + glm::vec3(0.0f, -190.0f, 0.0f);
    glm::vec3 bar2Position = tank2Position + glm::vec3(0.0f, -190.0f, 0.0f);
    Mesh* tank = object2D::CreateTank("tank", tankPosition, tankColor);
    AddMeshToList(tank);

    Mesh* tank1 = object2D::CreateTank1("tank1", tank1Position, tank1Color);
    AddMeshToList(tank1);

    Mesh* circle1 = object2D::CreateCircle1("circle1", circle1Position, 23.0f, tank1Color, true);
    AddMeshToList(circle1);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", circle1Position, 7.0f, 60.0f, rectangleColor, true);
    AddMeshToList(rectangle);

    Mesh* tank2 = object2D::CreateTank("tank2", tank2Position, glm::vec3(0.9f, 0.0f, 0.8f));
    AddMeshToList(tank2);

    Mesh* tank2Body = object2D::CreateTank1("tank2Body", tank2BodyPosition, glm::vec3(1.0f, 0.4f, 1.0f));
    AddMeshToList(tank2Body);

    Mesh* tank2Turret = object2D::CreateRectangle("tank2Turret", circle2Position, 7.0f, 60.0f, rectangleColor, true);
    AddMeshToList(tank2Turret);

    Mesh* circle2 = object2D::CreateCircle1("circle2", circle2Position, 23.0f, glm::vec3(1.0f, 0.4f, 1.0f), true);
    AddMeshToList(circle2);

    glClearColor(0.85f, 0.70f, 0.99f, 1);

    // Clouds
    Mesh* cloud = object2D::CreateCircle("cloud", glm::vec3(0, 0, 0), 30.0f, glm::vec3(0.9, 0.9, 1.0), true);
    AddMeshToList(cloud);

    Mesh* terrain = object2D::CreateTerrain("terrain", numPoints, frequency, amplitude, spacing, baseY, terrainColor);
    AddMeshToList(terrain);

    Mesh* bar1 =object2D::CreateRectangle("bar1", bar1Position, barWidth, barHeight, glm::vec3(1.0f, 1.0f, 1.0f), true);
    AddMeshToList(bar1);

    Mesh* bar12 = object2D::CreateRectangle("bar12", bar1Position+ glm::vec3(0, 0, 1), currentBarWidth1, barHeight, glm::vec3(0.6f, 3.0f, 0.8f), true);
    AddMeshToList(bar12);

    Mesh* bar2 = object2D::CreateRectangle("bar2", bar2Position, barWidth, barHeight, glm::vec3(1.0f, 1.0f, 1.0f), true);
    AddMeshToList(bar2);

    Mesh* bar22 = object2D::CreateRectangle("bar22", bar2Position + glm::vec3(0, 0, 1), currentBarWidth1, barHeight, glm::vec3(0.6f, 3.0f, 0.8f), true);
    AddMeshToList(bar22);
}


void Lab3::FrameStart()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab3::Update(float deltaTimeSeconds)
{
    glm::vec2 cloudCenter = glm::vec2(0, 600);

    cloudOffsetX += deltaTimeSeconds * 50; // v nori
    if (cloudOffsetX > 650) cloudOffsetX = 0; // Resetare la capatul ecranului
    //cloud1
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 40, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX, cloudCenter.y + 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 40, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX, cloudCenter.y - 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //2
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 540, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 500, cloudCenter.y + 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 500, cloudCenter.y - 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 460, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //3
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 210, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 250, cloudCenter.y - 90);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 290, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 250, cloudCenter.y - 110);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //4

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 210, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 250, cloudCenter.y - 90);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 290, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 250, cloudCenter.y - 110);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //5
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 700, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 740, cloudCenter.y - 90);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 780, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 740, cloudCenter.y - 110);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);


    //6
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 530, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 490, cloudCenter.y + 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 450, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX - 490, cloudCenter.y - 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //7
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 900, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 940, cloudCenter.y + 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 980, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 940, cloudCenter.y - 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //8
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1100, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1140, cloudCenter.y - 90);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1180, cloudCenter.y - 100);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1140, cloudCenter.y - 110);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    //9
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1300, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1340, cloudCenter.y + 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1380, cloudCenter.y);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudOffsetX + 1340, cloudCenter.y - 10);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["terrain"], shaders["VertexColor"], modelMatrix);

   


    glm::vec2 A, B;
    bool pointsFound = false;
    for (size_t i = 0; i < terrainVertices.size() - 1; ++i) {
        if (terrainVertices[i].x <= tankPosition.x && tankPosition.x <= terrainVertices[i + 1].x) {
            A = glm::vec2(terrainVertices[i].x, terrainVertices[i].y);
            B = glm::vec2(terrainVertices[i + 1].x, terrainVertices[i + 1].y);
            pointsFound = true;
            break;
        }
    }

    // Dacă nu gasim punctele A si B, nu actualizam pozitia tancului
    if (!pointsFound) return;

    // Calculăm interpolarea pentru poziția Y a tancului
    float t = (tankPosition.x - A.x) / (B.x - A.x);
    tankPosition.y = A.y + t * (B.y - A.y);

    // Calculăm unghiul de rotatie
    glm::vec2 direction = glm::normalize(B - A);
    float rotationAngle = atan2(direction.y, direction.x);
    if (tank1Visible) {
        float healthPercent1 = tank1Health / 5.0f;
        
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(tankPosition.x, tankPosition.y);
        modelMatrix *= transform2D::Rotate(rotationAngle);

        // Randare tanc+componentele sale
        RenderMesh2D(meshes["tank"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["tank1"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);
 
        glm::mat3 bar1Matrix = glm::mat3(1);
        bar1Matrix *= transform2D::Translate(tankPosition.x - barWidth / 2, tankPosition.y + 120.0f); // pozitionare bara
        RenderMesh2D(meshes["bar1"], shaders["VertexColor"], bar1Matrix);

        bar1Matrix *= transform2D::Scale(healthPercent1, 1.0f); // Scalare
        RenderMesh2D(meshes["bar12"], shaders["VertexColor"], bar1Matrix);
        
        modelMatrix *= transform2D::Translate(0.0f, 72.5f);

        // Rotatie obiect
        modelMatrix *= transform2D::Rotate(turretAngle1);

        //  Translatia inversă pentru a readuce obiectul la pozitia sa originala
        modelMatrix *= transform2D::Translate(0.0f, -72.5f);
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    }
    glm::vec2 A2, B2;
    bool pointsFound2 = false;
    for (size_t i = 0; i < terrainVertices.size() - 1; ++i) {
        if (terrainVertices[i].x <= tank2Position.x && tank2Position.x <= terrainVertices[i + 1].x) {
            A2 = glm::vec2(terrainVertices[i].x, terrainVertices[i].y);
            B2 = glm::vec2(terrainVertices[i + 1].x, terrainVertices[i + 1].y);
            pointsFound2 = true;
            break;
        }
    }
    if (pointsFound2) {
        float t = (tank2Position.x - A2.x) / (B2.x - A2.x);
        tank2Position.y = A2.y + t * (B2.y - A2.y);

        glm::vec2 direction = glm::normalize(B2 - A2);
        float rotationAngle2 = atan2(direction.y, direction.x);
        if (tank2Visible) {
            float healthPercent2 = tank2Health / 5.0f;
            glm::mat3 modelMatrix2 = glm::mat3(1);
            modelMatrix2 *= transform2D::Translate(tank2Position.x, tank2Position.y);
            modelMatrix2 *= transform2D::Rotate(rotationAngle2);
            RenderMesh2D(meshes["tank2"], shaders["VertexColor"], modelMatrix2);
            RenderMesh2D(meshes["tank2Body"], shaders["VertexColor"], modelMatrix2);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix2);
            glm::mat3 bar2Matrix = glm::mat3(1);
            bar2Matrix *= transform2D::Translate(tank2Position.x - barWidth / 2, tank2Position.y + 120.0f); // Pozitionarea barei
            RenderMesh2D(meshes["bar2"], shaders["VertexColor"], bar2Matrix);

            bar2Matrix *= transform2D::Scale(healthPercent2, 1.0f); // Scalare
            RenderMesh2D(meshes["bar22"], shaders["VertexColor"], bar2Matrix);
            // miscarea dreptunghiului pe cerc
            // miscarea turelei
            modelMatrix2 *= transform2D::Translate(0.0f, 72.5f);
            modelMatrix2 *= transform2D::Rotate(turretAngle2);
            modelMatrix2 *= transform2D::Translate(0.0f, -72.5f);
            RenderMesh2D(meshes["tank2Turret"], shaders["VertexColor"], modelMatrix2);
        }
    }



    if (isProjectileActive) {
        projectileVelocity.y -= gravity * deltaTimeSeconds; // Gravitatie pe Y
        projectilePosition += projectileVelocity * deltaTimeSeconds; // Actualizare pozitie
        if (isProjectile1Visible) {
            // proiectilul
            glm::mat3 projectileMatrix = glm::mat3(1);
            projectileMatrix *= transform2D::Translate(projectilePosition.x, projectilePosition.y);
            RenderMesh2D(meshes["circle"], shaders["VertexColor"], projectileMatrix);
        }
        // Opreste proiectilul dacă atinge pământul sau iese din ecran
        if (projectilePosition.y < 0 || projectilePosition.x > window->GetResolution().x || projectilePosition.x < 0) {
            isProjectileActive = false;
        }

        // coliziunea cu terenul
        for (size_t i = 0; i < terrainVertices.size() - 1; ++i) {
            glm::vec2 A = glm::vec2(terrainVertices[i].x, terrainVertices[i].y);
            glm::vec2 B = glm::vec2(terrainVertices[i + 1].x, terrainVertices[i + 1].y);

            if (projectilePosition.x >= A.x && projectilePosition.x <= B.x) {
                float t = (projectilePosition.x - A.x) / (B.x - A.x);
                float terrainHeight = A.y + t * (B.y - A.y)-72.f;

                if (projectilePosition.y <= terrainHeight) {
                    isProjectileActive = false;
                    break;
                }
            }
        }

    }

    if (isProjectile2Active) {
        projectile2Velocity.y -= gravity * deltaTimeSeconds; // gravitatia
        projectile2Position += projectile2Velocity * deltaTimeSeconds; 
        if (isProjectile2Visible) {
            // proiectilul2
            glm::mat3 projectile2Matrix = glm::mat3(1);
            projectile2Matrix *= transform2D::Translate(projectile2Position.x, projectile2Position.y);
            RenderMesh2D(meshes["circle"], shaders["VertexColor"], projectile2Matrix);
        }
        // Oprette proiectilul2 dacă atinge pământul sau iese din ecran
        if (projectile2Position.y < 0 || projectile2Position.x > window->GetResolution().x || projectile2Position.x < 0) {
            isProjectile2Active = false;
        }

        //coliziunea cu terenul
        for (size_t i = 0; i < terrainVertices.size() - 1; ++i) {
            glm::vec2 A = glm::vec2(terrainVertices[i].x, terrainVertices[i].y);
            glm::vec2 B = glm::vec2(terrainVertices[i + 1].x, terrainVertices[i + 1].y);

            if (projectile2Position.x >= A.x && projectile2Position.x <= B.x) {
                float t = (projectile2Position.x - A.x) / (B.x - A.x);
                float terrainHeight = A.y + t * (B.y - A.y) - 72.f;

                if (projectile2Position.y <= terrainHeight) {
                    isProjectile2Active = false;
                    break;
                }
            }
        }

    }

    glm::vec2 tank2Position2D(tank2Position.x, tank2Position.y);
    glm::vec2 tank2TurretPosition2D(tank2Position.x, tank2Position.y + 72.5f); // Pozitia turelei
    // Verificarea coliziunii cu corpul tancului
    float tankWidth = 60.0f; // l tanc
    float tankHeight = 20.0f; // h tanc
   // int tank2HitCount = 0;
    float turretWidth = 60.0f; // l
    float turretHeight = 15.0f; // h
    // Verificarea coliziunii cu corpul tancului2
    if (projectilePosition.x >= tank2Position2D.x - tankWidth / 2 && projectilePosition.x <= tank2Position2D.x + tankWidth / 2 &&
        projectilePosition.y >= tank2Position2D.y - tankHeight / 2 && projectilePosition.y <= tank2Position2D.y + tankHeight / 2) {
        isProjectile1Visible = false; // Coliziune cu corpul tancului2
        tank2HitCount++; // Creștem contorul de lovituri pentru corpul tancului
        tank2Health--;
    }

    // Verificarea coliziunii cu turela tancului2
    if (projectilePosition.x >= tank2TurretPosition2D.x - turretWidth / 2 && projectilePosition.x <= tank2TurretPosition2D.x + turretWidth / 2 &&
        projectilePosition.y >= tank2TurretPosition2D.y - turretHeight / 2 && projectilePosition.y <= tank2TurretPosition2D.y + turretHeight / 2) {
        isProjectile1Visible = false; // Coliziune cu turela tancului2
        tank2HitCount++; // Creștem contorul de lovituri pentru tureta tancului
        tank2Health--;
    }

    // Poziție inițială a proiectilului
    float startX = 0.0f;
    float startY = 100.0f;

    // Viteza inițială a proiectilului
    float startVelocityX = 50.0f;
    float startVelocityY = -100.0f;

   
    if (!isProjectile1Visible) {
        // Resetare pentru a lansa alt proiectil
        isProjectile1Visible = true;  // Face proiectilul vizibil din nou
        projectilePosition = glm::vec2(startX, startY); // Poziționează proiectilul la startX și startY
        projectileVelocity = glm::vec2(startVelocityX, startVelocityY); // Seteaza viteza inițială
    }

    
   
        if (tank2HitCount >= 5) { // După 5 lovituri
            tank2Visible = false; // Tancul 2 dispare
        }

    glm::vec2 tankPosition2D(tankPosition.x, tankPosition.y);
    glm::vec2 tankTurretPosition2D(tankPosition.x, tankPosition.y + 72.5f); // Pozitie turela

    // Verificarea coliziunii cu corpul tancului1
    float tank1Width = 60.0f; // l
    float tank1Height = 20.0f; // h
    if (projectile2Position.x >= tankPosition2D.x - tank1Width / 2 && projectile2Position.x <= tankPosition2D.x + tank1Width / 2 &&
        projectile2Position.y >= tankPosition2D.y - tank1Height / 2 && projectile2Position.y <= tankPosition2D.y + tank1Height / 2) {
        isProjectile2Visible = false; // Coliziune cu corpul tancului2
        tank1HitCount++; // Creștem contorul de lovituri pentru corpul tancului
        tank1Health--;
    }

    // Verificarea coliziunii cu turreta tancului1
    float turret1Width = 60.0f; //  l
    float turret1Height = 15.0f; // h
    if (projectile2Position.x >= tankTurretPosition2D.x - turret1Width / 2 && projectile2Position.x <= tankTurretPosition2D.x + turret1Width / 2 &&
        projectile2Position.y >= tankTurretPosition2D.y - turret1Height / 2 && projectile2Position.y <= tankTurretPosition2D.y + turret1Height / 2) {
        isProjectile2Visible = false; // Coliziune cu turreta tancului
        tank1HitCount++;
        tank1Health--;
    }
    // Poziție inițială a proiectilului
    float start2X = 0.0f;
    float start2Y = 100.0f;

    // Viteza inițială a proiectilului
    float startVelocity2X = 50.0f;
    float startVelocity2Y = -100.0f;


    if (!isProjectile2Visible) {
        // Resetare pentru a lansa alt proiectil
        isProjectile2Visible = true;  // Face proiectilul vizibil din nou
        projectile2Position = glm::vec2(start2X, start2Y); // Poziționează proiectilul la startX și startY
        projectile2Velocity = glm::vec2(startVelocity2X, startVelocity2Y); // Seteaza viteza inițială
    }



    if (tank1HitCount >= 5) { // După 5 lovituri
        tank1Visible = false; // Tancul 2 dispare
    }
}


void Lab3::FrameEnd()
{
}


void Lab3::OnInputUpdate(float deltaTime, int mods) {
    float speed = 200.0f;
    float rotationSpeed = 2.0f; // Viteza de rotatie a turelei

    if (window->KeyHold(GLFW_KEY_A)) {
        tankPosition.x -= speed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        tankPosition.x += speed * deltaTime;

    }
    if (window->KeyHold(GLFW_KEY_W)) {
        turretAngle1 += rotationSpeed * deltaTime;
        if (turretAngle1 > M_PI/2) {
            turretAngle1 = M_PI/2; 
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        turretAngle1 -= rotationSpeed * deltaTime;
        if (turretAngle1 < -M_PI/2) {
            turretAngle1 = -M_PI/2; 
        }
    }
    float tank2Speed = 200.0f;
    float tank2RotationSpeed = 2.0f;

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        tank2Position.x -= tank2Speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        tank2Position.x += tank2Speed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        turretAngle2 += tank2RotationSpeed * deltaTime;
        if (turretAngle2 > M_PI / 2) {
            turretAngle2 = M_PI / 2;
        }
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        turretAngle2 -= tank2RotationSpeed * deltaTime;
        if (turretAngle2 < -M_PI / 2) {
            turretAngle2 = -M_PI / 2;
        }
    }

}
void Lab3::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_SPACE && !isProjectileActive) {
        // pozitia initiala a proiectilului
        float turretLength = 72.5f; // l turela
        glm::vec2 turretTip = glm::vec2(
            tankPosition.x + turretLength * sin(-turretAngle1),
            tankPosition.y + turretLength * cos(turretAngle1)
        );

        projectilePosition = turretTip;

        // V initiala
        float projectileSpeed = 300.0f;
        projectileVelocity = glm::vec2(
            projectileSpeed * sin(-turretAngle1),
            projectileSpeed * cos(turretAngle1)
        );

        isProjectileActive = true;
    }
    if (key == GLFW_KEY_ENTER && !isProjectile2Active) {
        // Pozitia initiala a proiectilului
        float turret2Length = 72.5f; // Lungimea turelei
        glm::vec2 turret2Tip = glm::vec2(
            tank2Position.x + turret2Length * sin(-turretAngle2),
            tank2Position.y + turret2Length * cos(turretAngle2)
        );

        projectile2Position = turret2Tip;

        // v initiala
        float projectile2Speed = 300.0f;
        projectile2Velocity = glm::vec2(
            projectile2Speed * sin(-turretAngle2),
            projectile2Speed * cos(turretAngle2)
        );

        isProjectile2Active = true;
    }
}
void Lab3::OnKeyRelease(int key, int mods) {}
void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {}
void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}
void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}
void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void Lab3::OnWindowResize(int width, int height) {}

