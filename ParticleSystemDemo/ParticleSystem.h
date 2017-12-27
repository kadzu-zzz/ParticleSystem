#pragma once

#include "Object.h"

#include "ParticleEmitter.h"
#include "Rectangle.h"

#include <vector>

class ParticleSystem : public Object {
public:
	ParticleSystem();
	~ParticleSystem();

	void AddEmitter(ParticleEmitter emitter);

	void update(float deltaSeconds) override;
	void sendRenderingInformation(RenderingEngine* renderer) override;

	void SetOffset(float x, float y);
protected:
	Rectangle Render;
	std::vector<ParticleEmitter> Emitters;

	std::vector<TriangleGlyph> RenderGlyphs;
};

