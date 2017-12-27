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

	Particle HyperSpaceParticle = Particle(0, 0, 0, 0.25, 0.25, Colour(100, 0, 0, 255), 8.0f);
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

	Particle SwirlParticle = Particle(0, 0, 0, 0.1, 0.1, Colour(50,50, 50, 100), 5.0f);
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

	registerObject(&TestSystem);
}


void ParticleSystemTestState::processPhysics(float deltaTime) {
}


void ParticleSystemTestState::serialUpdate(float deltaTime) {
	camera.update(deltaTime);


	auto MouseLoc = InputManager::getMouseLocation();
	auto Pos = camera.convertScreenToWorld(Unit().setAsPixel(MouseLoc.x), Unit().setAsPixel(MouseLoc.y));
	TestSystem.SetOffset(Pos[0].meter, Pos[1].meter);
}

void ParticleSystemTestState::adjustRenderEngineSettings(RenderingEngine * engine) {
	engine->shaderObject->updateShader(GenericShaderObjectUniform(&(camera.getMatrix()), false, 0));
}

OrthographicCamera * ParticleSystemTestState::getCamera() {
	return &camera;
}
