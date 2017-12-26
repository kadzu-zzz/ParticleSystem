#pragma once

#include "Object.h"
#include <SDL2\SDL.h>
#include <vector>

class RenderingEngine;
class OrthographicCamera;

class GameState {
public:
	GameState();
	~GameState();

	virtual void initialise() = 0;

	virtual void processEvent(SDL_Event e);
	virtual void processPhysics(float deltaTime) = 0;
	virtual void serialUpdate(float deltaTime) = 0;
	virtual void serialRender(RenderingEngine* engine);
	virtual void adjustRenderEngineSettings(RenderingEngine* engine) = 0;

	virtual void OnChangeTo();
	virtual void OnChangeAway();

	void registerObject(Object* object);
	void deleteObject(Object* object);
	void clearAllObjects();

	virtual OrthographicCamera* getCamera() = 0;

	std::vector<Object*>* getSerialObjects();
	std::vector<Object*>* getSerialRenderObjects();
protected:
	std::vector<Object*> serialObjects;
	std::vector<Object*> serialRenderObjects;
};

