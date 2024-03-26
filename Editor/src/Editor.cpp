#include "Editor.h"
#include "graphics/Renderer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_dx11.h"
#include "components/Camera.h"
#include "project/ProjectManager.h"
#include "ecs/SystemManager.h"

using namespace rl::editor;

int Editor::newWidth;
int Editor::newHeight;
bool Editor::resized = false;
bool Editor::open = true;
bool Editor::playing = false;

std::vector<std::weak_ptr<GuiElement>> Editor::guiElements = std::vector<std::weak_ptr<GuiElement>>();

Editor::Editor() {

    // rl setup
    window = Window::Create(1280, 720, "RL Engine 2.0", false);
    window->setResizeCallback(OnWindowResize);
    Renderer::Start(window, false);

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    SetImGuiStyle();

    ImGui_ImplGlfw_InitForOther((GLFWwindow*)window->getGLFWwindow(), true);
    ImGui_ImplDX11_Init((ID3D11Device*)Renderer::GetDXDevice(), (ID3D11DeviceContext*)Renderer::GetDXContext());
    imGuiRenderTarget = RenderTarget::Create(true);
}

Editor::~Editor() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Editor::Render() {

    if(resized){
        Renderer::Resize(Renderer::getWidth(), Renderer::getHeight());
        imGuiRenderTarget->Resize(newWidth, newHeight);
        io->DisplayFramebufferScale = ImVec2(newWidth, newHeight);
        resized = false;
    }

    if (Camera::GetMain() != nullptr)
        Renderer::Render();

    imGuiRenderTarget->Enable();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();


    // temporary
    ImGui::ShowDemoWindow();

    for(int i = 0; i < guiElements.size(); i++)
    {
        if(const auto& elementValue = guiElements[i].lock()){
            if(elementValue->IsOpen()){
                elementValue->Render();
                continue;
            }
        }
        guiElements.erase(std::next(guiElements.begin(), i));
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    Renderer::Present();
}

bool Editor::Update() {
    return window->Update() && open;
}

void Editor::Exit() {
    open = false;
}

void Editor::OnWindowResize(Window *window, int width, int height) {
    newWidth = width;
    newHeight = height;
    resized = true;
}

void Editor::SetImGuiStyle() {
    ImGui::StyleColorsDark();
    io->Fonts->AddFontFromFileTTF("fonts/Tauri/Tauri-Regular.ttf", 18.0f);
    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 1.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

bool Editor::Playing() {
    return playing;
}

void Editor::Play() {
    //ProjectManager::Compile();
    ProjectManager::Run();
    SystemManager::StartSystems();
    playing = true;
}

void Editor::Pause() {
    playing = false;
}
