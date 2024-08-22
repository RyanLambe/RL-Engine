#pragma once

#include <filesystem>

#include "Scene.h"

namespace rl
{
    class SceneManager
    {
    public:
        inline Scene& GetCurrentScene()
        {
            if (!loadedScenes.contains(currentScene))
            {
                RL_THROW_EXCEPTION("Unable to get current scene as it has either not been loaded or set.");
            }
            return *loadedScenes[currentScene];
        }

        inline bool IsSceneOpen()
        {
            return loadedScenes.contains(currentScene);
        }

        inline bool IsSceneLoaded(const std::string& name)
        {
            return loadedScenes.contains(name);
        }

        inline void SetScene(const std::string& name)
        {
            if (!loadedScenes.contains(name))
            {
                RL_LOG_ERROR("Scene does not exist, cannot set to: ", name);
                return;
            }
            currentScene = name;
        }

        inline void UnloadScene(const std::string& name)
        {
            if (name == currentScene)
            {
                RL_LOG_ERROR("Cannot Unload scene as it is the currently set scene");
                return;
            }
            loadedScenes.erase(name);
        }

        std::string NewScene(const std::filesystem::path& file);
        std::string LoadScene(const std::filesystem::path& file);
        void SaveScene();

    private:
        std::string currentScene;
        std::unordered_map<std::string, std::shared_ptr<Scene>> loadedScenes = {};
    };
}
