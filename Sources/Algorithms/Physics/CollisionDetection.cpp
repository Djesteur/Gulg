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
		detectedColision.missingDistance = firstHitbox->radius + secondHitbox->radius 
										 - distanceBetween;

		m_collisionsToResolve.emplace_back(detectedColision);
	}
}

void CollisionDetection::convexAndCircle(Entity convexEntity,
						     			 Entity circleEntity) {

	std::shared_ptr<Component::ConvexHitbox> convex{ 
		std::static_pointer_cast<Component::ConvexHitbox>(m_gulgEngine.getComponent(convexEntity, "Hitbox"))
	};

	std::shared_ptr<Component::CircleHitbox> circle{ 
		std::static_pointer_cast<Component::CircleHitbox>(m_gulgEngine.getComponent(circleEntity, "Hitbox"))
	};

	std::vector<Component::Vector2D> convexPoints{convex->absolutePoints};
	convexPoints.emplace_back(convexPoints[0]);

	float t{0.f}, distanceToCircle{0.f};
	bool foundPoint{false};
	Component::Vector2D AB, AM, D, collisionPoint;
	float saveT;

	for(unsigned int i{1}; i < 2; i++) {

		AB.value = sf::Vector2f{convexPoints[i+1].value.x - convexPoints[i].value.x, convexPoints[i+1].value.y - convexPoints[i].value.y};
		AM.value = sf::Vector2f{circle->centerPosition.value.x - convexPoints[i].value.x, circle->centerPosition.value.y - convexPoints[i].value.y};

		Component::Vector2D ABnorm{AB}, AMnorm{AM};
		ABnorm.value /= AB.norm();
		AMnorm.value /= AM.norm();

		t = Maths::scalarProduct(AB.value, AM.value)/(20.f*AB.norm());
		saveT = t;
		if(t <= 0.f) { t = 0.f; }
		if(t >= 1.f) { t = 1.f; } 
		D.value.x = convexPoints[i].value.x + t*AB.value.x;
		D.value.y = convexPoints[i].value.y + t*AB.value.y;

		//std::cout << AB.norm() << " " << t  << " " << Maths::distance(circle->centerPosition, D) << std::endl;
		std::cout << saveT << " " << D.value.x << " " << D.value.y << std::endl;
		//std::cout << convexPoints[i].value.x << " " << convexPoints[i].value.y <<  " ! " << AB.value.x << " " << AB.value.y
		//<<  " ! " << convexPoints[i+1].value.x << " " << convexPoints[i+1].value.y << " ! " << t << std::endl;

		if(Maths::distance(circle->centerPosition, D) < circle->radius) {

			if(!foundPoint) {

				foundPoint = true;
				collisionPoint = D;
				distanceToCircle = Maths::distance(collisionPoint, circle->centerPosition);
			}

			else if(Maths::distance(collisionPoint, circle->centerPosition) < distanceToCircle) {

				collisionPoint = D;
				distanceToCircle = Maths::distance(collisionPoint, circle->centerPosition);
			}
		}
	}

	//std::cout << "test : " << saveT << std::endl;

	if(foundPoint) { std::cout << "Collision !" << std::endl; }
}

}}