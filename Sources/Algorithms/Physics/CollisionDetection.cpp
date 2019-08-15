#include "Algorithms/Physics/CollisionDetection.hpp"

namespace Gg {
namespace Algorithm {

CollisionDetection::CollisionDetection(GulgEngine &gulgEngine, std::vector<std::pair<Entity, Entity>> &collisionsToResolve): 
	AbstractAlgorithm{gulgEngine},
	m_collisionsToResolve{collisionsToResolve} {

	m_signature = gulgEngine.getComponentSignature("Hitbox");
}

CollisionDetection::~CollisionDetection() {}

void CollisionDetection::apply() {

	m_collisionsToResolve.clear();
	m_collisionsToResolve.reserve(m_entitiesToApply.size()*m_entitiesToApply.size());

	bool theyIsACollision{false};

	for(unsigned int i{0}; i < m_entitiesToApply.size(); i++) {

		std::shared_ptr<Component::AbstractHitbox> firstHitbox{ 
			std::static_pointer_cast<Component::AbstractHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[i], "Hitbox"))
		};

		for(unsigned int j{i+1}; j < m_entitiesToApply.size(); j++) {

			std::shared_ptr<Component::AbstractHitbox> secondHitbox{ 
				std::static_pointer_cast<Component::AbstractHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[j], "Hitbox"))
			};

			if(firstHitbox->isCircle() && secondHitbox->isCircle()) {

				theyIsACollision = bothCircleCollision(std::static_pointer_cast<Component::CircleHitbox>(firstHitbox),
													   std::static_pointer_cast<Component::CircleHitbox>(secondHitbox));
			}

			else if(!firstHitbox->isCircle() && !secondHitbox->isCircle()) {}

			else {

				if(firstHitbox->isCircle()) {

					theyIsACollision = convexAndCircle(std::static_pointer_cast<Component::ConvexHitbox>(secondHitbox),
													   std::static_pointer_cast<Component::CircleHitbox>(firstHitbox));
				}

				else {

					theyIsACollision = convexAndCircle(std::static_pointer_cast<Component::ConvexHitbox>(firstHitbox),
													   std::static_pointer_cast<Component::CircleHitbox>(secondHitbox));
				}
			}

			if(theyIsACollision) { 
				//m_collisionsToResolve.emplace_back(std::make_pair(m_entitiesToApply[i], m_entitiesToApply[j])); 
				std::cout << "Collision !" << std::endl;
			}
		}
	}
}

bool CollisionDetection::bothCircleCollision(std::shared_ptr<Component::CircleHitbox> firstHitbox,
											 std::shared_ptr<Component::CircleHitbox> secondHitbox) const {

	if(Maths::distance(firstHitbox->centerPosition, secondHitbox->centerPosition) 
					<= firstHitbox->radius + secondHitbox->radius) {

		return true;
	}

	return false;
}

bool CollisionDetection::convexAndCircle(std::shared_ptr<Component::ConvexHitbox> convexHitbox,
						     			 std::shared_ptr<Component::CircleHitbox> circleHitbox) const {

	/*
		A: first point
		B: second point
		C: center of circle
		D: projection
		t: parameter of the equation of the line with director vector AB
	*/

	std::vector<Component::Vector2D> points{convexHitbox->absolutePoints};
	points.emplace_back(points[0]);

	for(unsigned int i{0}; i < points.size()-1; i++) {

		Component::Vector2D AB{Maths::vectorFromPoints(points[i].value, points[i+1].value)}, ABNormalize;
		ABNormalize.value = AB.value/AB.norm();

		float b = (ABNormalize.value.x*(circleHitbox->centerPosition.value.x - points[i].value.x) +
				   ABNormalize.value.y*(circleHitbox->centerPosition.value.y - points[i].value.y));

		float delta = b*b;

		float t = -b/(-ABNormalize.value.x*ABNormalize.value.x -ABNormalize.value.y*ABNormalize.value.y);
		Component::Vector2D D{points[i].value.x + ABNormalize.value.x*t, points[i].value.y + ABNormalize.value.y*t};

		float distanceProjectionToCircle{Maths::distance(circleHitbox->centerPosition, D)};
		float bonusDistanceToCheck{sqrt(circleHitbox->radius*circleHitbox->radius - distanceProjectionToCircle*distanceProjectionToCircle)};

		std::cout << t << std::endl;
		//First check if D is between A and B

		if(t >= (0.f - bonusDistanceToCheck) 
		&& t <= (AB.norm() + bonusDistanceToCheck)) {

			//Check distance with circle

			if(distanceProjectionToCircle <= circleHitbox->radius) { return true; }
		}
	}

	return false;
}

}}