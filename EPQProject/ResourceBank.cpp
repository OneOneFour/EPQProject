#include "ResourceBank.hpp"
ResourceBank::ResourceBank(){
	sf::Image auxImg;
	auxImg.create(32, 32, sf::Color::White);
	for (int x = 0; x < 32; x++){
		for (int y = 0; y < 32; y++){
			if (y == x || y == 32 - x){
				auxImg.setPixel(x, y, sf::Color::Red);
			}
		}
	}
	auxImg.setPixel(16, 0, sf::Color::Red);
	auxImg.setPixel(16, 1, sf::Color::Red);
	auxImg.setPixel(16, 2, sf::Color::Red);
	sf::Texture* temp = new sf::Texture();
	temp->loadFromImage(auxImg);
	this->textures["default"] = temp;
}
ResourceBank::~ResourceBank(){
	for (auto iterator = textures.begin(); iterator != textures.end(); ++iterator){
		printf("FREED:Texure %s freed\n", iterator->first.c_str());
		delete iterator->second;
	}
	for (auto iterator = fonts.begin(); iterator != fonts.end(); ++iterator){
		printf("FREED:Font %s freed\n", iterator->first.c_str());
		delete iterator->second;
	}
}
void ResourceBank::addTexture(const std::string& name, const std::string& filepath){
	sf::Texture* temp = new sf::Texture();
	if (!temp->loadFromFile(filepath)){
		printf("ERROR: Unable to load tetxure at %s. Default texture used instead\n", filepath.c_str());
		this->textures[name] = this->textures["default"];
		return;
	}
	printf("LOADED: %s loaded\n", filepath.c_str());
	this->textures[name] = temp;
}

void ResourceBank::addFont(const std::string& name, const std::string& filepath){
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(filepath)){
		printf("ERROR: Unable to load font at %s.\n", filepath.c_str());
		return;
	}
	printf("LOADED: %s loaded\n", filepath.c_str());
	this->fonts[name] = font;
}
ShipData ResourceBank::loadShipData(std::ifstream& fileStream){
	std::string data;
	ShipData shipD;
	while (std::getline(fileStream, data) && data.find("}") == std::string::npos) {
		data.erase(std::remove_if(data.begin(), data.end(), isspace),data.end());
		if (data.find("health=") != std::string::npos) {
			shipD.health = std::atoi(data.substr(7).c_str());
		}
		else if (data.find("maxThrust=") != std::string::npos) {
			shipD.maxThrust = std::atof(data.substr(10).c_str());
		}
		else if (data.find("manuvarbility=") != std::string::npos) {
			shipD.manuv = std::atof(data.substr(14).c_str());
		}
	}
	return shipD;
}
std::vector<sf::Vector2f> getVertices(std::ifstream& fileStream) {
	std::string data;
	std::vector<sf::Vector2f> vertices;
	while (std::getline(fileStream, data) && data.find("}") == std::string::npos) {
		data.erase(std::remove_if(data.begin(), data.end(), isspace), data.end());
		size_t cPos = data.find(",");
		if (cPos == std::string::npos) {
			printf("ERROR: Error reading vertex data. Ensure two values are given when a vector2 is required\n");
			return std::vector<sf::Vector2f>();
		}
		vertices.push_back(sf::Vector2f(std::atof(data.substr(0, cPos).c_str()), 
			std::atof(data.substr(cPos+1).c_str())));

	}
	return vertices;
}
PhysicsData ResourceBank::loadPhysicsData(std::ifstream& fileStream){
	std::string data;
	PhysicsData physD;
	while (std::getline(fileStream, data) && data.find("}") == std::string::npos) {
		data.erase(std::remove_if(data.begin(), data.end(), isspace),data.end());
		if (data.find("sprite=") != std::string::npos) {
			physD.textureID = data.substr(7);
		}
		else if (data.find("mass=") != std::string::npos) {
			physD.mass = std::atof(data.substr(5).c_str());
		}
		else if (data.find("Vertices{") != std::string::npos) {
			physD.vertices = getVertices(fileStream);
		}
	}
	return physD;
}
sf::Texture* ResourceBank::getTexture(const std::string& name){
	if (textures.find(name) == textures.end()){
		printf("Unable to find texture %s. Using default \n", name.c_str());
		return textures["default"];
	}
	return textures[name];
}
sf::Font* ResourceBank::getFont(const std::string& name){
	if (fonts.find(name) == fonts.end()){
		printf("ERROR: Unable to find font %s. \n", name.c_str());
		return nullptr;
	}
	return fonts[name];
}

Data ResourceBank::getDefs(const std::string & name){
	if (data.find(name) == data.end()) {
		printf("ERROR: Unable to find def %s. \n", name.c_str());
		return Data();
	}
	return data[name];
}

void ResourceBank::addDefs(const std::string & filepath){
	std::ifstream file;
	std::string name;
	Data ldata;
	file.open(filepath,std::ios::in);
	if (!file) {
		printf("ERROR: Could not load file %s \n", filepath.c_str());
	}
	std::string lineData;
	while (std::getline(file, lineData)) {
		lineData.erase(std::remove_if(lineData.begin(), lineData.end(), isspace),lineData.end());
		if (lineData.find("name=") != std::string::npos) {
			name = lineData.substr(5);
		}
		else if (lineData.find("ShipData{") != std::string::npos) {
			ldata.shipData = loadShipData(file);
			
		}
		else if (lineData.find("PhysicsData{") != std::string::npos) {
			printf("LOADED: Physics Def %s at %s \n", name.c_str(), filepath.c_str());
			ldata.physicsData = loadPhysicsData(file);
		}
	}
	this->data[name] = ldata;
}
