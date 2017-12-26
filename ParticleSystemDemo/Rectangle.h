#pragma once

#include "RenderContainer.h"

#include "Glyph.h"
#include "Colour.h"
#include "Unit.h"
#include "TextureAsset.h"
#include <array>
#include <Box2D\Box2D.h>
class RenderingEngine;

class Rectangle : public RenderContainer {
public:
	Rectangle();
	~Rectangle();

	void intialise(TextureResource texture, Unit centerX, Unit centerY, float depth, Unit offsetX, Unit offsetY, Unit width, Unit height, float rotation, Colour colour);

	void setTexture(TextureResource texture);
	void setCenterX(Unit x);
	void setCenterY(Unit y);
	void setCenter(Unit x, Unit y);
	void setOffsetX(Unit x);
	void setOffsetY(Unit y);
	void setOffset(Unit x, Unit y);
	void setWidth(Unit width);
	void setHeight(Unit height);
	void setSize(Unit width, Unit height);
	void setDepth(float depth);
	void setRotation(float rotation);
	void setColour(Colour colour);
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);

	TextureResource getTexture();
	Unit getCenterX();
	Unit getCenterY();
	Unit getOffsetX();
	Unit getOffsetY();
	Unit getWidth();
	Unit getHeight();
	float getDepth();
	float getRotation();
	Colour getColour();
	bool isFlipX();
	bool isFlipY();

	void sendRenderInformation(VBOBatcher* target) override;
protected:
	TextureResource texture;
	Unit centerX, centerY;
	Unit offsetX, offsetY;
	Unit width, height;
	float depth;
	float rotation;
	Colour colour;
	UVBounds uvBounds;
	bool flipX, flipY;

	RectangleGlyph glyph;

	bool needsReconstructed;
	void reconstruct();
};