#include "ParticleSystemTestState.h"

#include "RenderingEngine.h"
#include "GenericShaderObject.h"
#include "Constants.h"
#include "InputManager.h"

ParticleSystemTestState::ParticleSystemTestState() {
}


ParticleSystemTestState::~ParticleSystemTestState() {
}

void ParticleSystemTestState::initialise() {
	camera.initialise(Unit().setAsPixel(VIDEO_OUTPUT_WIDTH_DEFAULT), Unit().setAsPixel(VIDEO_OUTPUT_HEIGHT_DEFAULT));

	SystemID = 3;

	if (SystemID == 0) {
		Particle HyperSpaceParticle = Particle(0, 0, 0, 0.25f, 0.25f, Colour(100, 0, 0, 255), 8.0f);
		HyperSpaceParticle.xVelocity = 0.0f;
		HyperSpaceParticle.yVelocity = 0.81f;
		HyperSpaceParticle.radialAcceleration = -3.81f;
		HyperSpaceParticle.endColour = Colour(0, 0, 0, 255);

		ParticleEmitter HyperSpaceEmitter = ParticleEmitter(HyperSpaceParticle, 200.0f);
		HyperSpaceEmitter.SetVariableLifeSpan(2.5f);
		HyperSpaceEmitter.SetVariableSpawn(40.0f, 40.0f);
		HyperSpaceEmitter.SetVariableSizeSpawn(0.1f, 0.1f);
		HyperSpaceEmitter.SetVariableRadial(0.0f, 4.0f);
		HyperSpaceEmitter.SetTexture(TextureAsset::getTexture("particle.png"));

		TestSystem.AddEmitter(HyperSpaceEmitter);

		Particle SwirlParticle = Particle(0, 0, 0, 0.1f, 0.1f, Colour(50, 50, 50, 100), 5.0f);
		SwirlParticle.endColour = Colour(0, 0, 0, 255);
		SwirlParticle.widthVelocity = 0.09f;
		SwirlParticle.heightVelocity = 0.09f;
		SwirlParticle.tangentialAcceleration = 0.3f;
		SwirlParticle.radialAcceleration = 0.3f;

		ParticleEmitter SwirlEmitter = ParticleEmitter(SwirlParticle, 200.0f);
		SwirlEmitter.SetVariableSpawn(0.25f, 0.25f);
		SwirlEmitter.SetVariableVelocity(0.3f, 0.25f);
		SwirlEmitter.SetVariableColour(Colour(200, 200, 200, 0), Colour(0, 0, 0, 0));
		SwirlEmitter.SetVariableRadial(0.0f, 0.25f);
		SwirlEmitter.SetVariableTangential(0.0f, 0.25f);
		SwirlEmitter.SetVariableSizeVelocity(0.03f, 0.03f);
		SwirlEmitter.SetTexture(TextureAsset::getTexture("particle.png"));

		TestSystem.AddEmitter(SwirlEmitter);
	} else if (SystemID == 1) {
		Particle FireParticle = Particle(0, 0, 0, 0.25f, 0.25f, Colour(150, 20, 0, 255), 3.2f);
		FireParticle.xAcceleration = 0.0f;
		FireParticle.yAcceleration = 0.4f;
		FireParticle.yVelocity = 0.25f;

		FireParticle.widthAcceleration = -0.02f;
		FireParticle.heightAcceleration = -0.02f;
		FireParticle.endColour = Colour(0, 0, 0, 0);
		FireParticle.radialAcceleration = -0.1f;

		ParticleEmitter FireEmitter = ParticleEmitter(FireParticle, 150.0f);
		FireEmitter.SetVariableLifeSpan(1.0f);
		FireEmitter.SetVariableColour(Colour(75, 0, 0, 0), Colour(0, 0, 0, 0));
		FireEmitter.SetVariableSpawn(0.25f, 0.0f);
		FireEmitter.SetVariableVelocity(0, 0.1f);
		FireEmitter.SetVariableAcceleration(0.42f, 0.2f);
		FireEmitter.SetVariableSizeSpawn(0.05f, 0.05f);
		FireEmitter.SetVariableTangential(0.0f, 0.2f);
		FireEmitter.SetVariableSizeAcceleration(0.01f, 0.01f);

		FireEmitter.SetTexture(TextureAsset::getTexture("particle.png"));

		Particle SmokeParticle = Particle(0, 1.0f, 0, 0.45f, 0.45f, Colour(100, 100, 100, 100), 4.0f);
		SmokeParticle.endColour = Colour(0, 0, 0, 0);
		SmokeParticle.yVelocity = 1.0f;
		SmokeParticle.yAcceleration = 0.25f;
		SmokeParticle.radialAcceleration = 0.1f;
		SmokeParticle.widthAcceleration = 0.1f;
		SmokeParticle.heightAcceleration = 0.1f;
		SmokeParticle.depth = 0.6f;
		
		ParticleEmitter SmokeEmitter = ParticleEmitter(SmokeParticle, 45.0f);
		SmokeEmitter.SetVariableColour(Colour(0, 0, 0, 0), Colour(0, 0, 0, 0));
		SmokeEmitter.SetVariableSpawn(0.75f, 0.25f);
		SmokeEmitter.SetVariableTangential(0.0f, 0.4f);
		SmokeEmitter.SetVariableSizeAcceleration(0.01f, 0.01f);
		SmokeEmitter.SetVariableSizeSpawn(0.05f, 0.05f);
		SmokeEmitter.SetVariableSizeAcceleration(0.15f, 0.15f);



		TestSystem.AddEmitter(FireEmitter);
		TestSystem.AddEmitter(SmokeEmitter);
	} else if (SystemID == 2) {
		Particle SnowflakeParticle = Particle(0, 0, 0, 0.25f, 0.25f, Colour(255, 255, 255, 255), 9.0f);
		SnowflakeParticle.yVelocity = -1.5f;
		SnowflakeParticle.endColour = Colour(100, 100, 100, 100);

		ParticleEmitter SnowflakeEmitter = ParticleEmitter(SnowflakeParticle, 125.0f);
		SnowflakeEmitter.SetVariableColour(Colour(0, 0, 0, 0), Colour(0, 0, 0, 0));
		SnowflakeEmitter.SetVariableSizeAcceleration(0.01f, 0.01f);
		SnowflakeEmitter.SetVariableSpawn(12.0, 0);
		SnowflakeEmitter.SetVariableTangential(0.0f, 0.10f);
		SnowflakeEmitter.SetVariableVelocity(0, 0, 0.25f);
		SnowflakeEmitter.SetVariableAcceleration(0.03f, 0, 0.51f);
		SnowflakeEmitter.SetVariableSizeSpawn(0.2f, 0.2f);
		SnowflakeEmitter.SetTexture(TextureAsset::getTexture("particle_snowflake.png"));

		SnowflakeEmitter.SetEmitterPosition(0, 5);

		TestSystem.AddEmitter(SnowflakeEmitter);
	} else if (SystemID == 3) {
		Particle RainParticle = Particle(0, 0, -0.25f, 0.15f, 0.15f, Colour(255, 255, 255, 255), 4.0f);
		RainParticle.yVelocity = -4.5f;
		RainParticle.xVelocity = -0.5f;
		RainParticle.endColour = Colour(0, 0, 0, 0);

		ParticleEmitter RainEmitter = ParticleEmitter(RainParticle, 500.0f);
		RainEmitter.SetVariableColour(Colour(0, 0, 0, 0), Colour(0, 0, 0, 0));
		RainEmitter.SetVariableSpawn(12.0, 0);
		RainEmitter.SetVariableVelocity(0, 1.0f);
		RainEmitter.SetTexture(TextureAsset::getTexture("particle_rain.png"));

		RainEmitter.SetEmitterPosition(0, 5);

		TestSystem.AddEmitter(RainEmitter);
	}

	registerObject(&TestSystem);
}


void ParticleSystemTestState::processPhysics(float deltaTime) {
}


void ParticleSystemTestState::serialUpdate(float deltaTime) {
	camera.update(deltaTime);


	auto MouseLoc = InputManager::getMouseLocation();
	auto Pos = camera.convertScreenToWorld(Unit().setAsPixel(MouseLoc.x), Unit().setAsPixel(MouseLoc.y));
	if (SystemID == 0) {
		TestSystem.SetOffset(Pos[0].meter, Pos[1].meter);
	}
}

void ParticleSystemTestState::postSerialUpdate(float deltaTime) {
}

void ParticleSystemTestState::adjustRenderEngineSettings(RenderingEngine * engine) {
	engine->shaderObject->updateShader(GenericShaderObjectUniform(&(camera.getMatrix()), false, 0));
}

OrthographicCamera * ParticleSystemTestState::getCamera() {
	return &camera;
}
