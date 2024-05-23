#pragma once
#include "Components.h"
#include "ECS.h"

class RigidBodyComponent : public Component
{
private:
	PhysicsComponent* physCom;
public:
	RigidBodyComponent() = default;

	void init() override
	{
		physCom = &entity->getComponent<PhysicsComponent>();
	}

	// entity1 = pC

	void TransferVelocity(const Entity& entity1, const Entity& rigidBody)
	{
		Vector2D rigidsVelocity = rigidBody.getComponent<TransformComponent>().velocity;
		Vector2D forceEntity = entity1.getComponent<TransformComponent>().velocity;

		
		//-----------------------------------------------------------------------------------------------------------------------------
		// X Momnetum exchange
		if (entity1.getComponent<PhysicsComponent>().mass < rigidBody.getComponent<PhysicsComponent>().mass)
		{
			// the disparity of mass in percentage
			float massDiff = (entity1.getComponent<PhysicsComponent>().mass / rigidBody.getComponent<PhysicsComponent>().mass) * 100;

			// the percentage of the velocity the rigid body will gain
			//float massDiffVal = (entity1.getComponent<PhysicsComponent>().mass / 100) * massDiff;

			// calc the mass disparity percentage of the inital velocity of the colliding object
			float newVelDeducted = (forceEntity.x / 100) * massDiff;

			rigidBody.getComponent<TransformComponent>().velocity.x += newVelDeducted * rigidBody.getComponent<PhysicsComponent>().mass;
		}
		else
		{
			rigidBody.getComponent<TransformComponent>().velocity.x += forceEntity.x * rigidBody.getComponent<PhysicsComponent>().mass;
		}
		// MOMENTUM = VELOCITY * MASS
		entity1.getComponent<TransformComponent>().velocity.x -= (rigidsVelocity.x * entity1.getComponent<PhysicsComponent>().mass) * 0.01;
		

		//MAX ENTITY1 VELOCITY
		// need to apply a max velocity to the colliding item to make it not fly away when colliding with a static object
		if (entity1.getComponent<TransformComponent>().velocity.x < 0) // check if the value is negative
		{
			if ((entity1.getComponent<TransformComponent>().velocity.x * -1) > 2)
			{
				entity1.getComponent<TransformComponent>().velocity.x = -2;
			}
		}
		if (entity1.getComponent<TransformComponent>().velocity.x > 2)
		{
			entity1.getComponent<TransformComponent>().velocity.x = 2;
		}
		//-----------------------------------------------------------------------------------------------------------------------------
		//Y momentum exchange
		if (entity1.getComponent<PhysicsComponent>().mass < rigidBody.getComponent<PhysicsComponent>().mass)
		{
			// the disparity of mass in percentage
			float massDiff = (entity1.getComponent<PhysicsComponent>().mass / rigidBody.getComponent<PhysicsComponent>().mass) * 100;

			// the percentage of the velocity the rigid body will gain
			//float massDiffVal = (entity1.getComponent<PhysicsComponent>().mass / 100) * massDiff;

			// calc the mass disparity percentage of the inital velocity of the colliding object
			float newVelDeducted = (forceEntity.y / 100) * massDiff;

			rigidBody.getComponent<TransformComponent>().velocity.y += newVelDeducted * rigidBody.getComponent<PhysicsComponent>().mass;
		}
		else
		{
			rigidBody.getComponent<TransformComponent>().velocity.y += forceEntity.y * rigidBody.getComponent<PhysicsComponent>().mass;
		}
		



		////MAX RIGIDBODY VELOCITY

		//if (rigidBody.getComponent<TransformComponent>().velocity.x < 0) // check if the value is negative
		//{
		//	if ((rigidBody.getComponent<TransformComponent>().velocity.x * -1) > 2)
		//	{
		//		rigidBody.getComponent<TransformComponent>().velocity.x = -2;
		//	}
		//}
		//if (rigidBody.getComponent<TransformComponent>().velocity.x > 2)
		//{
		//	rigidBody.getComponent<TransformComponent>().velocity.x = 2;
		//}



			// add mass into the transfer object funct using f=ma

	}
};
