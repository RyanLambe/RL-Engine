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
            if(currentScene >= loadedScenes.size()){
                RL_THROW_EXCEPTION("Unable to get current scene as it has either not been loaded or set.");
            }
            return *loadedScenes[currentScene];
        }

        inline bool IsSceneLoaded(const std::string& name)
        {
            for(const auto& scene : loadedScenes){
                if(scene->name == name)
                    return true;
            }
            return false;
        }

        inline void SetScene(const std::string& name)
        {
            for(size_t i = 0; i < loadedScenes.size(); i++){
                if(loadedScenes[i]->name == name){
                    currentScene = i;
                    break;
                }
            }
        }

        inline void UnloadScene(const std::string& name)
        {
            for(size_t i = 0; i < loadedScenes.size(); i++){
                if(loadedScenes[i]->name == name){
                    if(i == currentScene){
                        RL_LOG_ERROR("Cannot Unload scene as it is the currently set scene");
                        return;
                    }
                    loadedScenes.erase(loadedScenes.begin() + i);
                    break;
                }
            }
        }

        std::string NewScene(const std::filesystem::path& file);
        std::string LoadScene(const std::filesystem::path& file);
        void SaveScene();

    private:
        size_t currentScene = 0;
        std::vector<std::shared_ptr<Scene>> loadedScenes = {};
    };
}
