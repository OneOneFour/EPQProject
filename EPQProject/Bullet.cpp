#include "Bullet.hpp"
#include "PhysicsWorld.hpp"
Bullet::Bullet(sf::Vector2f position, PhysicsWorld& world, std::string prefId,Ship* owner):PhysicsObject(position,world,prefId) {
	this->owner = owner;
	this->damage = world.bankPtr->getDefs(prefId).bulletData.damage;
}

Bullet::~Bullet(){
}

void Bullet::update(float deltaTime){
	if (existanceTimer > life) {
		world.destroyObject(this);
	}
	existanceTimer += deltaTime;
	
	PhysicsObject::update(deltaTime);
}

Ship* Bullet::getOwner(){
	return this->owner;
}

void Bullet::onCollision(sf::Vector2f colPoint,PhysicsObject* collided){
	printf("Hello");
}
