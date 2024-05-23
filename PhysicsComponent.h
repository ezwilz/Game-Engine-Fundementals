#pragma once

#include <vector>
#include <memory>

#include "GameMath.h"

#include "Components.h"
#include "ECS.h"
#include "Components.h"
#include "TransformComponent.h"
#include "PhysicsEngine.h"
#include "VisualsComponent.h"
#include "Vector2D.h"


class PhysicsComponent :public Component
{
private:
	TransformComponent* transform;
public:

	// how heavy the object is
	float mass = 0;
	// speed / acceleration
	int speed = 0;
	//bounicess is out of 100, being a percentage
	float bouncinessX = 0;
	float bouncinessY = 0;

	PhysicsComponent()
	{

	}
	PhysicsComponent(int m, int s, int bX, int bY)
	{
		mass = m;
		speed = s;
		bouncinessX = bX;
		bouncinessY = bY;
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update()
	{
		transform->transform.x += transform->velocity.x * CalculateForce();
		transform->transform.y += transform->velocity.y * CalculateForce();
	}

	//calculate the force of the moving object by considering mass and speed
	float CalculateForce()
	{
		float force = mass * speed;

		return force;
	}

	//A stationary object such as a rigid body won't have a set speed like a player object, speed needs to be
	// calclulated.
	float CalculateSpeed(float force/*force being enacted on object*/)
	{
		// to calculate the speed of object after the other object has interacted with it
		int speed = force / mass;
		return speed;
	}


	// Calculate the force an object had after hitting a solid wall etc.
	float CalculateBounce(float force, int axis)
	{
		int thisBounciness;
		// axis 1 for x, axis 2 for y 
		if (axis == 1)
		{
			thisBounciness = bouncinessX;

		}
		if (axis == 2)
		{
			thisBounciness = bouncinessY;
		}
		//calculate the % of the inital force
		float newForce = ((force / 100) * thisBounciness) + 0.3f;
		return -newForce;
	}

};


