#pragma once
#include "GameObject.hpp"
#include "Definitions.hpp"
#include "Collider.hpp"
class Collider;
class PhysicsWorld;
class PhysicsObject : public GameObject{
public:
	PhysicsObject(sf::Vector2f position,PhysicsWorld& world,std::string prefId);
	PhysicsObject(sf::Vector2f position, PhysicsWorld& world);
	PhysicsObject(sf::Vector2f position, PhysicsWorld& world,sf::Vector2f vertices[],int size);
	~PhysicsObject();
	virtual void update(float deltaTime); //Called before physics system has run
	void draw(float deltaTime);//Called after physics system has run
	//PhysicsObject* checkForCollisions(); //checks for collision against all phys objects, returns nullptr if none found
	// PhysicsObject* rayCast(sf::Vector2f origin,sf::Vector2f direction,float maxDistance = FLT_MAX);
	void setVelocity(sf::Vector2f vel);
	virtual void onCollision(sf::Vector2f colPoint,PhysicsObject* collided);
	void setName(const std::string& name);
	bool isKinematic(); //checks if object is an active physics object.
	float getMass();
	void setMass(float mass);
	void applyForce(sf::Vector2f forceToApply, sf::Vector2f location);
	std::string getName();
	sf::Sprite getSprite();
	float getAngularVelocity();
	virtual void setSprite(std::string textureID);
	sf::Vector2f getVelocity();
	void setAcceleration(sf::Vector2f accel);
	sf::Vector2f getAcceleration();
	Collider* getCollider();//returns pointer to collider object.
protected:
	bool kinematic;
	sf::Vector2f frameNetForce;
	float netTorque;
	float mass;
	float momentOfInertia;
	PhysicsWorld& world;
	std::string name;
	std::string textureID;
	Collider col;
	//sf::Vector2f centerOfMass;
	float angularAccel;
	float angularVeloc;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Sprite sprite;
};