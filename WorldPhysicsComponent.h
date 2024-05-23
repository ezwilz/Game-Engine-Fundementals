#pragma once
#include "Components.h"
#include "PhysicsComponent.h"

class WorldPhysics : public Component
{
private:
	TransformComponent* transform;
	PhysicsComponent* physicsCom;
public:
	float worldResistance = 0.1f;
	WorldPhysics()
	{

	}
	// this class will handle all forces acting on the object by defualt.
	//e.g. gravity, drag/air resistance

	void init()
	{
		transform = &entity->getComponent<TransformComponent>();
		physicsCom = &entity->getComponent<PhysicsComponent>();
	}

	void update()
	{
		//enact gravity on object
		ApplyGravityToEntity();
		//enact drag on object
		ApplyDragToEntity();
		// turn the velocity to 0 if the velocity is close to it to prevent sliding
		PreventSliding();
	}

	void ApplyGravityToEntity()
	{
		transform->velocity.y += worldResistance;
	}

	void ApplyDragToEntity()
	{

		if (transform->velocity.x > 0) { transform->velocity.x -= worldResistance; };
		if (transform->velocity.x < 0) { transform->velocity.x += worldResistance; };
	}

	void PreventSliding()
	{
		if (transform->velocity.x < 0.3f && transform->velocity.x > -0.3f) { transform->velocity.x = 0; }
		//if (transform->velocity.y < 0.09f && transform->velocity.y > -0.09f) { transform->velocity.y = 0; }
	}
};