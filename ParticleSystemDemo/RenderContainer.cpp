#include "RenderContainer.h"

#include "RenderingEngine.h"
#include "Object.h"

RenderContainer::RenderContainer() {
}


RenderContainer::~RenderContainer() {
}

void RenderContainer::sendRenderInformationEngine(RenderingEngine * engine) {
	sendRenderInformation(engine->getRenderer());
}

void RenderContainer::ownParent(Object * parent) {
	this->parent = parent;
}
