#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.hpp"
#include "GameObject.hpp"
#include "PhysicsWorld.hpp"
#include "UIElement.hpp"
class LevelScreen : public Screen{
public:
	LevelScreen(Game* game);
	~LevelScreen();
	void onInput();
	void update(float deltaTime);
	void draw(float deltaTime);
private:
	sf::View mainCamera;
	PhysicsWorld world;
};

