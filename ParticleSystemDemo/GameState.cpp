#include "GameState.h"

#include "Object.h"

GameState::GameState() {
}


GameState::~GameState() {
}

void GameState::processEvent(SDL_Event e) {
}

void GameState::serialRender(RenderingEngine * engine) {
}

void GameState::OnChangeTo() {
}

void GameState::OnChangeAway() {
}

void GameState::registerObject(Object * object) {
	if (object->hasSerialUpdate())
		serialObjects.push_back(object);
	if (object->hasRenderInformation()) 
		serialRenderObjects.push_back(object);
}

void GameState::deleteObject(Object * object) {
	if (object->hasSerialUpdate()) for (auto obj = serialObjects.begin(); obj != serialObjects.end(); obj++) if (*obj == object) { serialObjects.erase(obj); break; }
	if (object->hasRenderInformation()) for (auto obj = serialRenderObjects.begin(); obj != serialRenderObjects.end(); obj++) if (*obj == object) { serialRenderObjects.erase(obj); break; }
}

void GameState::clearAllObjects() {
	serialObjects.clear();
	serialRenderObjects.clear();
}

std::vector<Object*>* GameState::getSerialObjects() {
	return &serialObjects;
}

std::vector<Object*>* GameState::getSerialRenderObjects() {
	return &serialRenderObjects;
}
