#include "SceneManager.h"

#include <fstream>

namespace rl
{
    std::string rl::SceneManager::NewScene(const std::filesystem::path& filePath) {
        loadedScenes.push_back(std::make_shared<Scene>(filePath));

        return filePath.stem().string();
    }

    std::string SceneManager::LoadScene(const std::filesystem::path& filePath) {
        loadedScenes.push_back(std::make_shared<Scene>(filePath));
        Scene::LoadFromFile(loadedScenes.back().get(), filePath);
        return filePath.stem().string();
    }

    void SceneManager::SaveScene() {
        loadedScenes[currentScene]->SaveToFile();
    }
}

