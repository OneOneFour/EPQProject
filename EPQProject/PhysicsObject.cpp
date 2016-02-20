#include "PhysicsObject.hpp"
#include "PhysicsWorld.hpp"
#include "Helpies.hpp"
PhysicsObject::PhysicsObject(sf::Vector2f position,PhysicsWorld& world,std::string prefID) : GameObject(position),col(*this),world(world){
	PhysicsData data = world.bankPtr->getDefs(prefID).physicsData;
	this->mass = data.mass;
	this->setSprite(data.textureID);
	this->col.init(data.vertices);
	this->kinematic = true;
	//calculare moment of interia 
	for (int i = 0; i < this->col.getVerticesSize(); i++){
		momentOfInertia += (this->mass / col.getVerticesSize()) * std::powf(getMagnitude(col.getVertex(i)),2);
	}
}
PhysicsObject::PhysicsObject(sf::Vector2f position, PhysicsWorld & world):GameObject(position),col(*this),world(world){
	this->kinematic = true;
	this->angularVeloc = 0;
	this->angularAccel = 0;
}
PhysicsObject::PhysicsObject(sf::Vector2f position, PhysicsWorld & world, sf::Vector2f vertices[],int size):GameObject(position),world(world),col(*this){
	this->kinematic = true;
	std::vector<sf::Vector2f> verticesV;
	for (int i = 0; i < size; i++){
		verticesV[i] = vertices[i];
	}
	this->col.init(verticesV);
}
PhysicsObject::~PhysicsObject(){

}
void PhysicsObject::applyForce(sf::Vector2f force, sf::Vector2f location) {
	frameNetForce += force;
	netTorque += (force.y * location.x) + (-force.x * location.y);
}
void PhysicsObject::update(float deltaTime){
	this->frameNetForce = sf::Vector2f(0, 0);
	this->netTorque = 0;
}
void PhysicsObject::draw(float deltaTime){
	if (kinematic) {
		acceleration = frameNetForce / mass;
		angularAccel = netTorque / momentOfInertia;
		velocity += acceleration*deltaTime;  

		angularVeloc += angularAccel * deltaTime;
		position += velocity * deltaTime;
		rotation += radToDegree(angularVeloc) * deltaTime;
		this->sprite.setPosition(position);
		this->sprite.setRotation(rotation);
	}
	else {
		velocity = sf::Vector2f(0, 0);
	}
}
void PhysicsObject::setVelocity(sf::Vector2f vel){
	this->velocity = vel;
}
void PhysicsObject::onCollision(sf::Vector2f colPoint, PhysicsObject * collided){
	return;
}
void PhysicsObject::setName(const std::string & name){
	this->name = name;
}
bool PhysicsObject::isKinematic()
{
	return kinematic;
}
float PhysicsObject::getMass()
{
	return mass;
}
void PhysicsObject::setMass(float mass){
	this->mass = mass;
}
std::string PhysicsObject::getName()
{
	return name;
}
sf::Sprite PhysicsObject::getSprite(){
	return sprite;
}
float PhysicsObject::getAngularVelocity()
{
	return angularVeloc;
}
void PhysicsObject::setSprite(std::string textureID){
	this->textureID = textureID;
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
