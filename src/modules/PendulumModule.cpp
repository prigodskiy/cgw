#include "PendulumModule.h"
#include <iostream>
#include <cmath>

PendulumModule::PendulumModule() 
    : G(9.81f), DT(0.016f), length(1.5f), randomColors(false)
{
    rodColor[0] = 0.2f;  rodColor[1] = 0.8f;  rodColor[2] = 1.0f;
    ballColor[0] = 1.0f; ballColor[1] = 0.3f; ballColor[2] = 0.3f;
}

void PendulumModule::setRandomColors(bool enable) {
    randomColors = enable;
    
    if (randomColors) {
        rodColor[0] = Random::value();
        rodColor[1] = Random::value();
        rodColor[2] = Random::value();
        
        ballColor[0] = Random::value();
        ballColor[1] = Random::value();
        ballColor[2] = Random::value();
        
        std::cout << "Случайные цвета включены!" << std::endl;
    } else {
        rodColor[0] = 0.2f;  rodColor[1] = 0.8f;  rodColor[2] = 1.0f;
        ballColor[0] = 1.0f; ballColor[1] = 0.3f; ballColor[2] = 0.3f;
        std::cout << "Стандартные цвета восстановлены!" << std::endl;
    }
}

void PendulumModule::reset()
{
    phi = 0.5f;
    omega = 0.0f;
    time = 0.0f;
    isRunning = true;
}

void PendulumModule::init() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    reset();
    showHelp();
    
    std::cout << "=== Модуль '" << getName() << "' активирован ===" << std::endl;
}

void PendulumModule::update()
{
    if (!isRunning) return;
    
    float alpha = -G / length * std::sinf(phi);
    
    omega += alpha * DT;
    phi += omega * DT;
    
    time += DT;
}

void PendulumModule::drawPendulum()
{
    float ballX = length * std::sinf(phi);
    float ballY = -length * std::cosf(phi);
    
    glColor3fv(rodColor);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(ballX, ballY);
    glEnd();
    
    glColor3fv(ballColor);
    glPointSize(20.0f);
    glBegin(GL_POINTS);
        glVertex2f(ballX, ballY);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f);
    glEnd();
}

void PendulumModule::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawPendulum();
    
    glutSwapBuffers();
}

void PendulumModule::handleKeyboard(unsigned char key)
{
    switch (key) {
        case ' ':
            isRunning = !isRunning;
            std::cout << (isRunning ? "Запущен" : "Пауза") << std::endl;
            break;
        case 'r':
            reset();
            break;
        case '+':
            length += 0.1f;
            std::cout << "Длина маятника: " << length << std::endl;
            break;
        case '-':
            if (length > 0.5f) length -= 0.1f;
            std::cout << "Длина маятника: " << length << std::endl;
            break;
        case 'c':
            setRandomColors(!randomColors);
            break;
    }
}

void PendulumModule::handleSpecialKey(int key)
{
    switch (key) {
        case GLUT_KEY_UP:
            phi += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            phi -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            omega -= 0.5f;
            break;
        case GLUT_KEY_RIGHT:
            omega += 0.5f;
            break;
    }
}

void PendulumModule::deinit()
{
    std::cout << "=== Модуль '" << getName() << "' деактивирован ===" << std::endl;
}

void PendulumModule::showHelp()
{
    std::cout << "\n=== Управление: " << getName() << " ===" << std::endl;
    std::cout << "Пробел - Пауза/Старт" << std::endl;
    std::cout << "r - Сброс положения" << std::endl;
    std::cout << "+/- - Увеличить/уменьшить длину маятника" << std::endl;
    std::cout << "Стрелки ВВЕРХ/ВНИЗ - изменить угол" << std::endl;
    std::cout << "Стрелки ВЛЕВО/ВПРАВО - толкнуть маятник" << std::endl;
    std::cout << "c - Случайные цвета" << std::endl;
    std::cout << "=========================\n" << std::endl;
}