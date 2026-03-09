# Сборник РГР

Этот проект представляет собой сборник работ РГР, которые можно запустить и просмотреть одним exe-файлом.

Проект легко масштабируем, ведь в него можно без проблем добавить и другие РГР. Достаточно просто закинуть работу в папку modules, предварительно переведя её в нужную форму.

> [!NOTE]
> Важно, чтобы РГР были реализованы с использованием библиотеки freeglut (все зависимости уже включены в проект).

Переключение между проектами осуществляется с помощью клавиш A (предыдущий) и D (следующий).

## РГР, которые уже лежат в папке modules

> По экрану движется вращающийся куб, изображаемый в виде граней. Вариант: управление вращением с клавиатуры.

> «Реальный маятник». В маятнике, закрепленном на жесткой оси, составляющая силы тяжести, вызывающая угловое ускорение равна F0 * sin(fi), при малых fi ≈ sin(fi) – маятник становится математическим. Изобразить график колебаний маятника y(t).

## Инструкция, как перевести любой standalone C++ файл в модуль

#### Шаг 1. Создайте два файла модуля

Создайте в папке src/modules/ два файла:
```cpp
Module.h — заголовочный файл (класс, объявления)
Module.cpp — файл реализации (код функций)
```
#### Шаг 2. Заполните заголовочный файл (.h)

Скопируйте этот шаблон и адаптируйте под свой проект:

```cpp
// src/modules/Module.h

#pragma once
#include "../IModule.h"
#include "../ModuleRegistry.h"
#include <GL/freeglut.h>

class Module : public IModule
{
private:
    // === ПЕРЕМЕННЫЕ ИЗ ОРИГИНАЛЬНОГО ФАЙЛА ===
    // Перенесите все глобальные переменные сюда
    // Пример:
    // float angleX, angleY, angleZ;
    // float rotationSpeed;
    // bool isRunning;
    
    // === ЦВЕТА И НАСТРОЙКИ ===
    GLfloat someColor[3];

public:
    Module();  // Конструктор
    
    // === ОБЯЗАТЕЛЬНЫЕ МЕТОДЫ (наследуются от IModule) ===
    void init() override;
    void update() override;
    void draw() override;
    void handleKeyboard(unsigned char key) override;
    void handleSpecialKey(int key) override;
    void deinit() override;
    
    // === НАЗВАНИЕ МОДУЛЯ (отображается в консоли) ===
    const char* getName() const override { return "[Название модуля]"; }
    
private:
    // === ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ===
    // Перенесите свои функции сюда
    // Пример:
    // void drawObject();
    // void reset();
    // void showHelp();
};

// === АВТОМАТИЧЕСКАЯ РЕГИСТРАЦИЯ (ОБЯЗАТЕЛЬНО!) ===
REGISTER_MODULE(Module)
```

#### Шаг 3: Заполните файл реализации (.cpp)

Скопируйте этот шаблон и адаптируйте:

```cpp
// src/modules/Module.cpp

#include "Module.h"
#include <iostream>
#include <cmath>

// === КОНСТРУКТОР ===
Module::Module()
{
    // Инициализация переменных из оригинального файла
    // Пример:
    // angleX = angleY = angleZ = 0.0f;
    // rotationSpeed = 2.0f;
    someColor[0] = 1.0f; someColor[1] = 0.0f; someColor[2] = 0.0f;
}

// === ИНИЦИАЛИЗАЦИЯ (вызывается при переключении на модуль) ===
void Module::init()
{
    // Настройка OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    // === ВАЖНО: Сброс матриц ===
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Для 3D:
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    // Для 2D:
    // gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Включите/выключите нужные режимы
    glEnable(GL_DEPTH_TEST);      // Для 3D
    // glDisable(GL_DEPTH_TEST);  // Для 2D
    
    // Сброс переменных
    reset();
    showHelp();
    
    std::cout << "=== Модуль '" << getName() << "' активирован ===" << std::endl;
}

// === ОБНОВЛЕНИЕ ЛОГИКИ (вызывается каждый кадр) ===
void Module::update()
{
    // Перенесите код из оригинальной функции timer()
    // Пример:
    // angleX += rotationSpeed;
    // if (angleX > 360.0f) angleX = 0.0f;
}

// === ОТРИСОВКА (вызывается каждый кадр) ===
void Module::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Для 3D добавьте камеру:
    // gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    // Вызовите свою функцию отрисовки
    drawObject();
    
    glutSwapBuffers();
}

// === ОБРАБОТКА ОБЫЧНЫХ КЛАВИШ (a-z, 0-9, ESC, пробел) ===
void Module::handleKeyboard(unsigned char key)
{
    switch (key) {
        case 'r': reset(); break;
        case '+': /* что-то */ break;
        case '-': /* что-то */ break;
        case 27: break;  // ESC обрабатывается в main.cpp
    }
}

// === ОБРАБОТКА СПЕЦИАЛЬНЫХ КЛАВИШ (стрелки, F1-F12, Page Up/Down) ===
void Module::handleSpecialKey(int key)
{
    switch (key) {
        case GLUT_KEY_UP:    /* что-то */ break;
        case GLUT_KEY_DOWN:  /* что-то */ break;
        case GLUT_KEY_LEFT:  /* что-то */ break;
        case GLUT_KEY_RIGHT: /* что-то */ break;
        case GLUT_KEY_PAGE_UP:   /* что-то */ break;
        case GLUT_KEY_PAGE_DOWN: /* что-то */ break;
    }
}

// === ОЧИСТКА (вызывается при переключении с модуля) ===
void Module::deinit()
{
    std::cout << "=== Модуль '" << getName() << "' деактивирован ===" << std::endl;
}

// === ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ===

void Module::reset()
{
    // Сброс всех переменных к начальным значениям
}

void Module::drawObject()
{
    // Перенесите код отрисовки из оригинальной функции display()
    // Пример для куба:
    /*
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    // ... остальные вершины
    glEnd();
    */
}

void Module::showHelp()
{
    std::cout << "\n=== Управление: " << getName() << " ===" << std::endl;
    std::cout << "r - Сброс" << std::endl;
    std::cout << "ESC - Выход из программы" << std::endl;
    std::cout << "=========================\n" << std::endl;
}
```