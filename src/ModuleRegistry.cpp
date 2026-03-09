#include "ModuleRegistry.h"

std::vector<std::pair<std::string, ModuleRegistry::CreatorFunc>>& 
ModuleRegistry::getCreators()
{
    static std::vector<std::pair<std::string, CreatorFunc>> creators;
    return creators;
}

void ModuleRegistry::registerModule(const std::string& name, CreatorFunc creator)
{
    getCreators().emplace_back(name, creator);
}

std::vector<std::unique_ptr<IModule>> ModuleRegistry::createAllModules()
{
    std::vector<std::unique_ptr<IModule>> modules;
    for (auto& [name, creator] : getCreators())
    {
        modules.push_back(creator());
    }
    return modules;
}

size_t ModuleRegistry::getModuleCount()
{
    return getCreators().size();
}