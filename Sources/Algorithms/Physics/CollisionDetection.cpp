#include "Algorithms/Physics/CollisionDetection.hpp"

namespace Gg {
namespace Algorithm {

CollisionDetection::CollisionDetection(GulgEngine &gulgEngine, std::vector<Collision> &collisionsToResolve): 
	AbstractAlgorithm{gulgEngine},
	m_collisionsToResolve{collisionsToResolve} {

	m_signature = gulgEngine.getComponentSignature("Hitbox");
}

CollisionDetection::~CollisionDetection() {}

void CollisionDetection::apply() {

	m_collisionsToResolve.clear();
	m_collisionsToResolve.reserve(m_entitiesToApply.size()*m_entitiesToApply.size());

	for(unsigned int i{0}; i < m_entitiesToApply.size(); i++) {

		std::shared_ptr<Component::AbstractHitbox> firstHitbox{ 
			std::static_pointer_cast<Component::AbstractHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[i], "Hitbox"))
		};

		for(unsigned int j{i+1}; j < m_entitiesToApply.size(); j++) {

			std::shared_ptr<Component::AbstractHitbox> secondHitbox{ 
				std::static_pointer_cast<Component::AbstractHitbox>(m_gulgEngine.getComponent(m_entitiesToApply[j], "Hitbox"))
			};

			if(firstHitbox->isCircle() && secondHitbox->isCircle()) {

				bothCircleCollision(m_entitiesToApply[i], m_entitiesToApply[j]);
			}

			else if(!firstHitbox->isCircle() && !secondHitbox->isCircle()) {}

			else {

				if(firstHitbox->isCircle()) { convexAndCircle(m_entitiesToApply[j], m_entitiesToApply[i]); }
				else { convexAndCircle(m_entitiesToApply[i], m_entitiesToApply[j]); }
			}
		}
	}
}

void CollisionDetection::bothCircleCollision(Entity firstEntity,
											 Entity secondEntity) {

	std::shared_ptr<Component::CircleHitbox> firstHitbox{ 
		std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(firstEntity, "Hitbox"))
	};

	std::shared_ptr<Component::CircleHitbox> secondHitbox{ 
		std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(secondEntity, "Hitbox"))
	};

	if(Maths::distance(firstHitbox->centerPosition, secondHitbox->centerPosition) 
					< firstHitbox->radius + secondHitbox->radius) {

		float distanceBetween{Maths::distance(firstHitbox->centerPosition, secondHitbox->centerPosition)};

		Collision detectedColision;
		detectedColision.firstEntity = firstEntity;
		detectedColision.secondEntity = secondEntity;
		detectedColision.collisionPoint.value = (firstHitbox->centerPosition.value + secondHitbox->centerPosition.value)/2.f;
		detectedColision.firstDirection.value = Maths::vectorFromPoints(detectedColision.collisionPoint.value, firstHitbox->centerPosition.value).value/distanceBetween;
		detectedColision.secondDirection.value = Maths::vectorFromPoints(detectedColision.collisionPoint.value, secondHitbox->centerPosition.value).value/distanceBetween;
		detectedColision.missingDistanceFirst = (firstHitbox->radius + secondHitbox->radius - distanceBetween)/2.f;
		detectedColision.missingDistanceSecond = detectedColision.missingDistanceFirst;

		m_collisionsToResolve.emplace_back(detectedColision);
	}
}

void CollisionDetection::convexAndCircle(Entity convexEntity, Entity circleEntity) {

	std::shared_ptr<Component::ConvexHitbox> convex{ 
		std::static_pointer_cast<Component::ConvexHitbox>(m_gulgEngine.getComponent(convexEntity, "Hitbox"))
	};

	std::shared_ptr<Component::CircleHitbox> circle{ 
		std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(circleEntity, "Hitbox"))
	};

	std::vector<Component::Vector2D> convexPoints{convex->absolutePoints};
	convexPoints.emplace_back(convexPoints[0]);

	float t{0.f}, tx, ty, radiusDistance{0.0}, distanceToCircle{0.f};
	bool foundPoint{false};
	Component::Vector2D AB, AM, D, collisionPoint, nn1;
	float saveT;

	Component::Vector2D nH, nC, H, v;

	for(unsigned int i{0}; i < convexPoints.size()-1; i++) {

		v.value = sf::Vector2f{convexPoints[i+1].value.x - convexPoints[i].value.x, convexPoints[i+1].value.y - convexPoints[i].value.y};
		if(v.norm() == 0.f) {

			throw std::runtime_error("Collision Detection error: find a null vector (two points of the polygon are at the same place");
		}

		v.value /= v.norm();
		nn1.value = sf::Vector2f{convexPoints[i+1].value.x - convexPoints[i].value.x, convexPoints[i+1].value.y - convexPoints[i].value.y};
		nC.value = sf::Vector2f{circle->centerPosition.value.x - convexPoints[i].value.x, circle->centerPosition.value.y - convexPoints[i].value.y};
		nH.value = Maths::scalarProduct(nC.value, v.value)*v.value;
		H.value = sf::Vector2f{convexPoints[i].value.x + nH.value.x, convexPoints[i].value.y + nH.value.y};

		if(convexPoints[i+1].value.x - convexPoints[i].value.x == 0.f) { //In case where v.x = 0;

			t = (H.value.y - convexPoints[i].value.y)/(convexPoints[i+1].value.y - convexPoints[i].value.y);
		}

		else {

			t = (H.value.x - convexPoints[i].value.x)/(convexPoints[i+1].value.x - convexPoints[i].value.x);

		}

		radiusDistance = circle->radius/nn1.norm();

		if(t >= 0.f - radiusDistance && t <= 1.0 + radiusDistance && Maths::distance(circle->centerPosition, H) < circle->radius) {

			//Collision

			if(!foundPoint) {

				foundPoint = true;
				collisionPoint = H;
				distanceToCircle = Maths::distance(collisionPoint, circle->centerPosition);
			}

			else if(Maths::distance(collisionPoint, circle->centerPosition) < distanceToCircle) {

				collisionPoint = D;
				distanceToCircle = Maths::distance(collisionPoint, circle->centerPosition);
			}
		}
	}

	if(foundPoint) {

		Collision detectedColision;
		detectedColision.firstEntity = convexEntity;
		detectedColision.secondEntity = circleEntity;
		detectedColision.collisionPoint = collisionPoint;
		detectedColision.firstDirection.value = Maths::vectorFromPoints(collisionPoint.value, convex->centerPosition.value).value;
		detectedColision.secondDirection.value = Maths::vectorFromPoints(collisionPoint.value, circle->centerPosition.value).value;
		detectedColision.missingDistanceFirst = 0.0;
		detectedColision.missingDistanceSecond = circle->radius - Maths::distance(circle->centerPosition, H);

		m_collisionsToResolve.emplace_back(detectedColision);
	}
}

}}