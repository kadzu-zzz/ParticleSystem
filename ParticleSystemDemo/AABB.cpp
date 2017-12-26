#include "AABB.h"

AABB::AABB(Unit x, Unit y, Unit halfDimension) : centerX(x), centerY(y), halfWidth(halfDimension), halfHeight(halfDimension) {
}

AABB::AABB(Unit x, Unit y, Unit halfWidth, Unit halfHeight) : centerX(x), centerY(y), halfWidth(halfWidth), halfHeight(halfHeight) {
}

AABB::~AABB() {
}

Unit AABB::getX() {
	return centerX;
}

Unit AABB::getY() {
	return centerY;
}

Unit AABB::getHalfWidth() {
	return halfWidth;
}

Unit AABB::getHalfHeight() {
	return halfHeight;
}

void AABB::setCenter(Unit x, Unit y) {
	centerX = x;
	centerY = y;
}

bool AABB::containsPoint(Unit x, Unit y) {
	return !(x > centerX + halfWidth ||
			 x < centerX - halfWidth ||
			 y < centerY - halfHeight ||
			 y > centerY + halfHeight);
}

bool AABB::intersectsAABB(AABB rhs) {
	return !(rhs.centerX - rhs.halfWidth > centerX + halfWidth ||
			 rhs.centerX + rhs.halfWidth < centerX - halfWidth ||
			 rhs.centerY - rhs.halfHeight > centerY + halfHeight ||
			 rhs.centerY + rhs.halfHeight < centerY - halfHeight);
}
