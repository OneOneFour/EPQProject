#include "Screen.hpp"
#include "Game.hpp"
#include "LevelScreen.hpp"

Game::Game(){
	srand(time(NULL));
	std::ifstream inSettings;
	inSettings.open("settings.txt",std::ios::in);
	std::string lineData;
	if (!inSettings.fail()){
		while (std::getline(inSettings, lineData)) {
			lineData.erase(std::remove_if(lineData.begin(), lineData.end(), isspace),lineData.end());
			if (lineData.find("Width:") != std::string::npos) {
				width = std::atoi(lineData.substr(6).c_str());
				std::cout << "INFO: window width set to " << width << std::endl;
			}
			else if (lineData.find("Height:") != std::string::npos) {
				height = std::atoi(lineData.substr(7).c_str());
				std::cout << "INFO: window height set to " << height << std::endl;
			}
			else if (lineData.find("VSync:") != std::string::npos) {
				vsync = std::atoi(lineData.substr(6).c_str());
				std::cout << "INFO: vSync is " << vsync << std::endl;
			}
			else if ( lineData.find("FpsCap:") != std::string::npos) {
				fpsCap = std::atof(lineData.substr(7).c_str());
				std::cout << "INFO: fps cap (if enabled) is " << fpsCap << std::endl;
			}
			else if (lineData.find("Fullscreen:") != std::string::npos) {
				fullscreen = std::atoi(lineData.substr(11).c_str());
				std::cout << "INFO: Fullscreen is " << fullscreen << std::endl;
			}
			else if (lineData.find("Antialiasing:") != std::string::npos) {
				antialising = std::atoi(lineData.substr(13).c_str());
				std::cout << "INFO: Antialiasing is " << antialising << "x" << std::endl;
			}
			else {
				continue;
			}
		}
		inSettings.close();
	}
	else {//Create file with default res and fps settings
		std::cout << "ERROR: File not found, creating default" << std::endl;
		std::ofstream outSettings;
		outSettings.open("settings.txt");
		if (!outSettings.is_open()) {
			std::cout << "ERROR: Could not write a settings file, please check your permissions" << std::endl;		
		}
		else {
			outSettings << "Width:" << width << "\n";
			outSettings << "Height:" << height << "\n";
			outSettings << "Fullscreen:" << fullscreen << "\n";
			outSettings << "VSync:" << vsync << "\n";
			outSettings << "FpsCap:" << fpsCap << "\n";
			outSettings << "Antialiasing:" << antialising << "\n";
		}
		outSettings.close();
	}
	sf::ContextSettings gpuSettings = sf::ContextSettings(0U, 0U,antialising, 1U, 1U, 0U);
	if (fullscreen) {
		window.create(sf::VideoMode(width, height), "EPQ Project", sf::Style::Fullscreen,gpuSettings);
	}
	else {
		window.create(sf::VideoMode(width, height), "EPQ Project", sf::Style::Close,gpuSettings);
	}
	window.setVerticalSyncEnabled(vsync);
	if (!vsync) window.setFramerateLimit(fpsCap);
	//Pre load code here please
	loadMedia();
	loadLevel();
	heartBeat();	
}
/*
void Game::loadLevel(int levelID){
	window.clear(sf::Color::Black);
	sf::Text loadingText ("Loading Level", *bank.getFont("futura"));
	window.draw(loadingText);
	window.display();
	//Load Level here
	std::string filepath = std::to_string(levelID) + ".leveldat";
	std::ifstream file;
	file.open(filepath, std::ios::in);
	if (!file.is_open()){
		std::cout << "ERROR: Cannot open file " << filepath << std::endl;
		return;
	}
	std::string lineData;
	std::vector<std::vector<char>> levelData;
	int yCount=0;
	while (std::getline(file,lineData)){
		if (lineData[0] == 0) continue;
		if (lineData[0] == 'H'){
			levelData.resize(std::atoi(lineData.substr(2).c_str()));
		}
		else if (lineData[0] == 'W'){
			for (int i = 0; i < levelData.size(); i++){
				levelData[i].resize(std::atoi(lineData.substr(2).c_str()));
			}
		}
		else{
			while (lineData.size() < levelData.size()){
				lineData.append("1");
			}
			for (int x = 0; x < lineData.length(); x++){
				levelData[yCount][x] = lineData[x];
			}
			yCount++;
		}
	}
	file.close();
	if (!levelData.empty()){
		std::cout << "INFO: Read file " << filepath << " succesfully" << std::endl;
		addToScreens(new LevelScreen(this,levelData)); //Load Level
	}
	else{
		std::cout << " ERROR: File " << filepath << " was read succesfully but a level could not be created. File may be corrupted" << std::endl;
	}
}
*/
void Game::loadLevel() {
	addToScreens(new LevelScreen(this));
}
void Game::loadMedia(){
	bank.addTexture("ship", "graphics/ShipModules.png");
	bank.addFont("futura", "futura-condensed-normal.ttf");
	bank.addDefs("ship.gamedef");
	bank.addDefs("box.gamedef");
}
void Game::addToScreens(Screen* screen){
	screens.push(screen);
}
int Game::getWidth()
{
	return width;
}
int Game::getHeight()
{
	return height;
}
int Game::getphysQ()
{
	return physQ;
}
float Game::getfpsCap()
{
	return fpsCap;
}
Screen* Game::getTopScreen(){
	if (screens.empty()) return nullptr;
	return screens.top();
}
void Game::removeTopScreen(){
	if (screens.empty()) return;
	delete screens.top();
	screens.pop();
}
void Game::changeTopScreen(Screen* screen){
	removeTopScreen();
	addToScreens(screen);
}
Game::~Game(){
	while (!screens.empty()){
		removeTopScreen();
	}
}
void Game::heartBeat(){
	//Post load code here please.
	float deltaTime = 0.f;
	loadTime = deltaClock.restart().asMilliseconds(); 
	std::cout << "INFO: Game loaded in " << loadTime << " milliseconds" << std::endl; // c++ way
	while (window.isOpen()){
		deltaTime = deltaClock.restart().asSeconds();
		if (getTopScreen() == nullptr) continue;
		window.clear(sf::Color::Black);
		getTopScreen()->onInput();
		getTopScreen()->update(deltaTime);
		getTopScreen()->draw(deltaTime);
		window.display();
	}
}
