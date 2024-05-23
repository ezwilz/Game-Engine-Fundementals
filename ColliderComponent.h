#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Vector2D.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	
	bool canOverlap = false;

	Vector2D center;

	TransformComponent* transform;
	
	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		GetCenter();
		collider.x = static_cast<int>(transform->transform.x);
		collider.y = static_cast<int>(transform->transform.y);
		collider.w = static_cast<int>(transform->width * transform->scale);
		collider.h = static_cast<int>(transform->height * transform->scale);
	}
	// end of third party

	void GetCenter()
	{
		center.x = collider.x + (collider.w / 2);
		center.y = collider.y + (collider.h / 2);
	}

	void CorrectOverlapY(const Entity& collidee)
	{
		float newY;

		newY = (collidee.getComponent<ColliderComponent>().collider.h - collider.h) + (collider.h);

		transform->transform.y = collidee.getComponent<ColliderComponent>().collider.y - collider.h;// -newY;
		//std::cout << newY << " & " << collidee.getComponent<ColliderComponent>().collider.y << std::endl;

	}
	void CorrectOverlapX(const Entity& collidee, int leftRight)
	{
		// leftright 1=left, 2=right
		float newX;
		if (leftRight == 1)
		{
			//newX = (collidee.getComponent<ColliderComponent>().collider.w + collider.w) + (collider.w);
			transform->transform.x = collidee.getComponent<ColliderComponent>().collider.x + collidee.getComponent<ColliderComponent>().collider.w +1;
			
		}
		if (leftRight == 2)
		{
			//newX = (collidee.getComponent<ColliderComponent>().collider.w - collider.w) + (collider.w);
			transform->transform.x = collidee.getComponent<ColliderComponent>().collider.x - collider.w -1;
		}

		// -newY;
		//std::cout << newX << " & " << collidee.getComponent<ColliderComponent>().collider.x << std::endl;

	}

};