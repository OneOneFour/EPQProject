#pragma once
#include "GameObject.hpp"
class Camera : public GameObject{
public:
	Camera(sf::Vector2f position,sf::Vector2f size);
	~Camera();
	void setObjectToTrack(GameObject* obj);
	void setTrack(bool tracking);
	bool getTrack();
	sf::View getView();
	GameObject* getTrackedObject();
	void update(float deltaTime);
private:
	bool track;
	GameObject* trackingObj;
	sf::View cameraView;
};

