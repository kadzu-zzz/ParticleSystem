#pragma once

class RenderingEngine;
class VBOBatcher;
class Object;

class RenderContainer {
public:
	RenderContainer();
	~RenderContainer();

	void sendRenderInformationEngine(RenderingEngine* engine);

	virtual void sendRenderInformation(VBOBatcher* batcher) = 0;

	void ownParent(Object* parent);
protected:
	Object* parent;
};

