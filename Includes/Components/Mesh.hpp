#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <Libraries/glm/glm.hpp>

#include "Vulkan/VulkanDeclaration.hpp"

struct Mesh {

	void fillFinalArray();

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colors;

	std::vector<glm::vec3> m_finalArray;

	std::vector<uint32_t> m_indices;
};

Mesh loadFromFile(const std::string &path);


#endif