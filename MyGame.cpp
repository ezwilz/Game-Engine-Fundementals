
//
//  MyGame.cpp
//  GameEngine
//
// all code resources are taken from https://github.com/AlmasB/xcube2d/tree/master
//
#include "ECS.h"
#include "Components.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "VisualsComponent.h"
#include "WorldPhysicsComponent.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "Vector2D.h"
#include "MyGame.h"

#include "RigidBodyComponent.h"

bool swap;


// declare manager
Manager manager;

//create player object
auto& playerSquare(manager.addEntity());

//walls, floor, ceiling
auto& boxEntity1(manager.addEntity());
auto& boxEntity2(manager.addEntity());
auto& boxEntity3(manager.addEntity());
auto& boxEntity4(manager.addEntity());

//rigid body tests
auto& rigidBodyTest(manager.addEntity());
auto& rigidBodyTest2(manager.addEntity());

//platform centre and the two coloured backgrounds
auto& platform(manager.addEntity());
auto& leftColour(manager.addEntity());
auto& rightColour(manager.addEntity());

MyGame::MyGame() : AbstractGame(), numKeys(5),
box2{ 0, 0, 60, 2000 }, score(0), lives(3), gameWon(false), phy({ 0,0 },
	10, 100), phyobj2({ 0,400 }, 2000, 10)
{
	swap = false;
	gfx->setVerticalSync(true);
	//
	customInstance->otherfunction();
	//
	physics->setGravity(2, 2);


	// Player components
	playerSquare.addComponent<TransformComponent>(325.0f,100.f,32,32,1);
	playerSquare.addComponent<VisualsComponent>();
	playerSquare.addComponent<ColliderComponent>("player");
	playerSquare.addComponent<PhysicsComponent>(1.1f, 10.0f, 0.0f, 0.0f);
	playerSquare.addComponent<WorldPhysics>();

	// Center platform Components
	platform.addComponent<TransformComponent>(320.0f, 200.0f, 160, 400, 1);
	platform.addComponent<VisualsComponent>();
	platform.addComponent<ColliderComponent>("platform");

	//Left colour components
	leftColour.addComponent<TransformComponent>(0.0f, 300.0f, 400, 300, 1);
	leftColour.addComponent<VisualsComponent>();

	//Right colour components
	rightColour.addComponent<TransformComponent>(400.0f, 300.0f, 400, 300, 1);
	rightColour.addComponent<VisualsComponent>();
	
	//Rigid Body 1 components
	rigidBodyTest.addComponent<TransformComponent>(60.0f, 490.0f, 32, 32, 1);
	rigidBodyTest.addComponent<VisualsComponent>();
	rigidBodyTest.addComponent<ColliderComponent>("rigidBodyTest");
	rigidBodyTest.addComponent<RigidBodyComponent>();
	rigidBodyTest.addComponent<PhysicsComponent>(6.0f,1.0f,50.0f,50.0f);
	rigidBodyTest.addComponent<WorldPhysics>();

	//Rb2 Components
	rigidBodyTest2.addComponent<TransformComponent>(384.0f, 100.0f, 32, 32, 1);
	rigidBodyTest2.addComponent<VisualsComponent>();
	rigidBodyTest2.addComponent<ColliderComponent>("rigidBodyTest2");
	rigidBodyTest.addComponent<RigidBodyComponent>();
	rigidBodyTest2.addComponent<PhysicsComponent>(6.0f, 1.0f, 50.0f, 50.f);
	rigidBodyTest2.addComponent<WorldPhysics>();

	//ground
	boxEntity1.addComponent<TransformComponent>(0.0f, 560.0f, 800, 40, 1);
	boxEntity1.addComponent<VisualsComponent>();
	boxEntity1.addComponent<ColliderComponent>("ground");
	//ceiling
	boxEntity2.addComponent<TransformComponent>(0.0f, 0.0f, 800, 40, 1);
	boxEntity2.addComponent<VisualsComponent>();
	boxEntity2.addComponent<ColliderComponent>("ceiling");
	
	
	//right wall
	boxEntity3.addComponent<TransformComponent>(760.0f, 0.0f, 40, 600, 1);
	boxEntity3.addComponent<VisualsComponent>();
	boxEntity3.addComponent<ColliderComponent>("rightWall");
	//left wall
	boxEntity4.addComponent<TransformComponent>(1.0f, 0.0f, 40, 600, 1);
	boxEntity4.addComponent<VisualsComponent>();
	boxEntity4.addComponent<ColliderComponent>("leftWall");
	
}
MyGame::~MyGame()
{
}
void MyGame::handleKeyEvents()
{
	if (eventSystem->isPressed(Key::W))
	{
		playerSquare.getComponent<TransformComponent>().velocity.y = -1;
	}
	if (eventSystem->isPressed(Key::D))
	{
		
		playerSquare.getComponent<TransformComponent>().velocity.x = 1;
	}
	if (eventSystem->isPressed(Key::A))
	{
		
		playerSquare.getComponent<TransformComponent>().velocity.x = -1;
	}
	/*if (eventSystem->isPressed(Key::S))
	{
		
		newPlayer.getComponent<TransformComponent>().velocity.y = 1;

	}*/
}
void MyGame::update() {
	//update all components
	manager.update();


	if (rigidBodyTest.getComponent<TransformComponent>().transform.x > 490 )
	{
		if (rigidBodyTest.getComponent<TransformComponent>().transform.y < 490 && rigidBodyTest.getComponent<TransformComponent>().transform.y > 470)
		{
			std::cout << "Made by EW." << std::endl;
		}
		
	}
	if (rigidBodyTest2.getComponent<TransformComponent>().transform.x < 310)
	{
		if (rigidBodyTest2.getComponent<TransformComponent>().transform.y < 490 && rigidBodyTest2.getComponent<TransformComponent>().transform.y > 470)
		{
			std::cout << "Made for ci517." << std::endl;
		}
		
	}

	if (playerSquare.getComponent<TransformComponent>().transform.x < 0)
	{
		playerSquare.getComponent<TransformComponent>().transform.x = 800;
	}
	if (playerSquare.getComponent<TransformComponent>().transform.x > 800)
	{
		playerSquare.getComponent<TransformComponent>().transform.x = 0;
	}

	//std::cout << rigidBodyTest.getComponent<TransformComponent>().velocity.y << " & " << rigidBodyTest.getComponent<TransformComponent>().transform.y << " & " << rigidBodyTest.getComponent<VisualsComponent>().GetRectY() << std::endl;

	if (rigidBodyTest.getComponent<TransformComponent>().transform.x > 800 || rigidBodyTest.getComponent<TransformComponent>().transform.x < 0)
	{
		rigidBodyTest.getComponent<TransformComponent>().transform.x = 400;
		rigidBodyTest.getComponent<TransformComponent>().transform.y = 60;
	}
	if (rigidBodyTest.getComponent<TransformComponent>().transform.y > 600 || rigidBodyTest.getComponent<TransformComponent>().transform.y < 0)
	{
		rigidBodyTest.getComponent<TransformComponent>().transform.x = 400;
		rigidBodyTest.getComponent<TransformComponent>().transform.y = 400;
	}


	//newPlayer.getComponent<TransformComponent>().ApplyGravityToEntity();
	//rigidBodyTest.getComponent<TransformComponent>().ApplyGravityToEntity();
	//----------------------------------------------------------------
	//player and ground collision
	if (Collision::AABB(playerSquare.getComponent<ColliderComponent>().collider, boxEntity1.getComponent<ColliderComponent>().collider))
	{
		playerSquare.getComponent<TransformComponent>().velocity.y = 0;
		if (playerSquare.getComponent<ColliderComponent>().collider.y != boxEntity1.getComponent<ColliderComponent>().collider.y - playerSquare.getComponent<ColliderComponent>().collider.h)
		{
			playerSquare.getComponent<ColliderComponent>().CorrectOverlapY(boxEntity1);
		}
	}
	//----------------------------------------
	//rigid body and ground object collision detection.
	if (Collision::AABB(boxEntity1.getComponent<ColliderComponent>().collider, rigidBodyTest.getComponent<ColliderComponent>().collider))
	{
		if (swap == false && rigidBodyTest2.getComponent<TransformComponent>().transform.y > 200) // it is rb1 turn on false
		{
			rigidBodyTest.getComponent<TransformComponent>().transform.x = 400 - 16;
			rigidBodyTest.getComponent<TransformComponent>().transform.y = 100;
			swap = true;
		}
	

		if (abs(rigidBodyTest.getComponent<TransformComponent>().velocity.y) < 0.5f)
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.y = 0;
		}
		else
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.y = rigidBodyTest.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest.getComponent<TransformComponent>().velocity.y, 2);
		}
		
		
		if (rigidBodyTest.getComponent<ColliderComponent>().collider.y != boxEntity1.getComponent<ColliderComponent>().collider.y - rigidBodyTest.getComponent<ColliderComponent>().collider.h)
		{
			
			rigidBodyTest.getComponent<ColliderComponent>().CorrectOverlapY(boxEntity1);
		}
	}

	//rigid body2 and ground object collision detection.
	if (Collision::AABB(boxEntity1.getComponent<ColliderComponent>().collider, rigidBodyTest2.getComponent<ColliderComponent>().collider))
	{
		if (swap == true && rigidBodyTest.getComponent<TransformComponent>().transform.y > 200) // it is rb1 turn on false
		{
			rigidBodyTest2.getComponent<TransformComponent>().transform.x = 400 - 16;
			rigidBodyTest2.getComponent<TransformComponent>().transform.y = 100;
			swap = false;
		}
		
		if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.y) < 1)
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.y = 0;
		}
		else
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.y = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.y, 2);
		}


		if (rigidBodyTest2.getComponent<ColliderComponent>().collider.y != boxEntity1.getComponent<ColliderComponent>().collider.y - rigidBodyTest2.getComponent<ColliderComponent>().collider.h)
		{

			rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapY(boxEntity1);
		}
	}


	// ----------------------------------------
	// player and rigidbody test collision
	if (Collision::AABB(playerSquare.getComponent<ColliderComponent>().collider, rigidBodyTest.getComponent<ColliderComponent>().collider))
	{
		rigidBodyTest.getComponent<RigidBodyComponent>().TransferVelocity(playerSquare, rigidBodyTest);
	}
	// player and rigidbody test2 collision
	if (Collision::AABB(playerSquare.getComponent<ColliderComponent>().collider, rigidBodyTest2.getComponent<ColliderComponent>().collider))
	{
		rigidBodyTest2.getComponent<RigidBodyComponent>().TransferVelocity(playerSquare, rigidBodyTest2);
	}




	//-------------------------------------------------------------------------
	// right wall collision and rigid body 1
	if (Collision::AABB(boxEntity3.getComponent<ColliderComponent>().collider, rigidBodyTest.getComponent<ColliderComponent>().collider))
	{	
		if (abs(rigidBodyTest.getComponent<TransformComponent>().velocity.x) < 1)
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.x = 0;
		}
		else
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.x = 
				rigidBodyTest.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest.getComponent<TransformComponent>().velocity.x, 1);
		}
		if (rigidBodyTest.getComponent<ColliderComponent>().collider.x != boxEntity3.getComponent<ColliderComponent>().collider.x
			- rigidBodyTest.getComponent<ColliderComponent>().collider.w)
		{
			rigidBodyTest.getComponent<ColliderComponent>().CorrectOverlapX(boxEntity3, 2);
		}
		
	}
	//-----
	// right wall collision and rigid body 2
	if (Collision::AABB(boxEntity3.getComponent<ColliderComponent>().collider, rigidBodyTest2.getComponent<ColliderComponent>().collider))
	{
		if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.x) < 1)
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.x = 0;
		}
		else
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.x = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.x, 1);
		}

		if (rigidBodyTest2.getComponent<ColliderComponent>().collider.x != boxEntity3.getComponent<ColliderComponent>().collider.x - rigidBodyTest2.getComponent<ColliderComponent>().collider.w)
		{
			rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapX(boxEntity3, 2);
		}
	}
	//-------------------------------------------------------------------------
	// left wall collision
	// Rigid body 1 and left wall collision
	if (Collision::AABB(boxEntity4.getComponent<ColliderComponent>().collider, rigidBodyTest.getComponent<ColliderComponent>().collider))
	{
		if (abs(rigidBodyTest.getComponent<TransformComponent>().velocity.x) < 1)
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.x = 0;
		}
		else
		{
			rigidBodyTest.getComponent<TransformComponent>().velocity.x = rigidBodyTest.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest.getComponent<TransformComponent>().velocity.x, 2);
		}
		if (rigidBodyTest.getComponent<ColliderComponent>().collider.x != boxEntity4.getComponent<ColliderComponent>().collider.x + rigidBodyTest.getComponent<ColliderComponent>().collider.w)
		{
			rigidBodyTest.getComponent<ColliderComponent>().CorrectOverlapX(boxEntity4, 1);
		}

	}
	//-----
	//rigid body 2 and left wall collision
	if (Collision::AABB(boxEntity4.getComponent<ColliderComponent>().collider, rigidBodyTest2.getComponent<ColliderComponent>().collider))
	{
		if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.x) < 1)
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.x = 0;
		}
		else
		{
			rigidBodyTest2.getComponent<TransformComponent>().velocity.x = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.x, 1);
		}
		if (rigidBodyTest2.getComponent<ColliderComponent>().collider.x != boxEntity4.getComponent<ColliderComponent>().collider.x + rigidBodyTest2.getComponent<ColliderComponent>().collider.w)
		{
			rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapX(boxEntity4, 1);
		}
	}
	//--------

	// Game Collision 

	//player and ground collision
	if (Collision::AABB(playerSquare.getComponent<ColliderComponent>().collider, platform.getComponent<ColliderComponent>().collider))
	{
		playerSquare.getComponent<TransformComponent>().velocity.y = 0;
		if (playerSquare.getComponent<ColliderComponent>().collider.y != platform.getComponent<ColliderComponent>().collider.y - playerSquare.getComponent<ColliderComponent>().collider.h)
		{
			playerSquare.getComponent<ColliderComponent>().CorrectOverlapY(platform);
		}
	}

	//rigid body2 and PLATFORM object collision detection.
	if (Collision::AABB(platform.getComponent<ColliderComponent>().collider, rigidBodyTest2.getComponent<ColliderComponent>().collider))
	{
		//if the entity is coming from above land on the top
		if (rigidBodyTest2.getComponent<TransformComponent>().transform.y < (platform.getComponent<TransformComponent>().transform.y))
		{
			if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.y) < 1)
			{
				rigidBodyTest2.getComponent<TransformComponent>().velocity.y = 0;
			}
			else
			{
				rigidBodyTest2.getComponent<TransformComponent>().velocity.y = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.y, 2);
			}

		
			if (rigidBodyTest2.getComponent<ColliderComponent>().collider.y != platform.getComponent<ColliderComponent>().collider.y - rigidBodyTest2.getComponent<ColliderComponent>().collider.h)
			{

				rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapY(platform);
			}
		}
		else {
			// if the entity is colliding from the sides....

			// ( right side of the platform, similar to hitting the levels left wall)
			if (rigidBodyTest2.getComponent<TransformComponent>().velocity.x < 0)
			{
				if (rigidBodyTest2.getComponent<TransformComponent>().transform.x > 400)
				{
					//std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
					if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.x) < 1)
					{
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = 0;
						//std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
					}
					else
					{
						//std::cout << "hit the right wall" << std::endl;
						std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.x, 1);
						std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
					}
					if (rigidBodyTest2.getComponent<ColliderComponent>().collider.x != platform.getComponent<ColliderComponent>().collider.x + platform.getComponent<ColliderComponent>().collider.w)
					{
						//std::cout << "reset" << std::endl;
						std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
						rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapX(platform, 1);
					}
				}
				
			}
			//( hitting the left side of the platform)
			if (rigidBodyTest2.getComponent<TransformComponent>().velocity.x > 0)
			{
				if (rigidBodyTest2.getComponent<TransformComponent>().transform.x < 400)
				{
					if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.x) < 0.5f)
					{
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = 0;
					}
					else
					{
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.x, 1);
					}

					if (rigidBodyTest2.getComponent<ColliderComponent>().collider.x != platform.getComponent<ColliderComponent>().collider.x - rigidBodyTest2.getComponent<ColliderComponent>().collider.w)
					{
						rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapX(platform, 2);
					}
				}
				
			}
			
		}
		
	}

	//rigid body and platform object collision detection.
	if (Collision::AABB(platform.getComponent<ColliderComponent>().collider, rigidBodyTest.getComponent<ColliderComponent>().collider))
	{

		//if the entity is coming from above land on the top
		if (rigidBodyTest.getComponent<TransformComponent>().transform.y < (platform.getComponent<TransformComponent>().transform.y))
		{
			if (abs(rigidBodyTest.getComponent<TransformComponent>().velocity.y) < 1)
			{
				rigidBodyTest.getComponent<TransformComponent>().velocity.y = 0;
			}
			else
			{
				rigidBodyTest.getComponent<TransformComponent>().velocity.y = rigidBodyTest.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest.getComponent<TransformComponent>().velocity.y, 2);
			}


			if (rigidBodyTest.getComponent<ColliderComponent>().collider.y != platform.getComponent<ColliderComponent>().collider.y - rigidBodyTest.getComponent<ColliderComponent>().collider.h)
			{

				rigidBodyTest.getComponent<ColliderComponent>().CorrectOverlapY(platform);
			}
		}
		else {
			// if the entity is colliding from the sides....

			// ( right side of the platform, similar to hitting the levels left wall)
			if (rigidBodyTest.getComponent<TransformComponent>().velocity.x < 0)
			{
				if (rigidBodyTest.getComponent<TransformComponent>().transform.x > 400)
				{
					//std::cout << std::endl << rigidBodyTest.getComponent<TransformComponent>().velocity.x << std::endl;
					if (abs(rigidBodyTest.getComponent<TransformComponent>().velocity.x) < 1)
					{
						rigidBodyTest.getComponent<TransformComponent>().velocity.x = 0;
						//std::cout << std::endl << rigidBodyTest.getComponent<TransformComponent>().velocity.x << std::endl;
					}
					else
					{
						//std::cout << "hit the right wall" << std::endl;
						//std::cout << std::endl << rigidBodyTest.getComponent<TransformComponent>().velocity.x << std::endl;
						rigidBodyTest.getComponent<TransformComponent>().velocity.x = rigidBodyTest.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest.getComponent<TransformComponent>().velocity.x, 1);
						//std::cout << std::endl << rigidBodyTest2.getComponent<TransformComponent>().velocity.x << std::endl;
					}
					if (rigidBodyTest.getComponent<ColliderComponent>().collider.x != platform.getComponent<ColliderComponent>().collider.x + platform.getComponent<ColliderComponent>().collider.w)
					{
						//std::cout << "reset" << std::endl;
						//std::cout << std::endl << rigidBodyTest.getComponent<TransformComponent>().velocity.x << std::endl;
						rigidBodyTest.getComponent<ColliderComponent>().CorrectOverlapX(platform, 1);
					}
				}

			}
			//( hitting the left side of the platform)
			if (rigidBodyTest2.getComponent<TransformComponent>().velocity.x > 0)
			{
				if (rigidBodyTest2.getComponent<TransformComponent>().transform.x < 400)
				{
					if (abs(rigidBodyTest2.getComponent<TransformComponent>().velocity.x) < 0.5f)
					{
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = 0;
					}
					else
					{
						rigidBodyTest2.getComponent<TransformComponent>().velocity.x = rigidBodyTest2.getComponent<PhysicsComponent>().CalculateBounce(rigidBodyTest2.getComponent<TransformComponent>().velocity.x, 1);
					}

					if (rigidBodyTest2.getComponent<ColliderComponent>().collider.x != platform.getComponent<ColliderComponent>().collider.x - rigidBodyTest2.getComponent<ColliderComponent>().collider.w)
					{
						rigidBodyTest2.getComponent<ColliderComponent>().CorrectOverlapX(platform, 2);
					}
				}

			}

		}

	}
}
void MyGame::render()
{
	
	//// Game Object rendering
	//
	//gfx->setDrawColor(SDL_COLOR_GREEN);
	//gfx->fillRect(leftColour.getComponent<TransformComponent>().transform.x,
	//	leftColour.getComponent<TransformComponent>().transform.y,
	//	leftColour.getComponent<TransformComponent>().width,
	//	leftColour.getComponent<TransformComponent>().height);
	//
	//gfx->setDrawColor(SDL_COLOR_PINK);
	//gfx->fillRect(rightColour.getComponent<TransformComponent>().transform.x,
	//	rightColour.getComponent<TransformComponent>().transform.y,
	//	rightColour.getComponent<TransformComponent>().width,
	//	rightColour.getComponent<TransformComponent>().height);
	
	

	//------------------------------------------
	//rigid body rendering
	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->fillRect(rigidBodyTest.getComponent<TransformComponent>().transform.x,
		rigidBodyTest.getComponent<TransformComponent>().transform.y,
		rigidBodyTest.getComponent<TransformComponent>().width,
		rigidBodyTest.getComponent<TransformComponent>().height);

	//rigid body 2 rendering
	gfx->setDrawColor(SDL_COLOR_PINK);
	gfx->fillRect(rigidBodyTest2.getComponent<TransformComponent>().transform.x,
		rigidBodyTest2.getComponent<TransformComponent>().transform.y,
		rigidBodyTest2.getComponent<TransformComponent>().width,
		rigidBodyTest2.getComponent<TransformComponent>().height);
	//-------------------------------------------
	// ground
	gfx->setDrawColor(SDL_COLOR_RED);
		gfx->fillRect(boxEntity1.getComponent<TransformComponent>().transform.x,
			boxEntity1.getComponent<TransformComponent>().transform.y,
			boxEntity1.getComponent<TransformComponent>().width,
			boxEntity1.getComponent<TransformComponent>().height);
	//----------------------------------
		//ceiling
		gfx->setDrawColor(SDL_COLOR_RED);
		gfx->fillRect(boxEntity2.getComponent<TransformComponent>().transform.x,
			boxEntity2.getComponent<TransformComponent>().transform.y,
			boxEntity2.getComponent<TransformComponent>().width,
			boxEntity2.getComponent<TransformComponent>().height);
	//--------------------------------
	//right wall
		gfx->setDrawColor(SDL_COLOR_RED);
		gfx->fillRect(boxEntity3.getComponent<TransformComponent>().transform.x,
			boxEntity3.getComponent<TransformComponent>().transform.y,
			boxEntity3.getComponent<TransformComponent>().width,
			boxEntity3.getComponent<TransformComponent>().height);
	//---------------------------------
	//left wall
		gfx->setDrawColor(SDL_COLOR_RED);
		gfx->fillRect(boxEntity4.getComponent<TransformComponent>().transform.x,
			boxEntity4.getComponent<TransformComponent>().transform.y,
			boxEntity4.getComponent<TransformComponent>().width,
			boxEntity4.getComponent<TransformComponent>().height);
		//---------------------------------
		//-----------------------------------------
	//player rendering
		gfx->setDrawColor(SDL_COLOR_YELLOW);
		gfx->fillRect(playerSquare.getComponent<TransformComponent>().transform.x,
			playerSquare.getComponent<TransformComponent>().transform.y,
			playerSquare.getComponent<TransformComponent>().width,
			playerSquare.getComponent<TransformComponent>().height);

		//platform
		gfx->setDrawColor(SDL_COLOR_RED);
		gfx->fillRect(platform.getComponent<TransformComponent>().transform.x,
			platform.getComponent<TransformComponent>().transform.y,
			platform.getComponent<TransformComponent>().width,
			platform.getComponent<TransformComponent>().height);



}
void MyGame::renderUI() {
}

