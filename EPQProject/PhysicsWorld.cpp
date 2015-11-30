#include "PhysicsWorld.hpp"

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
	for each(PhysicsObject* a in objects) {
		a->setVelocity(a->getVelocity() + a->getAcceleration()* deltaTime);
		for each(PhysicsObject* b in objects) {
			if (a == b) continue;
			if ((a->getCollider()->colCheck(*b->getCollider(), a->getPos(),b->getPos())
				&& a->getCollider()->colCheck(*b->getCollider(), a->getPos() + a->getVelocity() * deltaTime,b->getPos() + ( b->getVelocity()*deltaTime + 0.5f*b->getAcceleration()*std::powf(deltaTime,2))))){
				if (collision.find(b) != collision.end()) {
					if (collision.at(b) == a) {
						continue;
					}
				}
				collision[a] = b;
			}
		}
	}
	for (auto i = collision.begin(); i != collision.end(); i++) {
		PhysicsObject* a = i->first;
		PhysicsObject* b = i->second;

		if (!a->isKinematic()) {
			b->setVelocity(sf::Vector2f(0, 0));
		}
		else if (!b->isKinematic()) {
			a->setVelocity(sf::Vector2f(0, 0));
		}
		else {
			sf::Vector2f momentum = a->getVelocity()*a->data.mass + b->getVelocity() * b->data.mass;
			sf::Vector2f presC = COR * (a->getVelocity() - b->getVelocity());
			a->setVelocity((momentum - b->data.mass*presC) / (a->data.mass + b->data.mass));
			b->setVelocity(a->getVelocity() + presC);
		}

	}
	for each(PhysicsObject* a in objects){
		a->update(deltaTime);
	}
}
void PhysicsWorld::destroyObject(int id){
	delete objects[id];
	objects.erase(objects.begin() + id);
}
PhysicsWorld::~PhysicsWorld(){
	while (!objects.empty())
	{
		delete objects.back();
		objects.pop_back();
	}
}
