#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <vector>
#include <array>

namespace Gg {

enum class ComponentType {

	MainMesh,
	Transformations,
	SceneObject,
	VoxelMap,
	Light,
	Collider,
	WorldCollider,
	Forces,
	Explosive,
	Timer,
	StepSound
};

const uint32_t NbComponentType = 11;

class Signature {

	public:

		Signature();
		Signature(ComponentType type);
		Signature(std::vector<ComponentType> types);
		Signature(const std::array<bool, NbComponentType> &signature);
		Signature(const Signature &second);

		void operator=(const Signature &second);

		bool operator<(const Signature &second) const;
		bool operator>(const Signature &second) const;
		bool operator==(const Signature &second) const;

		Signature operator+(const Signature &second) const;
		void operator+=(const Signature &second);

		Signature operator-(const Signature &second) const;
		void operator-=(const Signature &second);

		Signature operator|(const Signature &second) const;
		void operator|=(const Signature &second);

		Signature operator&(const Signature &second) const;
		void operator&=(const Signature &second);

		std::string asString() const;

		size_t getSignatureSize() const;

	private:

		std::array<bool, NbComponentType> m_signature;                  
};

std::ostream& operator<<(std::ostream &stream, const Signature &sign);

}

#endif