#ifndef GULG_DECLARATIONS_HPP
#define GULG_DECLARATIONS_HPP

#include <cstdint>
#include <concepts>

namespace Gg {

	///////////////////////////////////////////////////////////////////////////////
	// The type of the entities                                                  //
	///////////////////////////////////////////////////////////////////////////////
	using Entity = uint32_t;



	/// The "null" entity
	#define NoEntity Entity{0}

	namespace Component {

		class AbstractComponent;
		enum class Type;

		/**
		 * \concept ComponentConstraint
		 * @brief Constraint for the component. Must inherits of AbstractComponent, and has a satic function with the signature: Component::Type getType();
		 */
		template<class T> 											
		concept ComponentConstraint = requires(T a) {   			
	 																
			std::derived_from<T, Component::AbstractComponent> == true;        
			{T::getType()} -> std::convertible_to<Type>; 
		};

	}

	namespace System {

		class AbstractSystem;
		
		/**
		 * \concept SystemConstraint
		 * @brief Constraint for the systems. Must inherits of AbstractSystem
		 */
		template<class T> 											
		concept SystemConstraint = requires(T a) {   			
	 																
			std::derived_from<T, System::AbstractSystem> == true;        
		};

	}

}

#endif