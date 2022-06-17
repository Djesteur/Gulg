#ifndef GULG_DECLARATIONS_HPP
#define GULG_DECLARATIONS_HPP

#include <cstdint>

namespace Gg {

	#define NoEntity Entity{0}

	using Entity = uint32_t;

	const uint32_t MaxComponentType = 256;

	namespace Component {

		enum class Type {

			Default,
			ComponentType1,
			ComponentType2
		};
	}

}

#endif