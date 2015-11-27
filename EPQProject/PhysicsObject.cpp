#include "PhysicsObject.hpp"


PhysicsObject::PhysicsObject(sf::Vector2f position,Screen& screen,std::string name) : GameObject(position,screen){
	this->data = screen.game->bank.getDefs(name).physicsData;
	this->setSprite(data.textureID);
}
PhysicsObject::~PhysicsObject(){

}
void PhysicsObject::update(float deltaTime){
	if (!active) return;
	velocity += acceleration*deltaTime;
	position += velocity * deltaTime;
	this->sprite.setPosition(position);
	this->sprite.setRotation(rotation);
}
void PhysicsObject::setVelocity(sf::Vector2f vel){
	this->velocity = vel;
}
sf::Sprite PhysicsObject::getSprite(){
	return sprite;
}
void PhysicsObject::setSprite(std::string textureID){
	this->sprite.setTexture(*screen.game->bank.getTexture(textureID));
	this->sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y / 2);
}
sf::Vector2f PhysicsObject::getVelocity()
{
	return velocity;
}
void PhysicsObject::setAcceleration(sf::Vector2f accel){
	this->acceleration = accel;
}

sf::Vector2f PhysicsObject::getAcceleration(){
	return acceleration;
}
void PhysicsObject::setActive(bool active){
	this->active = active;
}

bool PhysicsObject::getActive()
{
	return active;
}
