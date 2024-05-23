#pragma once


#include "ECS.h"
#include "PhysicsEngine.h"
#include "Components.h"
#include "SDL.h"




class VisualsComponent : public Component
{
private:
		TransformComponent *transform;
		SDL_Rect srcRect, destRect;
public:
	VisualsComponent() = default;
	
	/*VisualsComponent(const char* path)
	{

	}*/
	~VisualsComponent()
	{
		
	}
	int GetRectX()
	{
		return destRect.x;
	}
	int GetRectY()
	{
		return destRect.y;
	}
	int GetRectW()
	{
		return destRect.w;
	}
	int GetRectH()
	{
		return destRect.h;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = transform->transform.x;
		srcRect.y = transform->transform.y;
		srcRect.w = transform->width * transform->scale;
		srcRect.h = transform->height * transform->scale;

		destRect.w = destRect.h = 64;

	}

	void update() override
	{
		destRect.x = (int)transform->transform.x;
		destRect.y = (int)transform->transform.y;
		destRect.w = (int)transform->width * transform->scale;
		destRect.h = (int)transform->width * transform->scale;
	}
};