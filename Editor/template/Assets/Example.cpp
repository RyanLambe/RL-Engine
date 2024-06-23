#include "Example.h"
#include <Engine.h>

using namespace rl;

namespace Example{
    
    Entity cam = 1;
    Entity test = 0;

    void Start(){
        Transform::Create(test);
        MeshComponent::Create(test);
        MeshComponent::GetComponent(test).LoadMesh("test.obj");
        Transform::GetComponent(test).position = glm::vec3(0, 0, 5);
        Transform::GetComponent(test).SetRotation(0, 180, 0);

        Transform::Create(cam);
        Camera::Create(cam).SetMain();
    }

    void Update(){
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
}