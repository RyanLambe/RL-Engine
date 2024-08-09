#include "SceneManager.h"

#include <fstream>

namespace rl
{
    std::string rl::SceneManager::NewScene(const std::filesystem::path& filePath) {
        loadedScenes.emplace_back(filePath, std::make_shared<Scene>());
        return filePath.stem().string();
    }

    std::string SceneManager::LoadScene(const std::filesystem::path& filePath) {
        loadedScenes.emplace_back(filePath, std::make_shared<Scene>());
        Scene::LoadFromFile(loadedScenes.back().second.get(), loadedScenes.back().first);
        return filePath.stem().string();
    }

    void SceneManager::SaveScene() {
        Scene::SaveToFile(*loadedScenes[currentScene].second, loadedScenes[currentScene].first);
    }
}

