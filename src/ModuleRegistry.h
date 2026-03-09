#pragma once
#include "IModule.h"
#include <vector>
#include <memory>
#include <string>
#include <functional>

class ModuleRegistry
{
public:
    using CreatorFunc = std::function<std::unique_ptr<IModule>()>;
    
    // Регистрация модуля (вызывается автоматически при загрузке модуля)
    static void registerModule(const std::string& name, CreatorFunc creator);
    
    // Получение всех зарегистрированных модулей
    static std::vector<std::unique_ptr<IModule>> createAllModules();
    
    // Получение количества модулей
    static size_t getModuleCount();
    
private:
    static std::vector<std::pair<std::string, CreatorFunc>>& getCreators();
};

// Макрос для автоматической регистрации модуля
#define REGISTER_MODULE(ModuleClass) \
    static bool ModuleClass##_registered = []() { \
        ModuleRegistry::registerModule(#ModuleClass, []() { \
            return std::make_unique<ModuleClass>(); \
        }); \
        return true; \
    }();