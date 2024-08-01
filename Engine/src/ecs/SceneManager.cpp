#include "SceneManager.h"

#include <fstream>

namespace rl
{
    std::string rl::SceneManager::NewScene(const std::filesystem::path& filePath) {
        std::ofstream file(filePath);


        file.close();
        return filePath.stem().string();
    }

    std::string SceneManager::LoadScene(const std::filesystem::path& filePath) {
        return "";
    }

    void SceneManager::SaveScene() {
        std::ofstream file(loadedScenes[currentScene].first);
        if(!file.is_open()){
            RL_LOG_ERROR("Save Failed. Unable to open the Scene file: ", loadedScenes[currentScene].first.string());
            return;
        }



        file.close();
    }
}

