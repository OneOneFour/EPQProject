#pragma once
#include <random>
#include <cmath>
#include <SFML\Graphics.hpp>
extern float genRandomFloat(float min, float max);//Generates a random float between the two values using seed
extern float getMagnitude(sf::Vector2f A);
extern float getDistance(sf::Vector2f A, sf::Vector2f B);//Finds shortest distance between two vectors
extern double getArgument(sf::Vector2f A);//gets angle from the vertical
extern double getArgumentH(sf::Vector2f A);//gets angle from horizontal 
extern sf::Vector2f normalizeVector(sf::Vector2f vector);//Turns vector into a unit vector
extern float dotProduct(sf::Vector2f a, sf::Vector2f b);
extern sf::Vector2f lerp(sf::Vector2f vectorA, sf::Vector2f vectorB, float lerpFactor);//Linearly interpolates between two vectors in accorfance with the lerp factor
extern float lerp(float a, float b, float lerpFactor);
extern float incrementTowards(float u, float v, float a,float d);
extern double radToDegree(float angle);//Converts from radians to degrees
extern double degreeToRad(float angle);//converts angle from degrees to radians 
template <typename T> inline int sgn(T val) { //Thanks to user79758 on stackExchange!
	return (T(0) < val) - (val < T(0));
}