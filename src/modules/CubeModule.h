#pragma once
#include "../IModule.h"
#include "../ModuleRegistry.h"
#include <GL/freeglut.h>

class CubeModule : public IModule
{
private:
    float angleX, angleY, angleZ;
    float rotationSpeed;
    bool rotateX, rotateY, rotateZ;
    float cubeX, cubeY, cubeZ;
    float moveSpeed, dirX, dirY;
    GLfloat colors[6][3];

public:
    CubeModule();
    
    void init() override;
    void update() override;
    void draw() override;
    void handleKeyboard(unsigned char key) override;
    void handleSpecialKey(int key) override;
    void deinit() override;
    const char* getName() const override { return "Куб"; }
    
private:
    void drawCube();
    void showHelp();
    void reset();
};

// Автоматическая регистрация модуля
REGISTER_MODULE(CubeModule)