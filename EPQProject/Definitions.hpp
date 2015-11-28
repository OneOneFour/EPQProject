#pragma once
#include <SFML\Graphics.hpp>

struct PhysicsData {
	float mass, coR;
	std::string textureID;
	std::vector<sf::Vector2f> vertices;
};
struct ShipData{
	float health, manuv, maxThrust;
};