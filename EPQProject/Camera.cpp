#include "Camera.hpp"
#include "Helpies.hpp"
Camera::Camera(sf::Vector2f position, sf::Vector2f size) :GameObject(position) {
	this->cameraView.setSize(size);
}
Camera::~Camera()
{
}

void Camera::setObjectToTrack(GameObject * obj){
	this->trackingObj = obj;
}

void Camera::setTrack(bool tracking){
	this->track = tracking;
}

bool Camera::getTrack()
{
	return track;
}

sf::View Camera::getView()
{
	return cameraView;
}

GameObject * Camera::getTrackedObject()
{
	return trackingObj;
}

void Camera::update(float deltaTime){
	if (track) {
		this->position = lerp(this->position, trackingObj->getPos(), 0.5f);
	}
	this->cameraView.setCenter(this->position);
}
