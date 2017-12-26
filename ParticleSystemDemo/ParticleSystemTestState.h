#pragma once

#include "GameState.h"
#include "OrthographicCamera.h"

#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "Particle.h"

__declspec(align(16))
class ParticleSystemTestState : public GameState {
public:
	ParticleSystemTestState();
	~ParticleSystemTestState();

	void initialise() override;

	void processPhysics(float deltaTime) override;
	void serialUpdate(float deltaTime) override;
	void adjustRenderEngineSettings(RenderingEngine* engine) override;
	OrthographicCamera* getCamera() override;

	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }

protected:
	OrthographicCamera camera;

	ParticleSystem TestSystem;
};

