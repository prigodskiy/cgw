#include "CubeModule.h"
#include <iostream>

CubeModule::CubeModule() {
    colors[0][0] = 1.0f; colors[0][1] = 0.0f; colors[0][2] = 0.0f;
    colors[1][0] = 0.0f; colors[1][1] = 1.0f; colors[1][2] = 0.0f;
    colors[2][0] = 0.0f; colors[2][1] = 0.0f; colors[2][2] = 1.0f;
    colors[3][0] = 1.0f; colors[3][1] = 1.0f; colors[3][2] = 0.0f;
    colors[4][0] = 1.0f; colors[4][1] = 0.0f; colors[4][2] = 1.0f;
    colors[5][0] = 0.0f; colors[5][1] = 1.0f; colors[5][2] = 1.0f;
}

void CubeModule::setRandomColors(bool enable) {
    randomColors = enable;
    
    if (randomColors) {
        for (int i = 0; i < 6; i++) {
            colors[i][0] = Random::value();
            colors[i][1] = Random::value();
            colors[i][2] = Random::value();
        }
        std::cout << "Случайные цвета включены!" << std::endl;
    } else {
        colors[0][0] = 1.0f; colors[0][1] = 0.0f; colors[0][2] = 0.0f;
        colors[1][0] = 0.0f; colors[1][1] = 1.0f; colors[1][2] = 0.0f;
        colors[2][0] = 0.0f; colors[2][1] = 0.0f; colors[2][2] = 1.0f;
        colors[3][0] = 1.0f; colors[3][1] = 1.0f; colors[3][2] = 0.0f;
        colors[4][0] = 1.0f; colors[4][1] = 0.0f; colors[4][2] = 1.0f;
        colors[5][0] = 0.0f; colors[5][1] = 1.0f; colors[5][2] = 1.0f;
        std::cout << "Стандартные цвета восстановлены!" << std::endl;
    }
}

void CubeModule::reset() {
    angleX = angleY = angleZ = 0.0f;
    rotationSpeed = 2.0f;
    rotateX = rotateY = rotateZ = true;
    cubeX = cubeY = 0.0f;
    cubeZ = -5.0f;
    moveSpeed = 0.02f;
    dirX = 0.01f;
    dirY = 0.005f;
}

void CubeModule::init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 1280.0f / 720.0f;
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    reset();
    showHelp();
    
    std::cout << "=== Модуль '" << getName() << "' активирован ===" << std::endl;
}

void CubeModule::update() {
    if (rotateX) angleX += rotationSpeed;
    if (rotateY) angleY += rotationSpeed;
    if (rotateZ) angleZ += rotationSpeed;
    
    cubeX += dirX;
    cubeY += dirY;
    
    if (cubeX > 2.0f || cubeX < -2.0f) dirX = -dirX;
    if (cubeY > 1.5f || cubeY < -1.5f) dirY = -dirY;
}

void CubeModule::drawCube() {
    glBegin(GL_QUADS);
    
    glColor3fv(colors[0]);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    
    glColor3fv(colors[1]);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    
    glColor3fv(colors[2]);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    
    glColor3fv(colors[3]);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    
    glColor3fv(colors[4]);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    
    glColor3fv(colors[5]);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    glEnd();
}

void CubeModule::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0.0f, 0.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    glPushMatrix();
    glTranslatef(cubeX, cubeY, cubeZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    
    drawCube();
    
    glPopMatrix();
    glutSwapBuffers();
}

void CubeModule::handleKeyboard(unsigned char key) {
    switch (key) {
        case '1': rotateX = !rotateX; break;
        case '2': rotateY = !rotateY; break;
        case '3': rotateZ = !rotateZ; break;
        case '+': rotationSpeed += 0.5f; break;
        case '-': if (rotationSpeed > 0.5f) rotationSpeed -= 0.5f; break;
        case 'w': moveSpeed += 0.01f; break;
        case 's': if (moveSpeed > 0.01f) moveSpeed -= 0.01f; break;
        case 'r': reset(); break;
        case 'c': setRandomColors(!randomColors); break;
    }
}

void CubeModule::handleSpecialKey(int key) {
    switch (key) {
        case GLUT_KEY_UP:    cubeY += 0.1f; break;
        case GLUT_KEY_DOWN:  cubeY -= 0.1f; break;
        case GLUT_KEY_LEFT:  cubeX -= 0.1f; break;
        case GLUT_KEY_RIGHT: cubeX += 0.1f; break;
        case GLUT_KEY_PAGE_UP:   cubeZ += 0.5f; break;
        case GLUT_KEY_PAGE_DOWN: cubeZ -= 0.5f; break;
    }
}

void CubeModule::deinit() {
    std::cout << "=== Модуль '" << getName() << "' деактивирован ===" << std::endl;
}

void CubeModule::showHelp() {
    std::cout << "\n=== Управление: " << getName() << " ===" << std::endl;
    std::cout << "1, 2, 3 - Вкл/выкл вращение по осям X, Y, Z" << std::endl;
    std::cout << "+/- - Скорость вращения" << std::endl;
    std::cout << "w/s - Скорость движения" << std::endl;
    std::cout << "Стрелки - перемещение" << std::endl;
    std::cout << "Page Up/Down - приближение/отдаление" << std::endl;
    std::cout << "r - Сброс" << std::endl;
    std::cout << "c - Случайные цвета" << std::endl;
    std::cout << "=========================\n" << std::endl;
}