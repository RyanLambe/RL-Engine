
#include "core/Window.h"
#include "graphics/Renderer.h"
#include "ecs/SystemManager.h"
#include <components/Transform.h>
#include <components/MeshComponent.h>
#include <components/Camera.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_dx11.h"
#include "core/Input.h"

using namespace rl;

std::shared_ptr<RenderTarget> imGuiRenderTarget;
ImGuiIO* io;
int newWidth;
int newHeight;
bool resized = false;

void OnWindowResize(Window* window, int width, int height){
    newWidth = width;
    newHeight = height;
    resized = true;
}

Entity cam = 1;
Entity test = 0;
void CreateEntities(){
    Transform::Create(test);
    MeshComponent::Create(test);
    MeshComponent::GetComponent(test).LoadMesh("test.obj");
    Transform::GetComponent(test).position = glm::vec3(0, 0, 5);
    Transform::GetComponent(test).SetRotation(0, 180, 0);

    Transform::Create(cam);
    Camera::Create(cam).SetMain();
}
void CameraController(){
    if(Input::GetKey(Key::W)){
        Transform::GetComponent(cam).Translate(0, 0, 0.01f);
    }
    if(Input::GetKey(Key::S)){
        Transform::GetComponent(cam).Translate(0, 0, -0.01f);
    }
    if(Input::GetKey(Key::A)){
        Transform::GetComponent(cam).Translate(-0.01f, 0, 0);
    }
    if(Input::GetKey(Key::D)){
        Transform::GetComponent(cam).Translate(0.01f, 0, 0);
    }
    if (Input::GetKey(Key::E)) {
        Transform::GetComponent(cam).Translate(0, 0.01f, 0);
    }
    if (Input::GetKey(Key::Q)) {
        Transform::GetComponent(cam).Translate(0, -0.01f, 0);
    }
    if (Input::GetKey(Key::I)) {
        Transform::GetComponent(cam).Rotate(-0.1f, 0, 0);
        //rot.x -= 0.1f;
    }
    if (Input::GetKey(Key::K)) {
        Transform::GetComponent(cam).Rotate(0.1f, 0, 0);
        //rot.x += 0.1f;
    }
    if (Input::GetKey(Key::J)) {
        Transform::GetComponent(cam).Rotate(0, -0.1f, 0);
    }
    if (Input::GetKey(Key::L)) {
        Transform::GetComponent(cam).Rotate(0, 0.1f, 0);
    }
    if (Input::GetKey(Key::O)) {
        Transform::GetComponent(cam).Rotate(0, 0, -0.1f);
    }
    if (Input::GetKey(Key::U)) {
        Transform::GetComponent(cam).Rotate(0, 0, 0.1f);
    }
}

int main() {

    // create window
    std::shared_ptr<Window> window = Window::Create(1280, 720, "RL Engine 2.0", false);
    window->setResizeCallback(OnWindowResize);

    Renderer::Start(window, false);

    // test system
    System camera;
    camera.Start = CreateEntities;
    camera.Update = CameraController;
    SystemManager::AddSystem(camera);

    /*while(!Input::GetKey(Key::F)){
        window->Update();
    }*/

    // imgui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOther((GLFWwindow*)window->getGLFWwindow(), true);
    ImGui_ImplDX11_Init((ID3D11Device*)Renderer::GetDXDevice(), (ID3D11DeviceContext*)Renderer::GetDXContext());
    imGuiRenderTarget = RenderTarget::Create(true);

    // main loop
    SystemManager::StartSystems();
    while (window->Update()){

        SystemManager::UpdateSystems();

        if(resized){
            Renderer::Resize(Renderer::getWidth(), Renderer::getHeight());
            imGuiRenderTarget->Resize(newWidth, newHeight);
            io->DisplayFramebufferScale = ImVec2(newWidth, newHeight);
            resized = false;
        }


        Renderer::Render();

        // start imgui frame
        imGuiRenderTarget->Enable();
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // create windows
        ImGui::DockSpaceOverViewport();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Renderer");
        Renderer::Resize((int)ImGui::GetContentRegionAvail().x, (int)ImGui::GetContentRegionAvail().y);
        ImGui::Image( Renderer::GetRenderTexture(), ImGui::GetContentRegionAvail());
        ImGui::End();

        // finish rendering
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        Renderer::Present();
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}