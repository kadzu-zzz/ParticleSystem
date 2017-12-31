#pragma once

#include "Particle.h"

#include "Rectangle.h"
#include "Texture.h"
#include "Glyph.h"

#include <functional>
#include <vector>
#include <array>

class ParticleEmitter {
public:
	ParticleEmitter(Particle Prototype, float SpawnsPerSecond);
	~ParticleEmitter();

	void update(float deltaTime);

	void giveRenderGlyphs(Rectangle Renderable, std::vector<TriangleGlyph>* Glyphs, unsigned int offset);

	void SetVariableLifeSpan(float VLifeSpan);
	void SetVariableSpawn(float VX, float VY, float VRot = 0.0f);
	void SetVariableVelocity(float VVelX, float VVelY, float VVelRot = 0.0f);
	void SetVariableAcceleration(float VAccelX, float VAccelY, float VAccelRot = 0.0f);
	void SetVariableSizeSpawn(float VWidth, float VHeight);
	void SetVariableSizeVelocity(float VVelWidth, float VVelHeight);
	void SetVariableSizeAcceleration(float VAccelWidth, float VAccelHeight);
	void SetVariableColour(Colour VColourSpawn, Colour VColourEnd);

	void SetVariableTangential(float VVelTang, float VAccelTang = 0.0f);
	void SetVariableRadial(float VVelRadial, float VAccelRadial = 0.0f);

	float GetVariableLifeSpan();
	std::array<float, 3> GetVariableSpawn();
	std::array<float, 3> GetVariableVelocity();
	std::array<float, 3> GetVariableAcceleration();
	std::array<float, 2> GetVariableSizeSpawn();
	std::array<float, 2> GetVariableSizeVelocity();
	std::array<float, 2> GetVariableSizeAcceleration();
	std::array<Colour, 2> GetVariableColour();

	std::array<float, 2> GetVariableTangential();
	std::array<float, 2> GetVariableRadial();

	void SetEmitterPosition(float X, float Y);
	std::array<float, 2> GetEmitterPosition();

	void SetPrototype(Particle p);
	Particle* GetPrototype();

	void SetTexture(TextureResource tex);
	TextureResource GetTexture();

	void SetSpawnsPerSecond(float SpawnsPerSecond);
	float GetSpawnPerSecond();

	unsigned int GetParticleCount();

	void SetCustomSpawnFunction(std::function<Particle(ParticleEmitter*)> SpawnFunction);
	bool HasCustomSpawnFunction();
	void ClearCustomSpawnFunction();

	void SetUpdateFunctionFunction(std::function<void(Particle*, ParticleEmitter*)> UpdateFunction);
	bool HasUpdateFunctionFunction();
	void ClearUpdateFunctionFunction();

	std::vector<Particle>* GetAllParticles();
protected:
	TextureResource Texture;
	Particle Prototype;
	
	std::vector<Particle> Particles;

	std::function<Particle(ParticleEmitter*)> SpawnFunction;
	std::function<void(Particle*, ParticleEmitter*)> UpdateFunction;

	float OffsetX, OffsetY;

	//Particle Spawning
	float SpawnTimer;
	float SpawnPerSecondInverse;

	//Particle Varience
	float VariableLifeSpan;
	float VariableXSpawn, VariableYSpawn, VariableRotSpawn;
	float VariableXVelocity, VariableYVelocity, VariableRotVelocity;
	float VariableXAcceleration, VariableYAcceleration, VariableRotAcceleration;
	float VariableWidthSpawn, VariableHeightSpawn;
	float VariableWidthVelocity, VariableHeightVelocity;
	float VariableWidthAcceleration, VariableHeightAcceleration;
	Colour VariableColourSpawn, VariableColourEnd;

	//Circular Movement
	float VariableTangentialVelocity, VariableTangentialAcceleration;
	float VariableRadialVelocity, VariableRadialAcceleration;

	inline float GetVariableValue(float Variable);
};

