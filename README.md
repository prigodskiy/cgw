# Сборник РГР

Этот проект представляет собой сборник РГР, которые можно запустить и просмотреть одним exe-файлом.

Проект легко масштабируем, ведь в него можно без проблем добавить и другие РГР. Достаточно просто закинуть работу в папку modules, предварительно внеся правки согласно инструкции.

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
НазваниеМодуля.h — заголовочный файл (класс, объявления)
НазваниеМодуля.cpp — файл реализации (код функций)
```
#### Шаг 2. Заполните заголовочный файл (.h)

Скопируйте этот шаблон, измените название класса и перепишите свой код:

```cpp
// src/modules/НазваниеМодуля.h
#pragma once
#include "../IModule.h"
#include "../ModuleRegistry.h"
#include "../utils/Random.h"
#include <GL/freeglut.h>

class НазваниеМодуля : public IModule
{
private:
    // Ваши переменные (позиция, цвет, состояние и т.д.)
    float someValue;
    bool isRunning;

public:
    // Конструктор (опционально)
    НазваниеМодуля();

    // Обязательные методы интерфейса
    void init() override;
    void update() override;
    void draw() override;
    void handleKeyboard(unsigned char key) override;
    void handleSpecialKey(int key) override;
    void deinit() override;
    const char* getName() const override { return "Название модуля"; }

private:
    // Ваши вспомогательные методы
    void drawObject();
    void reset();
};

// Регистрация модуля
REGISTER_MODULE(НазваниеМодуля)
```

#### Шаг 3: Заполните файл реализации (.cpp)

Скопируйте этот шаблон и адаптируйте:

```cpp
// src/modules/НазваниеМодуля.cpp
#include "НазваниеМодуля.h"
#include <iostream>
#include <cmath>

НазваниеМодуля::НазваниеМодуля() : someValue(0.0f), isRunning(true)
{
    // Инициализация переменных
}

void НазваниеМодуля::init()
{
    // Настройка OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // Сброс матриц
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    reset();
    showHelp();
    
    std::cout << "=== Модуль '" << getName() << "' активирован ===" << std::endl;
}

void НазваниеМодуля::update()
{
    // Логика обновления (физика, анимация и т.д.)
    if (isRunning)
    {
        someValue += 0.01f;
    }
}

void НазваниеМодуля::drawObject()
{
    // Отрисовка вашего объекта
    // Пример: треугольник
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-1.0f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
    glEnd();
}

void НазваниеМодуля::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawObject();
    
    glutSwapBuffers();
}

void НазваниеМодуля::handleKeyboard(unsigned char key)
{
    switch (key)
    {
        case ' ':  // Пробел
            isRunning = !isRunning;
            break;
        case 'r':  // Сброс
            reset();
            break;
        case 'c':  // Случайный цвет
            // Random::color() можно использовать
            break;
    }
}

void НазваниеМодуля::handleSpecialKey(int key)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            // Обработка стрелки вверх
            break;
        case GLUT_KEY_DOWN:
            // Обработка стрелки вниз
            break;
    }
}

void НазваниеМодуля::deinit()
{
    std::cout << "=== Модуль '" << getName() << "' деактивирован ===" << std::endl;
}

void НазваниеМодуля::reset()
{
    someValue = 0.0f;
    isRunning = true;
}

void НазваниеМодуля::showHelp()
{
    std::cout << "\n=== Управление: " << getName() << " ===" << std::endl;
    std::cout << "Пробел - Старт/Пауза" << std::endl;
    std::cout << "r - Сброс" << std::endl;
    std::cout << "c - Случайный цвет" << std::endl;
    std::cout << "=========================\n" << std::endl;
}
```
