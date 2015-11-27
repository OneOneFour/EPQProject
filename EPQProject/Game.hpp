#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <stack>
#include <fstream>
#include "ResourceBank.hpp"
class Screen;
class Game{
public:
	int loadTime;

	Game();
	~Game();

	void loadLevel(int levelID);
	void loadLevel();
	void addToScreens(Screen* screen);
	void removeTopScreen();
	void changeTopScreen(Screen* screen);

	int getWidth();
	int getHeight();
	int getphysQ();
	float getfpsCap();

	Screen* getTopScreen();

	void heartBeat();

	ResourceBank bank;
	sf::RenderWindow window;
	sf::Clock deltaClock;
	std::stack<Screen*> screens;
private:
	void loadMedia();
	int width = 800;
	int height = 480;
	int physQ;
	int antialising;
	bool vsync = true;
	bool fullscreen = false;
	float fpsCap = 60.f;
};