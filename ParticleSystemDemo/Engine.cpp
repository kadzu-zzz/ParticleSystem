#include "Engine.h"

#include "RenderingEngine.h"
#include "Logger.h"
#include "InputManager.h"
#include "Constants.h"
#include "GateTimer.h"
#include "StopWatch.h"
#include "Game.h"
#include "GameState.h"
#include "TaskMaster.h"

Engine Engine::engine = Engine();

//If you're not windows, replace this with a create directory function from your operating system
#include <windows.h> //For CreateDirectory.
static void CreateDirectoryIfItDoesNotExist(std::string directory) {
	CreateDirectory(directory.c_str(), NULL);
}

Engine::Engine() : bRunning(false) {
}

Engine::~Engine() {
}

void Engine::intialise() {
	logger = new Logger();

	CreateDirectoryIfItDoesNotExist(ROOT_PATH);
	CreateDirectoryIfItDoesNotExist(TEXTURE_PATH);
	CreateDirectoryIfItDoesNotExist(SHADER_PATH);

	deafultRenderingEngine = new RenderingEngine();
	RenderingEngine::InitWindow();
	deafultRenderingEngine->initialise();

	game = new Game();
	game->initialise();

	TaskMaster::initialise(TaskMaster::getNumberOfThreads() / 2);
}

void Engine::run() {
	bRunning = true;
	engineLoop();
}

void Engine::stop() {
	bRunning = false;
}

Game * Engine::getGame() {
	return game;
}

Logger * Engine::getLogger() {
	return logger;
}

RenderingEngine * Engine::getRenderingEngine() {
	return deafultRenderingEngine;
}

const constexpr float loopCountRate() { return 10.0f; }

void Engine::engineLoop() {
	StopWatch physicsWatch = StopWatch();
	StopWatch concurrentWatch = StopWatch();
	StopWatch serialWatch = StopWatch();

	physicsWatch.update();
	concurrentWatch.update();
	serialWatch.update();

	int loopsPerSecond = 0;
	StopWatch loopsPerSecondWatch = StopWatch();
	GateTimer loopsPerSecondTimer = GateTimer();

	loopsPerSecondWatch.update();
	loopsPerSecondTimer.setLength(loopCountRate());
	
	while (bRunning) {
		GameState* state = game->getGameState();
		if (oldState != state) {
			if (oldState != nullptr) {
				oldState->OnChangeAway();
			}
			state->OnChangeTo();
			oldState = state;
		}

		//Events
		SDL_Event e;

		InputManager::update();
		if (SDL_PollEvent(&e) == 1) {
			do {
				state->processEvent(e);
				switch (e.type) {
					case SDL_QUIT:
						bRunning = false;
					case SDL_KEYDOWN:
						InputManager::updateKey(e.key.keysym.sym, true);
						break;
					case SDL_KEYUP:
						InputManager::updateKey(e.key.keysym.sym, false);
						break;
					case SDL_MOUSEBUTTONDOWN:
						InputManager::updateMouseButton(e.button.button, true);
						break;
					case SDL_MOUSEBUTTONUP:
						InputManager::updateMouseButton(e.button.button, false);
						break;
					case SDL_MOUSEWHEEL:
						InputManager::updateMouseWheel(e.wheel.y);
						break;
					default:
						break;
				}
			} while (SDL_PollEvent(&e) == 1);
		}
		//Physics
		physicsWatch.update();
		state->processPhysics(physicsWatch.getCurrentDeltaSecond());
		//Object Update
		serialWatch.update();
		float serialDeltaTime = serialWatch.getCurrentDeltaSecond();

		state->serialUpdate(serialDeltaTime);
		std::vector<Object*> serialObjects = *(state->getSerialObjects());
		if (serialObjects.size() > 0) {
			for (unsigned int i = 0; i < serialObjects.size(); i++) {
				if (serialObjects[i] != nullptr)
					serialObjects[i]->update(serialDeltaTime);
			}
		}
		state->postSerialUpdate(serialDeltaTime);
		while (TaskMaster::isDoingWork()) {
		//	std::this_thread::sleep_for(std::chrono::microseconds(1));
		};

		//Object Render
		std::vector<Object*> serialRenderObjects = *(state->getSerialRenderObjects());
		if (serialRenderObjects.size() > 0) {
			for (unsigned int i = 0; i < serialRenderObjects.size(); i++) {
				if (serialRenderObjects[i] != nullptr)
					serialRenderObjects[i]->sendRenderingInformation(deafultRenderingEngine);
			}
		}
		state->serialRender(deafultRenderingEngine);

		//Actually Render
		state->adjustRenderEngineSettings(deafultRenderingEngine);
		deafultRenderingEngine->render();

		//Loop Rate
		++loopsPerSecond;
		loopsPerSecondWatch.update();
		if (loopsPerSecondTimer.update(loopsPerSecondWatch.getCurrentDeltaSecond())) {
			logger->logMessage(LogLevel::INFO, "Loop Rate: " + std::to_string(loopsPerSecond / loopCountRate()) + " /sec.");
			loopsPerSecond = 0;
			loopsPerSecondTimer.setLength(loopCountRate());
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		//Output the log
		logger->outputLog();
	} 
}
