#pragma once

#include <vector>

class RenderingEngine;

class Object {
public:
	Object(bool hasUpdate, bool hasRenderInformation);
	~Object();
	virtual void update(float deltaSeconds);
	virtual void sendRenderingInformation(RenderingEngine* renderer);

	const bool hasSerialUpdate();
	const bool hasRenderInformation();
private:
	const bool bUpdate;
	const bool bRenderInformation;
};