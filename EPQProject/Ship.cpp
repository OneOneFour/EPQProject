#include "Ship.hpp"
#include "Helpies.hpp"
Ship::Ship(sf::Vector2f position, Screen& screen,std::string name) :PhysicsObject(position, screen,name) {
	this->health = this->screen.game->bank.getDefs(name).shipData.health;
	this->maxThrust = this->screen.game->bank.getDefs(name).shipData.maxThrust;
	this->manuvarability = this->screen.game->bank.getDefs(name).shipData.manuv;
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
