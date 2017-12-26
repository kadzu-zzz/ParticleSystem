#pragma once

#include "Unit.h"

class AABB {
public:
	AABB(Unit x, Unit y, Unit halfDimension);
	AABB(Unit x, Unit y, Unit halfWidth, Unit halfHeight);
	~AABB();

	virtual Unit getX();
	virtual Unit getY();
	Unit getHalfWidth();
	Unit getHalfHeight();

	void setCenter(Unit x, Unit y);

	virtual bool containsPoint(Unit x, Unit y);
	virtual bool intersectsAABB(AABB rhs);


	Unit centerX, centerY, halfWidth, halfHeight;
};

