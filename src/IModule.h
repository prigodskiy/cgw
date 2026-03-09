#pragma once

class IModule
{
public:
    virtual ~IModule() {}

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void handleKeyboard(unsigned char key) = 0;
    virtual void handleSpecialKey(int key) = 0;
    virtual void deinit() = 0;
    virtual const char* getName() const = 0;  // Название модуля для отображения
};