#include "Console.h"

#include <ranges>
#include <sstream>
#include <fstream>

#include "../Editor.h"

namespace rl::editor
{
    std::shared_ptr<Console> Console::window = nullptr;
    std::string Console::cmakeLog = "The project has not been compiled yet.";
    std::string Console::buildLog = "The project has not been compiled yet.";

    void Console::OpenWindow()
    {
        if (!window)
        {
            window = std::make_shared<Console>();
        }
        window->open = true;
        Editor::AddGuiElement(window);
    }

    void Console::CloseWindow()
    {
        window->open = false;
    }

    void Console::Render()
    {

        if (ImGui::Begin("Console", &open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse))
        {

            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("Logger"))
                {
                    DrawLogger();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Build"))
                {
                    ImGui::TextWrapped("%s", buildLog.c_str());
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("CMake"))
                {
                    ImGui::TextWrapped("%s", cmakeLog.c_str());
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            ImGui::End();
        }
        else
        {
            open = false;
            return;
        }
    }

    bool Console::IsOpen()
    {
        return open;
    }

    void Console::DrawLogger() {

        if(ImGui::Button("Clear")){
            Application::GetLogger().ClearMessages();
        }

        ImGui::Separator();

        if(ImGui::BeginChild("logs")){

            for(auto const& message : Application::GetLogger().GetMessages() | std::views::reverse){
                switch (message.type) {
                    case rl::Logger::LogType::Error:
                        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0, .55, .98));
                        break;

                    case rl::Logger::LogType::Warning:
                        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(36.0 / 360, .55, .98));
                        break;

                    default:
                        ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0, 0, .80));
                        break;
                }

                ImGui::TextWrapped("%s", message.GetFormatted().c_str());
                ImGui::PopStyleColor();

                if(ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)){
                    system(("explorer " + message.file).c_str());
                }

                ImGui::Separator();
            }
            ImGui::EndChild();
        }
    }

    void Console::UpdateBuildLogs() {
        std::ifstream cmakeIn("./logs/CMakeOut.txt");
        std::ostringstream cmakeSS;
        cmakeSS << cmakeIn.rdbuf();
        cmakeLog = cmakeSS.str();

        std::ifstream buildIn("./logs/BuildOut.txt");
        std::ostringstream buildSS;
        buildSS << buildIn.rdbuf();
        buildLog = buildSS.str();
    }
}