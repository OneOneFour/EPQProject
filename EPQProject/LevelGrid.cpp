#include "LevelGrid.hpp"

LevelGrid::LevelGrid(std::vector<std::vector<char>> data){ 
	this->tiles.resize(data[0].size());
	for (int y = 0; y < data.size(); y++){
		for (int x = 0; x < data[y].size(); x++){
			this->tiles[x].resize(data.size());
			switch (data[y][x]){
			case '0':
				tiles[x][y] = TileType::OPEN;
				break;
			case '1':
				tiles[x][y] = TileType::CLOSED;
				break;
			default:
				tiles[x][y] = TileType::CLOSED;
				break;
			}
		}
	}
	this->maxX = tiles.size() - 1;
	this->maxY = tiles[0].size() - 1;
}
void LevelGrid::setGridatPos(sf::Vector2i pos, TileType type){
	if (pos.x > maxX || pos.y > maxY || pos.x < 0 || pos.y < 0){
		printf("ERROR: Invalid coordinates X:%i , Y:%i \n", pos.x, pos.y);
		return;
	}
	this->tiles[pos.x][pos.y] = type;
}
TileType LevelGrid::getGridatPos(sf::Vector2i pos){
	return this->tiles[pos.x][pos.y];
}
sf::Vector2i LevelGrid::coordinateToGrid(sf::Vector2f worldPos){
	return sf::Vector2i((int)(worldPos.x / tileD), (int)(worldPos.y / tileD));
}
sf::Vector2f LevelGrid::gridToCoordinate(sf::Vector2i localPos){
	return sf::Vector2f(localPos.x * tileD, localPos.y * tileD);
}
sf::Vector2f LevelGrid::getGridDims(){
	return sf::Vector2f(tiles.size() * tileD, tiles[0].size()*tileD);
}
sf::Vector2f LevelGrid::getScaleFactor(float width, float height) {
	sf::Vector2f start = getGridDims();
	if ((start.x / start.y) != (width / height)) {
		if (width / height < 1) {
			start.x = (start.y * width) / height;
		}
		start.y = (start.x * height) / width;
	}
	return start;
}
void LevelGrid::draw(Game* game,float deltaTime){
	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f(tiles.size()*tileD, tiles[0].size()*tileD));
	bg.setFillColor(sf::Color(155, 89, 182));
	game->window.draw(bg);
	bg.setSize(sf::Vector2f(tileD, tileD));
	for (int x = 0; x < maxX; x++){
		for (int y = 0; y < maxY; y++){
			switch (tiles[x][y]){
				case TileType::OPEN:
					break;
				case TileType::WALL:
					bg.setPosition(gridToCoordinate(sf::Vector2i(x, y)));
					bg.setFillColor(sf::Color(142, 68, 173));
					game->window.draw(bg);
					break;
				default:
					break;
			}
		}
	}
}
LevelGrid::~LevelGrid(){
}
