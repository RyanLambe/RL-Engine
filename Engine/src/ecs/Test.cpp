
#include <vector>
#include "Component.h"

/**
 * 2 Ways to effect the gameplay:
 *   1. Scripts
 *      - There will be a scripting system that runs the script components
 *      - Each Script will be a C++ Class that inherits from a common Script class
 *      - Each Script will have the following functions: Start, Update
 *   2. Systems
 *      - Systems are functions that happen once per frame
 *      - Systems should loop over every Component of a specific type
 *      -
 *
 */

// needs to be created with special function for each entity it is attached to
// how to set values from editor???
struct Transform : rl::Component<Transform> {
    float Size;
    float Location;
};

struct Mesh : rl::Component<Mesh> {
    int test, te2;
};

// needs to be added to list of functions to call
void RenderSystemV1(){
    for(Mesh& mesh : Mesh::GetAllComponents()){
        if(!Transform::HasComponent(mesh.getEntity()))
            continue;

        // do stuff
    }
}

void RenderSystemV2(){
    for(Entity entity : Scene::GetEntitiesWithComponents<Mesh, Transform>()){
        // do stuff
    }
}

// script
void Update(){

    this.GetComponent<Mesh>();

    transform.Translate();


}