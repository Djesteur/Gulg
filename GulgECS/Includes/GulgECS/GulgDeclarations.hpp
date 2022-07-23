#ifndef GULG_DECLARATIONS_HPP
#define GULG_DECLARATIONS_HPP

#include <cstdint>
#include <concepts>

namespace Gg {

	using Entity = uint32_t;

	#define NoEntity Entity{0}

	namespace Component {

		class AbstractComponent;
		enum class Type;
		

		template<class T> 											
		concept ComponentConstraint = requires(T a) {   			
	 																
			std::derived_from<T, Component::AbstractComponent> == true;        
			{T::getType()} -> std::convertible_to<Type>; 
		};

	}

	namespace System {

		class AbstractSystem;
		
		template<class T> 											
		concept SystemConstraint = requires(T a) {   			
	 																
			std::derived_from<T, System::AbstractSystem> == true;        
		};

	}

}

#endif