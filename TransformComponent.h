#pragma once



#include "PhysicsComponent.h"
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D transform;
	Vector2D velocity;
	
	int height = 32;
	int width = 32;
	int scale = 1;

	bool gravityOn = false;


	TransformComponent(float x, float y, int w, int h, int sc) 
	{
		transform.x = x;
		transform.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	TransformComponent()
	{

	}
	
	void init()
	{

	}
	void update() override
	{

	
	}
};