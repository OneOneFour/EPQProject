#include "PhysicsWorld.hpp"
#include "Helpies.hpp"

PhysicsWorld::PhysicsWorld(){
}
void PhysicsWorld::init(Screen& screen) {
	this->bankPtr = &screen.game->bank;
}
PhysicsObject * PhysicsWorld::createPhysObject(PhysicsObject * obj)
{
	objects.push_back(obj);
	return obj;
}

PhysicsObject * PhysicsWorld::getPhysicsObject(int index)
{
	return objects[index];
}
int PhysicsWorld::getObjCount()
{
	return objects.size();
}
void PhysicsWorld::step(float deltaTime) {
	//preliminary phys check
	std::map<PhysicsObject*, PhysicsObject*> collision;
	std::map<PhysicsObject*, sf::Vector2f> colPoints;
	for (int i = 0; i < objects.size();i++) {
		objects[i]->update(deltaTime);
		for (int j = 0; j < objects.size();j++) {
			if (objects[i] == objects[j]) continue;
			if ((objects[i]->getCollider()->colCheck(*objects[j]->getCollider(), objects[i]->getPos(),objects[j]->getPos())
				&& objects[i]->getCollider()->colCheck(*objects[j]->getCollider(), objects[i]->getPos() + objects[i]->getVelocity() * deltaTime + 0.5f * objects[i]->getAcceleration() * std::pow(deltaTime,2),
					objects[j]->getPos() + ( objects[j]->getVelocity()*deltaTime + 0.5f*objects[j]->getAcceleration()*std::powf(deltaTime,2))))){
				if (collision.find(objects[j]) != collision.end()) {
					if (collision.at(objects[j]) == objects[i]) {
						continue;
					}
				}
				collision[objects[i]] = objects[j];
				colPoints[objects[i]] = objects[i]->getCollider()->getLastCol();
			}
		}
	}
	for (auto i = collision.begin(); i != collision.end(); i++) {
		PhysicsObject* a = i->first;
		PhysicsObject* b = i->second;
		//check if friendly fire
		sf::Vector2f aColPoint = colPoints[a] - a->getPos();
		sf::Vector2f bColPoint = colPoints[a] - b->getPos();
		//Custom Collision Logic
		a->onCollision(aColPoint,b);
		b->onCollision(bColPoint,a);
		//check if collision is still valid 
		if (a == nullptr || b == nullptr) {
			continue;
		}
		if (!a->isKinematic()) {
			b->setVelocity(sf::Vector2f(0, 0));
		}
		else if (!b->isKinematic()) {
			a->setVelocity(sf::Vector2f(0, 0));
		}
		else {
			sf::Vector2f aVel = a->getVelocity();//Velocity of point at collision (LOGIC JUMP)? 
			sf::Vector2f bVel = b->getVelocity();
			sf::Vector2f momentum =aVel*a->getMass() + bVel * b->getMass();
			sf::Vector2f presC = COR * (aVel - bVel);
			sf::Vector2f theForce = (((momentum - b->getMass()*presC) / (a->getMass() + b->getMass()) - aVel)* a->getMass())/deltaTime;
			a->applyForce(theForce,aColPoint);
			b->applyForce(-theForce,bColPoint);
			//Angular Momentum check?


			//TODO Check if still colliding after collision...(IMPORTANT- causes large fps drop)
			sf::Vector2f aNextFramePos = sf::Vector2f(a->getPos() + a->getVelocity()*deltaTime + 0.5f*(theForce / a->getMass())*std::powf(deltaTime, 2));
			sf::Vector2f bNextFramePos = sf::Vector2f(b->getPos() + b->getVelocity()*deltaTime + 0.5f*(theForce/b->getMass()) * std::powf(deltaTime,2));
			while (a->getCollider()->colCheck(*b->getCollider(), aNextFramePos, bNextFramePos)) {
				//Get line of least distance
				sf::Vector2f lDist = bNextFramePos - aNextFramePos;
				aNextFramePos -= normalizeVector(lDist); 
				bNextFramePos += normalizeVector(lDist);
			}
			a->setPos(aNextFramePos);
			b->setPos(bNextFramePos);
		}
	
	}
	
	for each(PhysicsObject* a in objects){
		a->draw(deltaTime);
	}
	while (!deleteObj.empty()) {
		auto top = std::find(objects.begin(),objects.end(),deleteObj.top());
		if (top != objects.end()) {
			delete objects[top - objects.begin()];
			objects.erase(top);
		}
		deleteObj.pop();
	}
}
void PhysicsWorld::destroyObject(int id){
	delete objects[id];
	objects.erase(objects.begin() + id);
}
void PhysicsWorld::destroyObject(PhysicsObject * obj){
	deleteObj.push(obj);
}
PhysicsWorld::~PhysicsWorld(){
	while (!objects.empty())
	{
		delete objects.back();
		objects.pop_back();
	}
}
