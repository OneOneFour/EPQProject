#include "Collider.hpp"
#include "PhysicsObject.hpp"
Collider::Collider(PhysicsObject& obj):attachedObj(obj){
	
}
void Collider::init(std::vector<sf::Vector2f> vertices) {
	this->vertices = vertices;
	aabb.left = FLT_MAX;
	aabb.top = FLT_MAX;
	float right = 0;
	float bottom = 0;
	for (int i = 0; i < this->vertices.size();i++) {
		this->vertices[i].x = this->vertices[i].x * attachedObj.getSprite().getTexture()->getSize().x/2;
		this->vertices[i].y = this->vertices[i].y * attachedObj.getSprite().getTexture()->getSize().y/2;
		aabb.left = (this->vertices[i].x < aabb.left) ? this->vertices[i].x : aabb.left;
		aabb.top = (this->vertices[i].y < aabb.top) ? this->vertices[i].y : aabb.top;
		right = (this->vertices[i].x > right) ? this->vertices[i].x : right;
		bottom = (this->vertices[i].y > bottom) ? this->vertices[i].y : bottom;
	}
	aabb.width = right - aabb.left;
	aabb.height = bottom - aabb.top;
}
Collider::~Collider() {

}
bool Collider::checkIfColliding(Collider& otherCol) {
	//AABB check
	sf::FloatRect otherAABB = otherCol.getAABB();
	if (aabb.top + aabb.height + attachedObj.getPos().y <= otherAABB.top + otherCol.attachedObj.getPos().y) return false;
	if (aabb.top + attachedObj.getPos().y >= otherAABB.top + otherAABB.height + otherCol.attachedObj.getPos().y) return false;
	if (aabb.left + aabb.width + attachedObj.getPos().x <= otherAABB.left + otherCol.attachedObj.getPos().x) return false;
	if (aabb.left + attachedObj.getPos().x >= otherAABB.left + otherAABB.width + otherCol.attachedObj.getPos().x) return false;
	printf("AABB collision\n");
	for (int i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < otherCol.getVerticesSize(); j++) {
			sf::Vector2f iA = vertices[i] + attachedObj.getPos();
			sf::Vector2f iB = ((i + 1 >= vertices.size()) ? vertices[0] : vertices[i + 1]) + attachedObj.getPos();

			sf::Vector2f jA = otherCol.getVertex(i) + otherCol.attachedObj.getPos();
			sf::Vector2f jB = ((j + 1 >= otherCol.getVerticesSize()) ? otherCol.getVertex(0) : otherCol.getVertex(j + 1)) + otherCol.attachedObj.getPos();
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
					return true;
				}
			}
		}
	}
	return false;
}
sf::Vector2f Collider::getVertex(const int index){
	return vertices[index];
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
