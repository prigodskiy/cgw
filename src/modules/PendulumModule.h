#pragma once
#include "../IModule.h"
#include "../ModuleRegistry.h"
#include "../utils/Random.h"
#include <GL/freeglut.h>

class PendulumModule : public IModule
{
private:
    float phi;
    float omega;
    float length;
    
    const float G;
    const float DT;
    
    GLfloat rodColor[3];
    GLfloat ballColor[3];
    bool randomColors;
    
    bool isRunning;
    float time;

public:
    PendulumModule();
    
    void init() override;
    void update() override;
    void draw() override;
    void handleKeyboard(unsigned char key) override;
    void handleSpecialKey(int key) override;
    void deinit() override;
    void setRandomColors(bool enable);
    const char* getName() const override { return "Маятник"; }
    
private:
    void drawPendulum();
    void showHelp();
    void reset();
};

REGISTER_MODULE(PendulumModule)