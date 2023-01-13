#pragma once
#include <msclr\marshal_cppstd.h>

#ifndef INCLUDE
#define INCLUDE
#include "../../../RL-EngineCore/include/Window.h"
#endif

#include "Managed.h"

namespace Engine {
	public ref class Mesh : public Managed<Core::Mesh> {
	public:
		Mesh(Core::Mesh* mesh);

		void ImportObj(System::String^ fileName);
	};
}