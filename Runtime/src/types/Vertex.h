#pragma once

#include <glm/glm.hpp>

namespace rl {
	struct Vertex {
		
		glm::vec3 position;
		glm::vec2 texCoords;
		glm::vec3 normal;

		bool operator==(const Vertex& other) const {
			if (position != other.position)
				return false;
			if (texCoords != other.texCoords)
				return false;
			if (normal != other.normal)
				return false;

			return true;
		}
	};
}