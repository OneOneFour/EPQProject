#include "PhysicsObject.hpp"
#include "PhysicsWorld.hpp"
PhysicsObject::PhysicsObject(sf::Vector2f position,PhysicsWorld& world,std::string prefID) : GameObject(position),col(*this),world(world){
	this->data = world.bankPtr->getDefs(prefID).physicsData;
	this->setSprite(data.textureID);
	this->col.init(data.vertices);
}
PhysicsObject::~PhysicsObject(){

}
void PhysicsObject::update(float deltaTime){
	position += velocity * deltaTime;
	this->sprite.setPosition(position);
	this->sprite.setRotation(rotation);
}
void PhysicsObject::setVelocity(sf::Vector2f vel){
	this->velocity = vel;
}
void PhysicsObject::setName(const std::string & name){
	this->name = name;
}
std::string PhysicsObject::getName()
{
	return name;
}
sf::Sprite PhysicsObject::getSprite(){
	return sprite;
}
void PhysicsObject::setSprite(std::string textureID){
	this->sprite.setTexture(*world.bankPtr->getTexture(textureID));
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

Collider * PhysicsObject::getCollider()
{
	return &col;
}
