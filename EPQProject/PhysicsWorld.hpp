#pragma once
#include <vector>
#include "PhysicsObject.hpp"
class PhysicsObject;
class PhysicsWorld{
public:
	const float COR = 0.85f;
	PhysicsWorld();
	void init(Screen& screen);
	PhysicsObject* createPhysObject(PhysicsObject* obj);
	PhysicsObject* getPhysicsObject(int id);
	int getObjCount();
	void step(float deltaTime);
	void destroyObject(int id);
	~PhysicsWorld();
	ResourceBank* bankPtr;
private:
	std::vector<PhysicsObject*> objects; //May change to std::map?
};

