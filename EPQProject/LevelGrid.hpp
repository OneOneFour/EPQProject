#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Game.hpp"
enum TileType{
	OPEN,
	WALL,
	CHAR
};
class LevelGrid{
public:
	LevelGrid(std::vector<std::vector<char>> data);
	~LevelGrid();
	void setGridatPos(sf::Vector2i localPos, TileType type);
	TileType getGridatPos(sf::Vector2i localPos);
	sf::Vector2i coordinateToGrid(sf::Vector2f worldPos);
	sf::Vector2f gridToCoordinate(sf::Vector2i localPos);
	sf::Vector2f getGridDims();
	sf::Vector2f getScaleFactor(float width, float height);
	void draw(Game* game, float deltaTime);
	void update(float deltaTime);
private:
	int tileD = 10;
	int maxX, maxY;
	std::vector<std::vector<TileType>> tiles;
};

