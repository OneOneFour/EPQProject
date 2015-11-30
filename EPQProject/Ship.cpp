#include "Ship.hpp"
#include "Helpies.hpp"
#include "PhysicsWorld.hpp"
Ship::Ship(sf::Vector2f position, PhysicsWorld& world,std::string name) :PhysicsObject(position, world,name) {
	this->health = world.bankPtr->getDefs(name).shipData.health;
	this->maxThrust = world.bankPtr->getDefs(name).shipData.maxThrust;
	this->manuvarability = world.bankPtr->getDefs(name).shipData.manuv;
	thrustLevel = 0.f;
}
void Ship::update(float deltaTime){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		thrustLevel += (thrustLevel >= 1.0f) ? 0.f : 0.05f;		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		thrustLevel -= (thrustLevel <= -1.0f) ? 0.f : 0.05f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		rotation -= manuvarability * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		rotation += manuvarability * deltaTime;
	}
	this->velocity = sf::Vector2f(thrustLevel*maxThrust * sin(degreeToRad(180 - rotation)), thrustLevel*maxThrust*cos(degreeToRad(180 - rotation)));
	PhysicsObject::update(deltaTime);//IMPORTANT
}
Ship::~Ship(){

}

void Ship::changeHealth(float deltaHealth){
	health += deltaHealth;
}

void Ship::setHealth(float health){
	this->health = health;
}

float Ship::getHealth(){
	return health;
}
