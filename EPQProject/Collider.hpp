#pragma once
#include <SFML\Graphics.hpp>

class PhysicsObject;
class Collider {
public:
	Collider(PhysicsObject& obj);
	void init(std::vector<sf::Vector2f> vertices);
	void init(std::vector<sf::Vertex> vertices);
	~Collider();
	bool colCheck(Collider& othercol,sf::Vector2f iPos,sf::Vector2f jPos);
	sf::Vector2f getVertex(const int index);
	int getVerticesSize();
	sf::FloatRect getAABB();
	void setVertex(sf::Vector2f vertex, const int index);
	void update();
	PhysicsObject& attachedObj;
private:
	sf::FloatRect aabb;
	std::vector<double> initAngle;
	std::vector<sf::Vector2f> vertices;//Points should be arranged in a clockwise fashion connecting lines. Do not repeat last point
};