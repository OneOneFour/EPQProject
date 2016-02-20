#include "Ship.hpp"
#include "Helpies.hpp"
#include "Bullet.hpp"
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
		angularLevel -= (angularLevel <= -1.0f) ? 0.f : 0.05f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angularLevel += (angularLevel >= 1.0f) ? 0.f : 0.05f;
	}
	else {
		angularLevel = 0.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && reloadTimer < 0) {
		Bullet* bullet = dynamic_cast<Bullet*>(world.createPhysObject(new Bullet(this->position + sf::Vector2f(25.0f * sin(degreeToRad(rotation)), -25.0f * cos(degreeToRad(rotation))), world, "Bullet", this)));
		bullet->setVelocity(this->velocity + sf::Vector2f(150*sin(degreeToRad(rotation)),-150*cos(degreeToRad(rotation))));
		bullet->setRotation(rotation);
		reloadTimer = 0.5f;
	}
	float targetVelocity = maxThrust*thrustLevel;
	this->angularVeloc = manuvarability*angularLevel;
	this->velocity = sf::Vector2f(incrementTowards(velocity.x, targetVelocity*sin(degreeToRad(rotation)), maxThrust/mass, deltaTime), incrementTowards(velocity.y, targetVelocity*-cos(degreeToRad(rotation)), maxThrust / mass, deltaTime));
	reloadTimer -= deltaTime;
	PhysicsObject::update(deltaTime);//IMPORNT
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
