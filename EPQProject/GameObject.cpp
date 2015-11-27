#include "GameObject.hpp"
GameObject::GameObject(sf::Vector2f position,Screen& screen):screen(screen){
	this->position = position;
}
GameObject::~GameObject(){

}
float GameObject::getRotation()
{
	return this->rotation;
}
void GameObject::setRotation(float rotation){
	this->rotation = rotation;
}
void GameObject::setPos(sf::Vector2f pos) {
	this->position = pos;
}
sf::Vector2f GameObject::getPos() {
	return position;
}