#define _USE_MATH_DEFINES 
#include <cmath>
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Helpies.hpp"
#include "PhysicsObject.hpp"

Collider::Collider(PhysicsObject& obj):attachedObj(obj){
	
}
void Collider::init(std::vector<sf::Vector2f> vertices) {
	this->vertices = vertices;
	for (int i = 0; i < this->vertices.size(); i++) {
		this->vertices[i].x *= attachedObj.getSprite().getTexture()->getSize().x / 2;
		this->vertices[i].y *= attachedObj.getSprite().getTexture()->getSize().y / 2;
		this->initAngle.push_back(getArgument(this->vertices[i])+ M_PI/2);
	}
	update();
}
void Collider::init(std::vector<sf::Vertex> vertices) {
	this->vertices.resize(vertices.size());
	for (int i = 0; i < vertices.size(); i++) {
		this->vertices[i] = vertices[i].position - this->attachedObj.getPos();
		this->initAngle.push_back(getArgument(this->vertices[i]) + M_PI / 2);
	}
	update();
}
Collider::~Collider() {

}
void Collider::update() {
	aabb.left = FLT_MAX;
	aabb.top = FLT_MAX;
	float right = 0;
	float bottom = 0;
	for (int i = 0; i < this->vertices.size(); i++) {
		this->vertices[i] = sf::Vector2f(getMagnitude(this->vertices[i])*sin(degreeToRad(attachedObj.getRotation()) + initAngle[i]),
										-getMagnitude(this->vertices[i])*cos(degreeToRad(attachedObj.getRotation()) + initAngle[i]));
		aabb.left = (this->vertices[i].x < aabb.left) ? this->vertices[i].x : aabb.left;
		aabb.top = (this->vertices[i].y < aabb.top) ? this->vertices[i].y : aabb.top;
		right = (this->vertices[i].x > right) ? this->vertices[i].x : right;
		bottom = (this->vertices[i].y > bottom) ? this->vertices[i].y : bottom;
	}
	aabb.width = right - aabb.left;
	aabb.height = bottom - aabb.top;
}
sf::Vector2f Collider::getLastCol()
{
	return lastColPoint;
}
bool Collider::colCheck(Collider& otherCol,sf::Vector2f iPos,sf::Vector2f jPos) {
	if (dynamic_cast<Bullet*>(&attachedObj) != nullptr) {
		if (dynamic_cast<Bullet*>(&attachedObj)->getOwner()->getCollider() == &otherCol || dynamic_cast<Bullet*>(&otherCol.attachedObj) != nullptr) {
			return false;
		}
	}
	else if (dynamic_cast<Bullet*>(&otherCol.attachedObj) !=nullptr) {
		if (dynamic_cast<Bullet*>(&otherCol.attachedObj)->getOwner()->getCollider() == this) {
			return false;
		}
	}
	update();
	otherCol.update();
	sf::FloatRect otherAABB = otherCol.getAABB();
	if (aabb.top + aabb.height + iPos.y <= otherAABB.top + jPos.y) return false ;
	if (aabb.top + iPos.y >= otherAABB.top + otherAABB.height + jPos.y) return false;
	if (aabb.left + aabb.width + iPos.x <= otherAABB.left + jPos.x) return false;
	if (aabb.left + iPos.x >= otherAABB.left + otherAABB.width + jPos.x) return false;
	for (int i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < otherCol.getVerticesSize(); j++) {
			sf::Vector2f iA = vertices[i] + iPos;
			sf::Vector2f iB = ((i + 1 >= vertices.size()) ? vertices[0] : vertices[i + 1]) + iPos;

			sf::Vector2f jA = otherCol.getVertex(i) + jPos;
			sf::Vector2f jB = ((j + 1 >= otherCol.getVerticesSize()) ? otherCol.getVertex(0) : otherCol.getVertex(j + 1)) + jPos;
			sf::Vector2f colPoint;
			if (iA.x - iB.x == 0 || jA.x - jB.x == 0) {
				if (iA.x - iB.x == jA.x - jB.x) continue;
				colPoint = sf::Vector2f((iA.x - iB.x == 0) ? iA.x : jA.x,
					(iA.x - iB.x == 0) ? (jA.y - jB.y) / (jA.x - jB.x) *(iA.x - jA.x) + jA.y :
					(iA.y - iB.y) / (iA.x - iB.x) *(jA.x - iA.x) + iA.y);
			}
			else {
				float gI = (iA.y - iB.y) / (iA.x - iB.x);
				float cI = -gI*iA.x + iA.y;
				float gJ = (jA.y - jB.y) / (jA.x - jB.x);
				float cJ = -gJ*jA.x + jA.y;
				if (gJ - gI == 0) continue;
				colPoint = sf::Vector2f((cI - cJ) / (gJ - gI),
					gI*((cI - cJ) / (gJ - gI)) + cI);
			}
			//Check if col points are valid.. organize and set out
			if (((colPoint.x >= iA.x && colPoint.x <= iB.x) || (colPoint.x <= iA.x && colPoint.x >= iB.x)) &&
				((colPoint.y >= iA.y && colPoint.y <= iB.y) || (colPoint.y <= iA.y && colPoint.y >= iB.y))) {
				if (((colPoint.x >= jA.x && colPoint.x <= jB.x) || (colPoint.x <= jA.x && colPoint.x >= jB.x)) &&
					((colPoint.y >= jA.y && colPoint.y <= jB.y) || (colPoint.y <= jA.y && colPoint.y >= jB.y))) {
					lastColPoint = colPoint;
					return true;
				}
			}
		}
	}
	return false;
}
sf::Vector2f Collider::getVertex(const int index){
	const int rIndex = index % vertices.size();
	return vertices[rIndex];
}

int Collider::getVerticesSize()
{
	return vertices.size();
}

sf::FloatRect Collider::getAABB()
{
	return aabb;
}

void Collider::setVertex(sf::Vector2f vertex, const int index){
	vertices[index] = vertex;
}
