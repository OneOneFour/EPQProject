#pragma once
#include "GameObject.hpp"
#include "LevelScreen.hpp"
#include "Definitions.hpp"
#include "Collider.hpp"
class Collider;
class PhysicsObject : public GameObject{
public:
	PhysicsObject(sf::Vector2f position,Screen& screen,std::string name);
	~PhysicsObject();
	virtual void update(float deltaTime); 
	//PhysicsObject* checkForCollisions(); //checks for collision against all phys objects, returns nullptr if none found
	// PhysicsObject* rayCast(sf::Vector2f origin,sf::Vector2f direction,float maxDistance = FLT_MAX);
	void setVelocity(sf::Vector2f vel);
	sf::Sprite getSprite();
	virtual void setSprite(std::string textureID);
	sf::Vector2f getVelocity();
	void setAcceleration(sf::Vector2f accel);
	sf::Vector2f getAcceleration();
	PhysicsData data;
	Collider* getCollider();
protected:
	std::string textureID;
	Collider col;
	//sf::Vector2f centerOfMass;
	sf::Vector2f angularAccel;
	sf::Vector2f angularVeloc;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Sprite sprite;
};