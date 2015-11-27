#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.hpp"
class GameObject{
public:
	GameObject(sf::Vector2f position,Screen& screen);
	~GameObject();
	float getRotation();
	void setRotation(float rotation);
	void setPos(sf::Vector2f pos);
	sf::Vector2f getPos();
	virtual void update(float deltaTime) = 0;
protected:
	float rotation = 0;
	sf::Vector2f position; 
	Screen& screen;
};

