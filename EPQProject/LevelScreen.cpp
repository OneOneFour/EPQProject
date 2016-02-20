#define _USE_MATH_DEFINES
#include "LevelScreen.hpp"
#include "Helpies.hpp"
#include "PhysicsObject.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Planet.hpp"
LevelScreen::LevelScreen(Game* game):camera(sf::Vector2f(0,0),sf::Vector2f(game->getWidth(),game->getHeight())){
	this->game = game;
	this->camera.setTrack(true);
	this->world.init(*this);
	playerShip = dynamic_cast<Ship*>(world.createPhysObject(new Ship(sf::Vector2f(200, 200), world, "testShip")));
	for (int i = 0; i < 12; i++) {
		world.createPhysObject(new PhysicsObject(sf::Vector2f(genRandomFloat(0, game->getWidth()), genRandomFloat(0, game->getHeight())), world, "box"))->setMass(genRandomFloat(0.05f, 1.5f));

	}
	camera.setObjectToTrack(playerShip);
	//world.createPhysObject(new Planet(sf::Vector2f(600, 250), world, 6, 10, 50, 10));
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
			case sf::Event::KeyPressed:
				if(e.key.code == sf::Keyboard::F2) game->setDebug(!game->getDebug());
				break;
			default:
				break;
		}
	}
}
void LevelScreen::update(float deltaTime){
	world.step(deltaTime);
	//for each(UIElement* ui in uiElements) {
	//	ui->update(deltaTime);
	//}
}
void LevelScreen::draw(float deltaTime) {
	
	if (playerShip->getHealth() > 0){
		camera.setTrack(true);
	}
	else {
		camera.setTrack(false);
	}
	camera.update(deltaTime);
	game->window.setView(camera.getView());
	game->window.clear(sf::Color::Black);
	for (int i = 0; i < world.getObjCount(); i++) {
		PhysicsObject* obj = world.getPhysicsObject(i);
		if (dynamic_cast<Planet*>(obj) != NULL) {
			dynamic_cast<Planet*>(obj)->Draw(game->window);
		}
		else {
			game->window.draw(world.getPhysicsObject(i)->getSprite());
		}
		if (game->getDebug()) {
			for (int i = 0; i < obj->getCollider()->getVerticesSize(); i++) {
				sf::Vertex vertices[] = { sf::Vertex(sf::Vector2f(obj->getCollider()->getVertex(i)) + obj->getPos(),sf::Color::Green),
				sf::Vertex(sf::Vector2f(obj->getCollider()->getVertex(i + 1) + obj->getPos()),sf::Color::Green) };
				game->window.draw(vertices, 2, sf::LinesStrip);
				sf::RectangleShape aabb = sf::RectangleShape(sf::Vector2f(obj->getCollider()->getAABB().width, obj->getCollider()->getAABB().height));
				aabb.setPosition(obj->getPos() + sf::Vector2f(obj->getCollider()->getAABB().left, obj->getCollider()->getAABB().top));
				aabb.setFillColor(sf::Color::Transparent);
				aabb.setOutlineColor(sf::Color::Blue);
				aabb.setOutlineThickness(1.0f);
				game->window.draw(aabb);
			}
		}
	}
	for each(UIElement* ui in uiElements) {
		ui->draw(game->window);
	}
	sf::Text fpsCounter;
	fpsCounter.setFont(*game->bank.getFont("futura"));
	fpsCounter.setColor(sf::Color::White);
	fpsCounter.setString(std::to_string(1.0f / deltaTime));
	fpsCounter.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0,0)));
	game->window.draw(fpsCounter);
}