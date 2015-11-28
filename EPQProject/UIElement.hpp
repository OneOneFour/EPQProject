#pragma once
#include "GameObject.hpp"
class UIElement : public GameObject{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	/*
		Stuff goes here
	*/
};

