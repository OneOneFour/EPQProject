#pragma once
#include "PhysicsObject.hpp"
#include <SFML\Graphics.hpp>
class Ship :public PhysicsObject{
public:
	Ship(sf::Vector2f position,PhysicsWorld& world,std::string name);
	~Ship();
	void changeHealth(float deltaHealth);
	void setHealth(float health);
	float getHealth();
	void update(float deltaTime);
protected:
	float reloadTimer = 0.5f;
	float health;
	float manuvarability;
	float angularLevel;
	float thrustLevel;
	float maxThrust;
};

