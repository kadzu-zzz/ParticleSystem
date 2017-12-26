#include "Game.h"

#include "ParticleSystemTestState.h"

Game::Game() {
}

Game::~Game() {
}

void Game::initialise() {
	particleSystemTestState = new ParticleSystemTestState();

	particleSystemTestState->initialise();

	currentState = particleSystemTestState;
}

GameState * Game::getGameState() {
	return currentState;
}

void Game::setGameState(GameState * state) {
	currentState = state;
}
