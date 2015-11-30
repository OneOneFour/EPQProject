#define _USE_MATH_DEFINES
#include "LevelScreen.hpp"
#include "Helpies.hpp"
#include "PhysicsObject.hpp"
#include "Ship.hpp"
#include "Planet.hpp"
LevelScreen::LevelScreen(Game* game){
	this->game = game;
	this->world.init(*this);
	mainCamera.setSize(game->getWidth(),game->getHeight());
	mainCamera.setCenter(mainCamera.getSize().x / 2, mainCamera.getSize().y / 2);
	world.createPhysObject(new Ship(sf::Vector2f(200, 200), world, "testShip"));
	world.createPhysObject(new PhysicsObject(sf::Vector2f(300, 200), world, "box"));

	world.createPhysObject(new Planet(sf::Vector2f(600, 250), world, 6, 10, 50, 10));
}
LevelScreen::~LevelScreen(){
	while (!uiElements.empty()) {
		delete uiElements.back();
		uiElements.pop_back();
	}
}
void LevelScreen::onInput(){
	sf::Event e;
	while (game->window.pollEvent(e)){
		switch (e.type){
			case sf::Event::Closed:
				game->window.close();
				break;
			default:
				break;
		}
	}
}
void LevelScreen::update(float deltaTime){
	world.step(deltaTime);
	for each(UIElement* ui in uiElements) {
		ui->update(deltaTime);
	}
}
void LevelScreen::draw(float deltaTime) {
	game->window.clear(sf::Color::Black);
	for (int i = 0; i < world.getObjCount(); i++) {
		PhysicsObject* obj = world.getPhysicsObject(i);
		if (dynamic_cast<Planet*>(obj) != NULL) {
			dynamic_cast<Planet*>(obj)->Draw(game->window);
		}
		else {
			game->window.draw(world.getPhysicsObject(i)->getSprite());
		}
		for (int i = 0; i < obj->getCollider()->getVerticesSize(); i++) {
			sf::Vertex vertices[] = { sf::Vertex(sf::Vector2f(obj->getCollider()->getVertex(i)) + obj->getPos(),sf::Color::Green),
			sf::Vertex(sf::Vector2f(obj->getCollider()->getVertex(i + 1) + obj->getPos()),sf::Color::Green) };
			game->window.draw(vertices, 2, sf::LinesStrip);
			sf::RectangleShape aabb = sf::RectangleShape(sf::Vector2f(obj->getCollider()->getAABB().width, obj->getCollider()->getAABB().height));
			aabb.setPosition(obj->getPos() + sf::Vector2f(obj->getCollider()->getAABB().left,obj->getCollider()->getAABB().top));
			aabb.setFillColor(sf::Color::Transparent);
			aabb.setOutlineColor(sf::Color::Blue);
			aabb.setOutlineThickness(1.0f);
			game->window.draw(aabb);
			
		}
	}
	for each(UIElement* ui in uiElements) {
		ui->draw(game->window);
	}
	game->window.setView(mainCamera);
}