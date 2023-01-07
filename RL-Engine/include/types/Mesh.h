#pragma once
#include "../../pch.h"

#include <msclr\marshal_cppstd.h>

#include "Managed.h"

namespace Engine {
	public ref class Mesh : public Managed<Core::Mesh> {
	public:
		Mesh();

		void ImportObj(System::String^ fileName);
	};
}