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

	Particle PrototypeParticle = Particle(0, 0, 0, 0.25, 0.25, Colour(100, 0, 0, 255), 8.0f);
	PrototypeParticle.xVelocity = 0.0f;
	PrototypeParticle.yVelocity = 0.81f;
	PrototypeParticle.radialAcceleration = -3.81f;
	PrototypeParticle.endColour = Colour(0, 0, 0, 255);

	ParticleEmitter TestEmitter = ParticleEmitter(PrototypeParticle, 200.0f);
	TestEmitter.SetVariableLifeSpan(2.5f);
	TestEmitter.SetVariableSpawn(40.0f, 40.0f);
	//TestEmitter.SetVariableVelocity(0.4f, 0.3f);
	TestEmitter.SetVariableSizeSpawn(0.1f, 0.1f);
	//TestEmitter.SetVariableRadial(0.0f, 4.0f);
	//TestEmitter.SetVariableTangential(0.0f, 1.0f);
	TestEmitter.SetTexture(TextureAsset::getTexture("particle.png"));

	Particle PrototypeParticle2 = Particle(0, 0, 0, 0.25, 0.25, Colour(100, 100, 0, 255), 4.0f);
	//PrototypeParticle2.xVelocity = 0.0f;
	//PrototypeParticle2.yVelocity = 0.71f;
	PrototypeParticle2.radialAcceleration  = 0.3f;
	PrototypeParticle2.tangentialAcceleration = 0.35f;
	PrototypeParticle2.endColour = Colour(0, 0, 0, 255);

	ParticleEmitter TestEmitter2 = ParticleEmitter(PrototypeParticle2, 100.0f);
	TestEmitter2.SetVariableLifeSpan(2.5f);
	TestEmitter2.SetVariableSpawn(0.5125f, 0.60f);
	TestEmitter2.SetVariableVelocity(0.3f, 0.25f);
	TestEmitter2.SetVariableRadial(0.0f, 0.30f);
	TestEmitter2.SetVariableTangential(0.0f, 0.31f);
	TestEmitter2.SetTexture(TextureAsset::getTexture("particle.png"));

	TestSystem.AddEmitter(TestEmitter2);
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));
	TestSystem.AddEmitter(ParticleEmitter(TestEmitter2));

	TestSystem.AddEmitter(TestEmitter);

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
