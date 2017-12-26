#pragma once


class TaskMaster;
class Logger;
class Game;
class Object;
class RenderingEngine;
class GameState;

#define StaticEngine Engine::engine
#define StaticGame Engine::engine.getGame()
#define StaticLogger Engine::engine.getLogger()
#define StaticRenderingEngine Engine::engine.getRenderingEngine()
class Engine {
public:
	static Engine engine;

	Engine();
	~Engine();

	void intialise();
	void run();
	void stop();

	Game* getGame();
	Logger* getLogger();
	RenderingEngine* getRenderingEngine();
protected:
	Game* game;
	GameState* oldState;
	RenderingEngine* deafultRenderingEngine;
	Logger* logger;

	bool bRunning;
	void engineLoop();
};

