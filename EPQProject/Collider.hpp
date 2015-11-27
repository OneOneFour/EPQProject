#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicsObject.hpp"
class Collider {
public:
	Collider(std::vector<sf::Vector2f> vertices,PhysicsObject& obj);
	~Collider();
	bool checkIfColliding(Collider& otherCol);
	sf::Vector2f getVertex(const int index);
	int getVerticesSize();
	sf::FloatRect getAABB();
	void setVertex(sf::Vector2f vertex, const int index);
	PhysicsObject& attachedObj;
private:
	sf::FloatRect aabb;
	std::vector<sf::Vector2f> vertices;//Points should be arranged in a clockwise fashion connecting lines. Do not repeat last point
};