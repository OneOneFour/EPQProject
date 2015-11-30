#pragma once
#include <SFML\Graphics.hpp>
#include "Game.hpp"
class PhysicsObject;
class UIElement;
class Screen{
public:
	Game* game;
	std::vector<UIElement*> uiElements;
	virtual void onInput() = 0;
	virtual UIElement* createUIElement(UIElement* ui);
	virtual void update(float deltaTime) = 0;
	virtual void draw(float deltaTime) = 0;
};