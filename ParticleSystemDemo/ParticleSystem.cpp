#include "ParticleSystem.h"



ParticleSystem::ParticleSystem() : Object(true, true) {
	Render.intialise(TextureAsset::getTexture("arrow.png"), 0, 0, 0.5f, 0, 0, 1.0f, 1.0f, 0.0f, Colour(255, 255, 255, 255));
}


ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::AddEmitter(ParticleEmitter emitter) {
	Emitters.push_back(emitter);
}

#include "TaskMaster.h"

void ParticleSystem::update(float deltaSeconds) {
	if (Emitters.size() > 1) {
		for (int i = 1; i < Emitters.size(); i++) {
			TaskMaster::addTask(MakeTask(std::bind(&ParticleEmitter::update, &Emitters[i], deltaSeconds)));
		}
		//update emitter0 on the main thread and continue, mabye move it off when theres more stuff happening in the enviroment (
		// Basically we don't want to waste the main threads processing power.
		//)
		Emitters[0].update(deltaSeconds);
	} else {
		for (ParticleEmitter& emitter : Emitters) {
			emitter.update(deltaSeconds);
		}
	}
}

void ParticleSystem::sendRenderingInformation(RenderingEngine * renderer) {
	for (ParticleEmitter& emitter : Emitters) {
		emitter.render(Render, renderer);
	}
}

void ParticleSystem::SetOffset(float x, float y) {
	for (ParticleEmitter& emitter : Emitters) {
		emitter.SetEmitterPosition(x, y);
	}
}
