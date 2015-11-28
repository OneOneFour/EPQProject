#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include "Definitions.hpp"
struct Data {
	ShipData shipData;
	PhysicsData physicsData;
};
class ResourceBank{
public:
	ResourceBank();
	~ResourceBank();
	sf::Texture* getTexture(const std::string& name);
	sf::Font* getFont(const std::string& name);
	Data getDefs(const std::string& name);
	void addDefs(const std::string& filepath);
	void addTexture(const std::string& name, const std::string& filepath);
	void addFont(const std::string& name, const std::string& filepath);
private:
	std::vector<sf::Vector2f> readVertices(std::ifstream& fileStream);
	ShipData loadShipData(std::ifstream& fileStream);
	PhysicsData loadPhysicsData(std::ifstream& fileStream);
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, Data> data;
};