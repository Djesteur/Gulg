#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>
#include <algorithm>

#include "GulgEngine/GulgEngine.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

namespace Gg {

namespace Algorithm {

class AbstractAlgorithm {

	public:

		AbstractAlgorithm(GulgEngine &gulgEngine);
<<<<<<< HEAD
		virtual ~AbstractAlgorithm();
=======
		virtual ~AbstractAlgorithm(); 
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025

		void addEntity(const Entity newEntity);
		void deleteEntity(const Entity entity);

		Signature getSignature() const;

		virtual void apply() = 0;
<<<<<<< HEAD
=======
		virtual void apply(const long unsigned int elapsedTime); 
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025

	protected:

		GulgEngine &m_gulgEngine;
		std::vector<Entity> m_entitiesToApply;

		Signature m_signature;
};

}}

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> fe2f1969785e2560e997539fe4e8f24cdd02b025
