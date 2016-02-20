#pragma once
#include "PhysicsObject.hpp"
#include "Ship.hpp"
class Bullet :public PhysicsObject{
public:
	Bullet(sf::Vector2f position,PhysicsWorld& world,std::string prefId,Ship* owner);
	~Bullet();
	void update(float deltaTime);
	Ship* getOwner();
	void onCollision(sf::Vector2f colPoint,PhysicsObject* collided);
private:
	float existanceTimer;
	float life= 15.0f;
	float damage;
	Ship* owner;
};
