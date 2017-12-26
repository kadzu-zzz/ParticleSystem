#include "Object.h"



Object::Object(bool hasUpdate, bool hasRenderInformation): bUpdate(hasUpdate), bRenderInformation(hasRenderInformation) {
}

Object::~Object() {
}

void Object::update(float deltaSeconds) {
}

void Object::sendRenderingInformation(RenderingEngine * renderer) {
}

const bool Object::hasSerialUpdate() {
	return bUpdate;
}

const bool Object::hasRenderInformation() {
	return bRenderInformation;
}
