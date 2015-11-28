#define _USE_MATH_DEFINES
#include "Helpies.hpp"
float coloumbsConstant = 9000000000;

float genRandomFloat(float min, float max){
	float range = max - min;
	return min + (rand() / (float(RAND_MAX) / range));
}
float getMagnitude(sf::Vector2f A) {
	return std::sqrt(std::pow(A.x, 2) + std::pow(A.y, 2));
}
float getDistance(sf::Vector2f A, sf::Vector2f B){
	return std::sqrt(std::pow(A.x - B.x, 2) + std::pow(A.y - B.y, 2));
}
double getArgument(sf::Vector2f A){
	return std::atan2(A.y, A.x);
}
double getArgumentH(sf::Vector2f A){
	return std::atan2(A.x, A.y);
}
void normalizeVector(sf::Vector2f& vector){
	float magnitude = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
	vector.x = vector.x /  magnitude;
	vector.y = vector.y / magnitude;
}
sf::Vector2f lerp(sf::Vector2f vectorA, sf::Vector2f vectorB, float lerpFactor){
	return sf::Vector2f(vectorA.x + (lerpFactor* (vectorB.x - vectorA.x)), vectorA.y + (lerpFactor* (vectorB.y - vectorA.y)));
}
double degreeToRad(float angle){
	return (angle / 180.0)* M_PI;
	
}
double radToDegree(float angle){
	return (angle / M_PI) * 180.0;
}