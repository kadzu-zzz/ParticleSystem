#include "OrthographicCamera.h"

#include "MathHelper.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera() {
}

OrthographicCamera::~OrthographicCamera() {
}

void OrthographicCamera::initialise(Unit screenWidth, Unit screenHeight) {
	bNeedsUpdate = true;

	position = { 0, 0 };
	bounds = { screenWidth, screenHeight };
	scale = 1.0f;
	targetPosition = position;
	targetBounds = bounds;
	scaleTarget = scale;

	movementLerpPercentage = 1.0f;
	boundsLerpPercentage = 1.0f;
	scaleLerpPercentage = 1.0f;
}

void OrthographicCamera::setPosition(Unit x, Unit y) {
	position = { x, y };
	targetPosition = position;
	bNeedsUpdate = true;
}

void OrthographicCamera::setPositionTarget(Unit x, Unit y) {
	targetPosition = { x, y };
	bNeedsUpdate = true;
}

void OrthographicCamera::setPositionLerpPercentage(float percentage) {
	movementLerpPercentage = percentage;
}

void OrthographicCamera::setBounds(Unit width, Unit height) {
	bounds = { width, height };
	targetBounds = bounds;
	bNeedsUpdate = true;
}

void OrthographicCamera::setBoundsTarget(Unit width, Unit height) {
	targetBounds = { width, height };
	bNeedsUpdate = true;
}

void OrthographicCamera::setBoundsLerpPercentage(float percentage) {
	boundsLerpPercentage = percentage;
}

void OrthographicCamera::setScale(float scale) {
	this->scale = scale;
	this->scaleTarget = this->scale;
	bNeedsUpdate = true;
}

void OrthographicCamera::setScaleTarget(float scale) {
	scaleTarget = scale;
	bNeedsUpdate = true;
}

void OrthographicCamera::setScaleLerpPercentage(float percentage) {
	scaleLerpPercentage = percentage;
}

Unit OrthographicCamera::getX() {
	return position[0];
}

Unit OrthographicCamera::getY() {
	return position[1];
}

Unit OrthographicCamera::getWidth() {
	return bounds[0];
}

Unit OrthographicCamera::getHeight() {
	return bounds[1];
}

float OrthographicCamera::getScale() {
	return scale;
}

Unit OrthographicCamera::getTargetX() {
	return targetPosition[0];
}

Unit OrthographicCamera::getTargetY() {
	return targetPosition[1];
}

Unit OrthographicCamera::getTargetWidth() {
	return targetBounds[0];
}

Unit OrthographicCamera::getTargetHeight() {
	return targetBounds[1];
}

float OrthographicCamera::getTargetScale() {
	return scaleTarget;
}

std::array<Unit, 2> OrthographicCamera::convertScreenToWorld(Unit screenX, Unit screenY) {
	return std::array<Unit, 2>({ Unit((((screenX - (bounds[0] / 2.0f)) / scale) + position[0]).meter),
							   Unit(-((((screenY - (bounds[1] / 2.0f)) / scale) - position[1])).meter) });
}

std::array<Unit, 2> OrthographicCamera::convertWorldToScreen(Unit worldX, Unit worldY) {
	return std::array<Unit, 2>({ ((((worldX - position[0]) * scale) + (bounds[0] / 2.0f))),
							   ((((worldY - position[1]) * scale) + (bounds[1] / 2.0f))) });
}

AABB OrthographicCamera::getCameraBounds(Unit extraPadding) {
	return AABB(position[0], position[1], bounds[0] + extraPadding, bounds[1] + extraPadding);
}

glm::mat4 OrthographicCamera::getMatrix() {
	if (bNeedsUpdate)
		updateMatrix();
	return cameraMatrix;
}

void OrthographicCamera::update(float deltaTime) {
	if (!std::equal(position.begin(), position.end(), targetPosition.begin())) {
		position = Math::lerp<Unit, 2>(position, targetPosition, movementLerpPercentage);
		bNeedsUpdate = true;
	}
	if (!std::equal(bounds.begin(), bounds.end(), targetBounds.begin())) {
		bounds = Math::lerp<Unit, 2>(bounds, targetBounds, boundsLerpPercentage);
		bNeedsUpdate = true;
	}
	if (scale != scaleTarget) {
		scale = Math::lerp<float>(scale, scaleTarget, scaleLerpPercentage);
	}
}

void OrthographicCamera::updateMatrix() {
	int xPixel = position[0].getPixel();
	int yPixel = position[1].getPixel();

	orthoMatrix = glm::ortho(0.0f, static_cast<float>(bounds[0].getPixel()), 0.0f, static_cast<float>(bounds[1].getPixel()), -1.0f, 1.0f);

	cameraMatrix = glm::translate(orthoMatrix, glm::vec3(-xPixel + bounds[0].getPixel() / 2, -yPixel + bounds[1].getPixel() / 2, 0.0f));
	glm::vec3 scaleV3 = glm::vec3(scale, scale, 1.0f);
	cameraMatrix = glm::scale(glm::mat4(1.0f), scaleV3) * cameraMatrix;

	bNeedsUpdate = false;
}
