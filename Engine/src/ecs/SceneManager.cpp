#include "SceneManager.h"

#include <fstream>

namespace rl
{
    std::string rl::SceneManager::NewScene(const std::filesystem::path& filePath)
    {
        loadedScenes[filePath.stem().string()] = std::make_shared<Scene>(filePath);

        return filePath.stem().string();
    }

    std::string SceneManager::LoadScene(const std::filesystem::path& filePath)
    {
        loadedScenes[filePath.stem().string()] = std::make_shared<Scene>(filePath);
        Scene::LoadFromFile(loadedScenes[filePath.stem().string()].get(), filePath);
        return filePath.stem().string();
    }

    void SceneManager::SaveScene()
    {
        if (loadedScenes.find(currentScene) == loadedScenes.end())
            return;
        loadedScenes[currentScene]->SaveToFile();
    }
}
