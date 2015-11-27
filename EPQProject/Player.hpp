#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicsObject.hpp"
class Player:public PhysicsObject{
public:
	Player(sf::Vector2f position,float mass = 1.0f);
	~Player();
	void update(float deltaTime);
};

