#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <memory>

#include "GulgEngine/GulgEngine.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

#include "Algorithms/Algorithm.hpp"

namespace Gg {

class System {

	public:

		System(GulgEngine &gulgEngine);
		virtual ~System(); 

		void addEntity(const Entity newEntity);
		void deleteEntity(const Entity newEntity);

		virtual void applyAlgorithms();

	protected:

		std::vector<std::unique_ptr<Algorithm>> m_algorithms;
		GulgEngine &m_gulgEngine;      
};

}

#endif