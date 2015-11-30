#pragma once
#include "GameObject.hpp"
#include "Definitions.hpp"
#include "Collider.hpp"
class Collider;
class PhysicsWorld;
class PhysicsObject : public GameObject{
public:
	PhysicsObject(sf::Vector2f position,PhysicsWorld& world,std::string prefId);
	~PhysicsObject();
	virtual void update(float deltaTime); 
	//PhysicsObject* checkForCollisions(); //checks for collision against all phys objects, returns nullptr if none found
	// PhysicsObject* rayCast(sf::Vector2f origin,sf::Vector2f direction,float maxDistance = FLT_MAX);
	void setVelocity(sf::Vector2f vel);
	void setName(const std::string& name);
	std::string getName();
	sf::Sprite getSprite();
	virtual void setSprite(std::string textureID);
	sf::Vector2f getVelocity();
	void setAcceleration(sf::Vector2f accel);
	sf::Vector2f getAcceleration();
	PhysicsData data;
	Collider* getCollider();
protected:
	PhysicsWorld& world;
	std::string name;
	std::string textureID;
	Collider col;
	//sf::Vector2f centerOfMass;
	sf::Vector2f angularAccel;
	sf::Vector2f angularVeloc;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Sprite sprite;
};