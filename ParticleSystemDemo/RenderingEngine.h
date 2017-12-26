#pragma once

#include "VBOBatcher.h"
#include "Window.h"

#include "GenericShaderObject.h"

class RenderingEngine {
public:
	RenderingEngine();
	~RenderingEngine();

	static void InitWindow();

	virtual void initialise();
	virtual void render();

	GenericShaderObject* shaderObject;

	VBOBatcher* getRenderer();
	VBOBatcher* getGUIRenderer();
	Window getWindow();
protected:
	VBOBatcher renderer;
	VBOBatcher GUIRenderer;
	static Window window;
};

