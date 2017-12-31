#include "ParticleSystem.h"

#include "TaskMaster.h"
#include "RenderingEngine.h"

ParticleSystem::ParticleSystem() : Object(true, true) {
	Render.intialise(TextureAsset::getTexture("arrow.png"), 0, 0, 0.5f, 0, 0, 1.0f, 1.0f, 0.0f, Colour(255, 255, 255, 255));
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::AddEmitter(ParticleEmitter emitter) {
	Emitters.push_back(emitter);
}

void ParticleSystem::update(float deltaSeconds) {
	if (Emitters.size() > 1) {
		//Multithreading masses of trig operations does give a reasonable speed increase ~(10% with 10K particles using trig) without any noticiable synchronization issues. The speed increase is more negligible when using purely linear particles.
		for (unsigned int i = 0; i < Emitters.size(); i++) {
			TaskMaster::addTask(MakeTask(std::bind(&ParticleEmitter::update, &Emitters[i], deltaSeconds)));
		}
	} else {
		for (ParticleEmitter& emitter : Emitters) {
			emitter.update(deltaSeconds);
		}
	}
}

void ParticleSystem::sendRenderingInformation(RenderingEngine * renderer) {
	RenderGlyphs.resize(0);
	if (Emitters.size() > 1) {
		unsigned int ParticleCount = 0;
		for (unsigned int i = 0; i < Emitters.size(); i++) {
			ParticleCount += Emitters[i].GetParticleCount();
		}

		RenderGlyphs.resize(ParticleCount * 2);
		ParticleCount = 0;

		for (unsigned int i = 0; i < Emitters.size(); i++) {
			Emitters[i].giveRenderGlyphs(Render, &RenderGlyphs, ParticleCount * 2);
			ParticleCount += Emitters[i].GetParticleCount();
		}
		renderer->getRenderer()->add(RenderGlyphs);
	} else {
		RenderGlyphs.resize(Emitters[0].GetParticleCount() * 2);

		Emitters[0].giveRenderGlyphs(Render, &RenderGlyphs, 0);
		
		renderer->getRenderer()->add(RenderGlyphs);
	}	
}

void ParticleSystem::SetOffset(float x, float y) {
	for (ParticleEmitter& emitter : Emitters) {
		emitter.SetEmitterPosition(x, y);
	}
}
