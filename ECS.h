#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


//define classes
class Component;
class Entity;

//Each component needs an ID e.g. physics, position, size etc.
// std size t is 64 bit and largest number possible etc.
using ComponentID = std::size_t;


// inline function put into place wherever we use it.
//increases as many times as it is called. 
inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

//Keeps the components IDs the same, so when a new one is added it gets the next ID. 
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentID();
	return typeID;
}

//sets the max amount of components an entity can have on it at one time. 
constexpr std::size_t maxComponents = 32;

// If we want to find out if a entity has a component, bitset can be used.
using CompontBitSet = std::bitset<maxComponents>;
// store all the components in an array
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;
	virtual void init() {}
	virtual void draw() {}
	virtual void update() {}

	virtual ~Component(){}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	CompontBitSet componentBitSet;
public:
	void update()
	{
		for (auto& c : components) c->update();
		//for (auto& c : components) c->init();
	}
	void draw(){ for (auto& c : components) c->draw(); }
	bool isActive() { return active;  }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
private:
	std::vector < std::unique_ptr<Entity>> entities;
public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}
	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}
	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uptr{ e };
		entities.emplace_back(std::move(uptr));
		return *e;
	}
};