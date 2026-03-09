#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <memory>
#include "ModuleRegistry.h"
#include "IModule.h"

// Глобальные переменные
std::vector<std::unique_ptr<IModule>> modules;
int currentModuleIndex = 0;
bool isRunning = true;

// Колбэки
void displayFunc() {
    modules[currentModuleIndex]->draw();
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC
        isRunning = false;
        glutLeaveMainLoop();
        return;
    }
    
    // Переключение модулей стрелками
    if (key == GLUT_KEY_LEFT || key == 'p') {
        modules[currentModuleIndex]->deinit();
        currentModuleIndex = (currentModuleIndex - 1 + modules.size()) % modules.size();
        modules[currentModuleIndex]->init();
        std::cout << ">>> Переключено на: " << modules[currentModuleIndex]->getName() << std::endl;
        return;
    }
    
    if (key == GLUT_KEY_RIGHT || key == 'n') {
        modules[currentModuleIndex]->deinit();
        currentModuleIndex = (currentModuleIndex + 1) % modules.size();
        modules[currentModuleIndex]->init();
        std::cout << ">>> Переключено на: " << modules[currentModuleIndex]->getName() << std::endl;
        return;
    }
    
    modules[currentModuleIndex]->handleKeyboard(key);
}

void specialKeysFunc(int key, int x, int y) {
    // Стрелки влево/вправо для переключения модулей
    if (key == GLUT_KEY_LEFT) {
        modules[currentModuleIndex]->deinit();
        currentModuleIndex = (currentModuleIndex - 1 + modules.size()) % modules.size();
        modules[currentModuleIndex]->init();
        std::cout << ">>> Переключено на: " << modules[currentModuleIndex]->getName() << std::endl;
        return;
    }
    
    if (key == GLUT_KEY_RIGHT) {
        modules[currentModuleIndex]->deinit();
        currentModuleIndex = (currentModuleIndex + 1) % modules.size();
        modules[currentModuleIndex]->init();
        std::cout << ">>> Переключено на: " << modules[currentModuleIndex]->getName() << std::endl;
        return;
    }
    
    modules[currentModuleIndex]->handleSpecialKey(key);
}

void timerFunc(int value) {
    if (!isRunning) return;
    modules[currentModuleIndex]->update();
    glutPostRedisplay();
    glutTimerFunc(16, timerFunc, 0);
}

void reshapeFunc(int width, int height) {
    float aspect = (height == 0) ? 1.0f : (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    
    // Автоматически получаем ВСЕ зарегистрированные модули
    modules = ModuleRegistry::createAllModules();
    
    if (modules.empty()) {
        std::cerr << "Ошибка: нет зарегистрированных модулей!" << std::endl;
        return 1;
    }
    
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(300, 125);
    glutCreateWindow("Модульная система");
    
    // Инициализируем первый модуль
    modules[currentModuleIndex]->init();
    
    // Регистрируем колбэки
    glutDisplayFunc(displayFunc);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialKeysFunc);
    glutTimerFunc(16, timerFunc, 0);
    
    std::cout << "\n=== Запущено модулей: " << ModuleRegistry::getModuleCount() << " ===" << std::endl;
    for (size_t i = 0; i < modules.size(); i++) {
        std::cout << "  " << i + 1 << ". " << modules[i]->getName() << std::endl;
    }
    std::cout << "\nСтрелки ВЛЕВО/ВПРАВО - переключение модулей" << std::endl;
    std::cout << "ESC - выход\n" << std::endl;
    
    glutMainLoop();
    
    modules[currentModuleIndex]->deinit();
    return 0;
}