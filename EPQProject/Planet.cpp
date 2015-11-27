#include "Planet.hpp"
#include <cmath>
Planet::Planet(){
}
void Planet::init(sf::Vector2f origin, int roughness, float maxAlt, float radius = 150.f,float mass = 1.0f){
	this->leftPos = sf::Vector2f(0, 0);
	this->rightPos = sf::Vector2f(800, 0);;
	this->origin = origin;
	heightmap.push_back(leftPos);
	heightmap.push_back(rightPos);
	this->roughness = roughness;
	this->maxAlt = maxAlt;
	this->mass = mass;
	this->radius = radius;
	genMesh();
	verticesArrPtr = new sf::Vertex[vertices.size()];
	PhysicsObject::planets.push_back(this);
}
Planet::~Planet(){
	delete verticesArrPtr;
}
sf::Vector2f Planet::randomPos(sf::Vector2f left, sf::Vector2f right, float subCount){
	float xPos = (left.x + right.x) / 2;
	float yPos = ((left.y + right.y) / 2) + genRandomFloat(-maxAlt/subCount, maxAlt/subCount);
	return sf::Vector2f(xPos, yPos);
}
void Planet::genMesh(){
	for (int i = 0; i < roughness; i++){
		float numberOfSubs = heightmap.size() - 1;
		for (int s = 0; s < numberOfSubs; s++){
			sf::Vector2f left = heightmap[2 * s];
			sf::Vector2f right = heightmap[(2 * s) + 1];
			sf::Vector2f newPos(randomPos(left, right, numberOfSubs));
			auto iterator = heightmap.begin();
			heightmap.insert(iterator + ((2 * s) + 1), newPos);
		}
	}
	//COnvert to circle.
	for (int i = 0; i < heightmap.size(); i++){
		float alt = heightmap[i].y;
		float circlePos = ( float(i) / (heightmap.size() - 1)) * 2 * std::_Pi; //gets poisiton in rads
		float y = origin.y + std::cos(circlePos) * (radius + alt);
		float x = origin.x + std::sin(circlePos) * (radius + alt);
		vertices.push_back(sf::Vertex(sf::Vector2f(x, y),sf::Color::Black));
	}
}
float Planet::getAngle(sf::Vector2f position){
	float angleFromVertical = std::atan2(position.x - origin.x, position.y - origin.y);
	if (angleFromVertical < 0){
		angleFromVertical += 2 * std::_Pi;
	}
	return angleFromVertical;
}
float Planet::getAltitude(sf::Vector2f position){
	float angle = getAngle(position);
	int pos = (angle * heightmap.size() - 1) / (2 * std::_Pi);
	float alt = heightmap[pos].y + radius;
	return alt;
}
bool Planet::checkCollision(sf::Vector2f position){
	float distance = std::sqrt(std::pow(position.x - origin.x, 2) + std::pow(position.y - origin.y, 2));
	if (distance <= getAltitude(position)){
		printf("COLLISION! Height: %f  \n",distance);
		return true;
	}
	return false;	
}
void Planet::Draw(sf::RenderWindow& window){
	for (int i = 0; i < vertices.size(); i++){
		verticesArrPtr[i] = vertices[i];
	}
	window.draw(verticesArrPtr, vertices.size(), sf::LinesStrip);

}
