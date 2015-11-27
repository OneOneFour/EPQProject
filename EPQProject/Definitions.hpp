#pragma once
#include <SFML\Graphics.hpp>

struct PhysicsData {
	float mass, coR;
	std::string textureID;
};
struct ShipData{
	float health, manuv, maxThrust;
};