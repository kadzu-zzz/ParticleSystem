#pragma once

#include "Unit.h"
#include "AABB.h"

#include <glm\glm.hpp>
#include <array>

__declspec(align(16))
class OrthographicCamera {
public:
	OrthographicCamera();
	~OrthographicCamera();

	void initialise(Unit screenWidth, Unit screenHeight);

	void setPosition(Unit x, Unit y);
	void setPositionTarget(Unit x, Unit y);
	void setPositionLerpPercentage(float percentage);

	void setBounds(Unit width, Unit height);
	void setBoundsTarget(Unit width, Unit height);
	void setBoundsLerpPercentage(float percentage);

	void setScale(float scale);
	void setScaleTarget(float scale);
	void setScaleLerpPercentage(float percentage);

	Unit getX();
	Unit getY();
	Unit getWidth();
	Unit getHeight();
	float getScale();

	Unit getTargetX();
	Unit getTargetY();
	Unit getTargetWidth();
	Unit getTargetHeight();
	float getTargetScale();

	std::array<Unit, 2> convertScreenToWorld(Unit screenX, Unit screenY);
	std::array<Unit, 2> convertWorldToScreen(Unit worldX, Unit worldY);

	AABB getCameraBounds(Unit extraPadding);

	glm::mat4 getMatrix();

	void update(float deltaTime);

	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
private:

	std::array<Unit, 2> position;
	std::array<Unit, 2> targetPosition;
	std::array<Unit, 2> bounds;
	std::array<Unit, 2> targetBounds;

	float scale;
	float scaleTarget;

	float movementLerpPercentage;
	float boundsLerpPercentage;
	float scaleLerpPercentage;

	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;

	bool bNeedsUpdate;

	void updateMatrix();
};

