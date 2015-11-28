#pragma once
#include "PhysicsObject.hpp"
#include <SFML\Graphics.hpp>
class Ship :public PhysicsObject{
public:
	Ship(sf::Vector2f position,Screen& screen,std::string name);
	~Ship();
	void changeHealth(float deltaHealth);
	void setHealth(float health);
	float getHealth();
	void update(float deltaTime);
protected:
	float health;
	float manuvarability;
	float thrustLevel;
	float maxThrust;
};

