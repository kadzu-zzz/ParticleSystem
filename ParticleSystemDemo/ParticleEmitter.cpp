#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(Particle Prototype, float SpawnsPerSecond) : OffsetX(0.0f), OffsetY(0.0f), Prototype(Prototype), SpawnTimer(0.0f), SpawnPerSecondInverse(1.0f / SpawnsPerSecond), Texture(nullptr, "", ""), 
VariableXSpawn(0.0f), VariableYSpawn(0.0f), VariableXVelocity(0.0f), VariableYVelocity(0.0f), VariableXAcceleration(0.0f), VariableYAcceleration(0.0f),
VariableWidthSpawn(0.0f), VariableHeightSpawn(0.0f), VariableWidthVelocity(0.0f), VariableHeightVelocity(0.0f), VariableWidthAcceleration(0.0f), VariableHeightAcceleration(0.0f),
VariableLifeSpan(0.0f), VariableRotSpawn(0.0f), VariableRotVelocity(0.0f), VariableRotAcceleration(0.0f),
VariableTangentialVelocity(0.0f), VariableTangentialAcceleration(0.0f), VariableRadialVelocity(0.0f), VariableRadialAcceleration(0.0f)
{
}


ParticleEmitter::~ParticleEmitter() {
}

void ParticleEmitter::update(float deltaTime) {
	SpawnTimer -= deltaTime;
	while (SpawnTimer < 0.0f) {
		if (SpawnFunction) {
			Particles.push_back(SpawnFunction(this));
		} else {
			Particles.push_back(Prototype.copy());
			
			Particles.back().x += OffsetX;
			Particles.back().y += OffsetY;

			if (VariableLifeSpan != 0.0f)
				Particles.back().SetLifeSpawn(Particles.back().lifeSpan + GetVariableValue(VariableLifeSpan));

			//Linear Motion
			if(VariableXSpawn != 0.0f)
				Particles.back().x += GetVariableValue(VariableXSpawn);
			if (VariableYSpawn != 0.0f)
				Particles.back().y += GetVariableValue(VariableYSpawn);
			if (VariableXVelocity != 0.0f)
				Particles.back().xVelocity += GetVariableValue(VariableXVelocity);
			if (VariableYVelocity != 0.0f)
				Particles.back().yVelocity += GetVariableValue(VariableYVelocity);
			if (VariableXAcceleration != 0.0f)
				Particles.back().xAcceleration += GetVariableValue(VariableXAcceleration);
			if (VariableYAcceleration != 0.0f)
				Particles.back().yAcceleration += GetVariableValue(VariableYAcceleration);
			//Size Motion
			if (VariableWidthSpawn != 0.0f)
				Particles.back().width += GetVariableValue(VariableWidthSpawn);
			if (VariableHeightVelocity != 0.0f)
				Particles.back().height += GetVariableValue(VariableHeightVelocity);
			if (VariableWidthVelocity != 0.0f)
				Particles.back().widthVelocity += GetVariableValue(VariableWidthVelocity);
			if (VariableHeightVelocity != 0.0f)
				Particles.back().heightVelocity += GetVariableValue(VariableHeightVelocity);
			if (VariableWidthAcceleration != 0.0f)
				Particles.back().widthAcceleration += GetVariableValue(VariableWidthAcceleration);
			if (VariableHeightAcceleration != 0.0f)
				Particles.back().heightAcceleration += GetVariableValue(VariableHeightAcceleration);

			//Rotational Motion
			if (VariableRotSpawn != 0.0f)
				Particles.back().rot += GetVariableValue(VariableRotSpawn);
			if (VariableRotVelocity != 0.0f)
				Particles.back().rotVelocity += GetVariableValue(VariableRotVelocity);
			if (VariableRotAcceleration != 0.0f)
				Particles.back().rotAcceleration += GetVariableValue(VariableRotAcceleration);

			//Orbiting Motion
			if (VariableTangentialVelocity != 0.0f)
				Particles.back().tangentialVelocity += GetVariableValue(VariableTangentialVelocity);
			if (VariableTangentialAcceleration != 0.0f)
				Particles.back().tangentialAcceleration += GetVariableValue(VariableTangentialAcceleration);
			if (VariableRadialVelocity != 0.0f)
				Particles.back().radialVelocity += GetVariableValue(VariableRadialVelocity);
			if (VariableRadialAcceleration != 0.0f)
				Particles.back().radialAcceleration += GetVariableValue(VariableRadialAcceleration);

			Particles.back().startColour += Colour(static_cast<GLubyte>(GetVariableValue(VariableColourSpawn.r)),
												   static_cast<GLubyte>(GetVariableValue(VariableColourSpawn.g)),
												   static_cast<GLubyte>(GetVariableValue(VariableColourSpawn.b)),
												   static_cast<GLubyte>(GetVariableValue(VariableColourSpawn.a)));
		}
		Particles.back().InitialiseUpdateBools();

		SpawnTimer += SpawnPerSecondInverse;
	}
	if (UpdateFunction) {
		for (unsigned int i = 0; i < Particles.size(); i++) {
			UpdateFunction(&Particles[i], this);
		}
	} else {
		for (unsigned int i = 0; i < Particles.size(); i++) {

			Particles[i].lifeSpan -= deltaTime;

			if (Particles[i].bLinearAcceleration) {
				Particles[i].xVelocity += Particles[i].xAcceleration * deltaTime;
				Particles[i].yVelocity += Particles[i].yAcceleration * deltaTime;
				Particles[i].rotVelocity += Particles[i].rotAcceleration * deltaTime;
			}
			if (Particles[i].bLinearVelocity) {
				Particles[i].x += Particles[i].xVelocity * deltaTime;
				Particles[i].y += Particles[i].yVelocity * deltaTime;
				Particles[i].rot += Particles[i].rotVelocity * deltaTime;
			}
			if (Particles[i].bSizeAcceleration) {
				Particles[i].widthVelocity += Particles[i].widthAcceleration * deltaTime;
				Particles[i].heightVelocity += Particles[i].heightAcceleration * deltaTime;
			}
			if (Particles[i].bSizeVelocity) {
				Particles[i].width += Particles[i].widthVelocity * deltaTime;
				Particles[i].height += Particles[i].heightVelocity * deltaTime;
			}
			if (Particles[i].bOrbitalAcceleration) {
				Particles[i].tangentialVelocity += Particles[i].tangentialAcceleration * deltaTime;
				Particles[i].radialVelocity += Particles[i].radialAcceleration * deltaTime;
			}
			if (Particles[i].bOrbitalVelocity) {
				float XDifference = OffsetX - Particles[i].x;
				float YDifference = OffsetY - Particles[i].y;

				float RadialDir = std::atan2f(Particles[i].y - OffsetY, Particles[i].x - OffsetX);
				float TangentialDir = RadialDir + 1.5708f;

				Particles[i].x += (Particles[i].tangentialVelocity != 0.0f ? (std::cos(TangentialDir) * Particles[i].tangentialVelocity * deltaTime) : 0.0f) +
					(Particles[i].radialVelocity != 0.0f ? (std::cos(RadialDir) * Particles[i].radialVelocity * deltaTime) : 0.0f);
				Particles[i].y += (Particles[i].tangentialVelocity != 0.0f ? (std::sin(TangentialDir) * Particles[i].tangentialVelocity * deltaTime) : 0.0f) +
					(Particles[i].radialVelocity != 0.0f ? (std::sin(RadialDir) * Particles[i].radialVelocity * deltaTime) : 0.0f);

			}

			if (Particles[i].lifeSpan <= 0.0f) {
				if (i != Particles.size()) {
					Particles[i] = Particles.back();
					--i;
				}
				Particles.pop_back();
			}
		}
	}
}

