#pragma once
#include "Node.h"
#include "../types/Mesh.h"

class MeshRenderer : Node {

public:

	MeshRenderer();//set instance vars
	
	void Draw();

	//setters
	//getters

private:

	Mesh mesh;
	//materials?
	//shaders

};