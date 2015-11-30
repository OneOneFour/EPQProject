#include "Screen.hpp"

UIElement* Screen::createUIElement(UIElement* obj){
	uiElements.push_back(obj);
	return obj;
}

