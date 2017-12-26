#pragma once

class GameState;

class ParticleSystemTestState;

class Game {
public:
	Game();
	~Game();

	void initialise();

	GameState* getGameState();
	void setGameState(GameState* state);

	ParticleSystemTestState* particleSystemTestState;
private:
	GameState* currentState;
};