void ParticleEmitter::giveRenderGlyphs(Rectangle Renderable, std::vector<TriangleGlyph>* Glyphs, unsigned int offset) {
	Renderable.setTexture(Texture);
	std::array<TriangleGlyph, 2> Glyph = {};
	for (unsigned int i = 0; i < Particles.size(); i++) {
		Renderable.setCenter(Particles[i].x, Particles[i].y);
		Renderable.setSize(Particles[i].width, Particles[i].height);
		Renderable.setRotation(Particles[i].rot);

		Renderable.setColour(Particles[i].startColour.lerp(Particles[i].endColour, (1.0f - (Particles[i].lifeSpan / Particles[i].startLifeSpan))));

		Glyph = Renderable.getRenderGlyphs();
		(*Glyphs)[offset++] = Glyph[0];
		(*Glyphs)[offset++] = Glyph[1];
	}
}

void ParticleEmitter::SetVariableLifeSpan(float VLifeSpan) {
	VariableLifeSpan = VLifeSpan;
}

void ParticleEmitter::SetVariableSpawn(float VX, float VY, float VRot) {
	VariableXSpawn = VX;
	VariableYSpawn = VY;
	VariableRotSpawn = VRot;
}

void ParticleEmitter::SetVariableVelocity(float VVelX, float VVelY, float VVelRot) {
	VariableXVelocity = VVelX;
	VariableYVelocity = VVelY;
	VariableRotVelocity = VVelRot;
}

void ParticleEmitter::SetVariableAcceleration(float VAccelX, float VAccelY, float VAccelRot) {
	VariableXAcceleration = VAccelX;
	VariableYAcceleration = VAccelY;
	VariableRotAcceleration = VAccelRot;
}

