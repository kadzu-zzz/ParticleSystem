#pragma once

#include "Colour.h"

struct Particle {
	Particle() : x(0.0f), y(0.0f), rot(0.0f), width(0.0f), height(0.0f), lifeSpan(0.0f), xVelocity(0.0f), yVelocity(0.0f), rotVelocity(0.0f) {};
	Particle(float x, float y, float rot, float width, float height, Colour colour, float lifeSpan) : x(x), y(y), rot(rot), width(width), height(height), 
		lifeSpan(lifeSpan), startLifeSpan(lifeSpan), startColour(colour), xVelocity(0.0f), yVelocity(0.0f), rotVelocity(0.0f), xAcceleration(0.0f), yAcceleration(0.0f), rotAcceleration(0.0f), widthVelocity(0.0f), heightVelocity(0.0f), widthAcceleration(0.0f), heightAcceleration(0.0f), tangentialVelocity(0.0f), tangentialAcceleration(0.0f), radialVelocity(0.0f), radialAcceleration(0.0f) {}

	float x, y, rot;
	float width, height;
	Colour startColour, endColour;
	float lifeSpan, startLifeSpan;

	float xVelocity, yVelocity, rotVelocity;
	float xAcceleration, yAcceleration, rotAcceleration;

	float widthVelocity, heightVelocity;
	float widthAcceleration, heightAcceleration;

	float tangentialVelocity, tangentialAcceleration;
	float radialVelocity, radialAcceleration;

	bool bSizeAcceleration, bSizeVelocity;
	bool bLinearAcceleration, bLinearVelocity;
	bool bOrbitalAcceleration, bOrbitalVelocity;

	void InitialiseUpdateBools() {
		bSizeAcceleration = (widthAcceleration != 0.0f || heightAcceleration != 0.0f);
		bSizeVelocity = bSizeAcceleration || (widthVelocity != 0.0f || heightVelocity != 0.0f);
		bLinearAcceleration = (xAcceleration != 0.0f || yAcceleration != 0.0f || rotAcceleration != 0.0f);
		bLinearVelocity = bLinearAcceleration || (xVelocity != 0.0f || yVelocity != 0.0f || rotVelocity != 0.0f);
		bOrbitalAcceleration = (tangentialAcceleration != 0.0f || radialAcceleration != 0.0f);
		bOrbitalVelocity = bOrbitalAcceleration || (tangentialVelocity != 0.0f || radialVelocity != 0.0f);
	}

	void SetLifeSpawn(float LifeSpan) {
		lifeSpan = LifeSpan;
		startLifeSpan = LifeSpan;
	}

	void SetColour(Colour C) {
		startColour = C;
	}

	Particle copy() {
		return Particle(*this);
	}
};