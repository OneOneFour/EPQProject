#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "PhysicsObject.hpp"
#include "Helpies.hpp"
class Planet{
public:
	Planet();
	~Planet();
	void init(sf::Vector2f origin, int roughness, float maxAlt,float radius,float mass);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getOrigin(){ return origin; };
	float getMass(){ return mass; };
	float getAltitude(sf::Vector2f position);
	bool checkCollision(sf::Vector2f position);
private:
	void genMesh();
	float getAngle(sf::Vector2f position);
	sf::Vertex* verticesArrPtr;
	sf::Vector2f randomPos(sf::Vector2f left, sf::Vector2f right, float subCount);
	int roughness;
	float maxAlt, radius;
	sf::Vector2f leftPos, rightPos,origin;
	std::vector<sf::Vertex> vertices;
	std::vector<sf::Vector2f> heightmap;
	//Physics
	float density;
	float mass;
};