void ParticleEmitter::SetVariableSizeSpawn(float VWidth, float VHeight) {
	VariableWidthSpawn = VWidth;
	VariableHeightSpawn = VHeight;
}

void ParticleEmitter::SetVariableSizeVelocity(float VVelWidth, float VVelHeight) {
	VariableWidthVelocity = VVelWidth;
	VariableHeightVelocity = VVelHeight;
}

void ParticleEmitter::SetVariableSizeAcceleration(float VAccelWidth, float VAccelHeight) {
	VariableWidthAcceleration = VAccelWidth;
	VariableHeightAcceleration = VAccelHeight;
}

void ParticleEmitter::SetVariableColour(Colour VColourSpawn, Colour VColourEnd) {
	VariableColourSpawn = VColourSpawn;
	VariableColourEnd = VColourEnd;
}

void ParticleEmitter::SetVariableTangential(float VVelTang, float VAccelTang) {
	VariableTangentialVelocity = VVelTang;
	VariableTangentialAcceleration = VAccelTang;
}

void ParticleEmitter::SetVariableRadial(float VVelRadial, float VAccelRadial) {
	VariableRadialVelocity = VVelRadial;
	VariableRadialAcceleration = VAccelRadial;
}

float ParticleEmitter::GetVariableLifeSpan() {
	return VariableLifeSpan;
}

std::array<float, 3> ParticleEmitter::GetVariableSpawn() {
	return { VariableXSpawn, VariableYSpawn, VariableRotSpawn };
}

std::array<float, 3> ParticleEmitter::GetVariableVelocity() {
	return { VariableXVelocity, VariableYVelocity, VariableRotVelocity };
}

std::array<float, 3> ParticleEmitter::GetVariableAcceleration() {
	return { VariableXAcceleration, VariableYAcceleration, VariableRotAcceleration };
}

std::array<float, 2> ParticleEmitter::GetVariableSizeSpawn() {
	return { VariableWidthSpawn, VariableHeightSpawn };
}

std::array<float, 2> ParticleEmitter::GetVariableSizeVelocity() {
	return { VariableWidthVelocity, VariableHeightVelocity };
}

std::array<float, 2> ParticleEmitter::GetVariableSizeAcceleration() {
	return { VariableWidthAcceleration, VariableHeightAcceleration };
}

std::array<Colour, 2> ParticleEmitter::GetVariableColour() {
	return { VariableColourSpawn, VariableColourEnd };
}

std::array<float, 2> ParticleEmitter::GetVariableTangential() {
	return { VariableTangentialVelocity, VariableTangentialAcceleration };
}

std::array<float, 2> ParticleEmitter::GetVariableRadial() {
	return { VariableRadialVelocity, VariableRadialAcceleration };
}

void ParticleEmitter::SetEmitterPosition(float X, float Y) {
	OffsetX = X;
	OffsetY = Y;
}

std::array<float, 2> ParticleEmitter::GetEmitterPosition() {
	return{ OffsetX, OffsetY };
}

void ParticleEmitter::SetPrototype(Particle p) {
	Prototype = p;
}

Particle * ParticleEmitter::GetPrototype() {
	return &Prototype;
}

void ParticleEmitter::SetTexture(TextureResource tex) {
	Texture = tex;
}

TextureResource ParticleEmitter::GetTexture() {
	return Texture;
}

void ParticleEmitter::SetSpawnsPerSecond(float SpawnsPerSecond) {
	SpawnPerSecondInverse = (1.0f / SpawnsPerSecond);
}

float ParticleEmitter::GetSpawnPerSecond() {
	return 1.0f / SpawnPerSecondInverse;
}

unsigned int ParticleEmitter::GetParticleCount() {
	return Particles.size();
}

void ParticleEmitter::SetCustomSpawnFunction(std::function<Particle(ParticleEmitter*)> SpawnFunction) {
	this->SpawnFunction = SpawnFunction;
}

bool ParticleEmitter::HasCustomSpawnFunction() {
	return SpawnFunction.operator bool();
}

void ParticleEmitter::ClearCustomSpawnFunction() {
	SpawnFunction = nullptr;
}

void ParticleEmitter::SetUpdateFunctionFunction(std::function<Particle(ParticleEmitter*)> UpdateFunction) {
	this->UpdateFunction = UpdateFunction;
}

bool ParticleEmitter::HasUpdateFunctionFunction() {
	return UpdateFunction.operator bool();
}

void ParticleEmitter::ClearUpdateFunctionFunction() {
	UpdateFunction = nullptr;
}

inline float ParticleEmitter::GetVariableValue(float Variable) {
	return (-Variable / 2.0f) + ((Variable)* (((float)rand()) / RAND_MAX));
}
