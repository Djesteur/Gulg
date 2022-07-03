#ifndef GULG_DECLARATIONS_HPP
#define GULG_DECLARATIONS_HPP

#include <cstdint>

namespace Gg {

	using Entity = uint32_t;

	#define NoEntity Entity{0}

	const uint32_t MaxComponentType = 256;

	namespace Component {

		enum class Type {

			Default,
			Sprite,
			ComponentType2
		};
	}

}

#endif