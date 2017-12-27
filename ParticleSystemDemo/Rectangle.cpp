#include "Rectangle.h"

#include "RenderingEngine.h"

Rectangle::Rectangle() : texture(nullptr, "", ""), uvBounds(0.0f, 0.0f, 1.0f, 1.0f), glyph(nullptr, std::array<Vertex, 4>({})) {
}

Rectangle::~Rectangle() {
}

void Rectangle::intialise(TextureResource texture, Unit centerX, Unit centerY, float depth, Unit offsetX, Unit offsetY, Unit width, Unit height, float rotation, Colour colour) {
	this->texture = texture;
	this->centerX = centerX;
	this->centerY = centerY;
	this->depth = depth;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->width = width;
	this->height = height;
	this->rotation = rotation;
	this->colour = colour;
	uvBounds = texture.getBounds();
	flipX = false;
	flipY = false;

	needsReconstructed = true;
}

void Rectangle::setTexture(TextureResource texture) {
	this->texture = texture;
	uvBounds = texture.getBounds();

	if (flipX) {
		float w = uvBounds.uWidth;
		uvBounds.u = uvBounds.u + w;
		uvBounds.uWidth = -w;
	}
	if (flipY) {
		float h = uvBounds.vHeight;
		uvBounds.v = uvBounds.v + h;
		uvBounds.vHeight = -h;
	}

	needsReconstructed = true;
}

void Rectangle::setCenterX(Unit x) {
	centerX = x;
	needsReconstructed = true;
}

void Rectangle::setCenterY(Unit y) {
	centerY = y;
	needsReconstructed = true;
}

void Rectangle::setCenter(Unit x, Unit y) {
	centerX = x;
	centerY = y;
	needsReconstructed = true;
}

void Rectangle::setOffsetX(Unit x) {
	offsetX = x;
	needsReconstructed = true;
}

void Rectangle::setOffsetY(Unit y) {
	offsetY = y;
	needsReconstructed = true;
}

void Rectangle::setOffset(Unit x, Unit y) {
	offsetX = x;
	offsetY = y;
	needsReconstructed = true;
}

void Rectangle::setWidth(Unit width) {
	this->width = width;
	needsReconstructed = true;
}

void Rectangle::setHeight(Unit height) {
	this->height = height;
}

void Rectangle::setSize(Unit width, Unit height) {
	this->width = width;
	this->height = height;
	needsReconstructed = true;
}

void Rectangle::setDepth(float depth) {
	this->depth = depth;
	needsReconstructed = true;
}

void Rectangle::setRotation(float rotation) {
	this->rotation = rotation;
	needsReconstructed = true;
}

void Rectangle::setColour(Colour colour) {
	this->colour = colour;
	needsReconstructed = true;
}

void Rectangle::setFlipX(bool flipX) {
	if (flipX != this->flipX) {
		float w = uvBounds.uWidth;
		uvBounds.u = uvBounds.u + w;
		uvBounds.uWidth = -w;
	}
	this->flipX = flipX;

	needsReconstructed = true;
}

void Rectangle::setFlipY(bool flipY) {
	if (flipY != this->flipY) {
		float h = uvBounds.vHeight;
		uvBounds.v = uvBounds.v + h;
		uvBounds.vHeight = -h;
	}
	this->flipY = flipY;

	needsReconstructed = true;
}

TextureResource Rectangle::getTexture() {
	return texture;
}

Unit Rectangle::getCenterX() {
	return centerX;
}

Unit Rectangle::getCenterY() {
	return centerY;
}

Unit Rectangle::getOffsetX() {
	return offsetX;
}

Unit Rectangle::getOffsetY() {
	return offsetY;
}

Unit Rectangle::getWidth() {
	return width;
}

Unit Rectangle::getHeight() {
	return height;
}

float Rectangle::getDepth() {
	return depth;
}

float Rectangle::getRotation() {
	return rotation;
}

Colour Rectangle::getColour() {
	return colour;
}

bool Rectangle::isFlipX() {
	return flipX;
}

bool Rectangle::isFlipY() {
	return flipY;
}



std::array<TriangleGlyph, 2> Rectangle::getRenderGlyphs() {
	if (needsReconstructed)
		reconstruct();

	return glyph.disposeIntoTriangles();
}

void Rectangle::sendRenderInformation(VBOBatcher* target) {
	if (needsReconstructed)
		reconstruct();

	target->add(glyph);
}

void Rectangle::reconstruct() {
	needsReconstructed = false;

	float halfWidth = (width.asUnalignedPixel() / 2.0f);
	float halfHeight = (height.asUnalignedPixel() / 2.0f);
	Unit globalX = offsetX + centerX;
	Unit globalY = offsetY + centerY;

	float cosAngle = static_cast<float>(cos(rotation));
	float sinAngle = static_cast<float>(sin(rotation));

	float hCos = halfHeight * cosAngle;
	float wCos = halfWidth * cosAngle;
	float hSin = halfHeight * sinAngle;
	float wSin = halfWidth * sinAngle;

	glyph = RectangleGlyph(texture.getGLTexture(), std::array<Vertex, 4>({
		Vertex(globalX.asUnalignedPixel() - wCos + hSin,
		globalY.asUnalignedPixel() - hCos - wSin, depth, uvBounds.u, uvBounds.v + uvBounds.vHeight, colour),

																		 Vertex(globalX.asUnalignedPixel() + wCos + hSin,
																				globalY.asUnalignedPixel() - hCos + wSin, depth, uvBounds.u + uvBounds.uWidth, uvBounds.v + uvBounds.vHeight, colour),

																		 Vertex(globalX.asUnalignedPixel() - wCos - hSin,
																				globalY.asUnalignedPixel() + hCos - wSin, depth, uvBounds.u, uvBounds.v , colour),

																		 Vertex(globalX.asUnalignedPixel() + wCos - hSin,
																				globalY.asUnalignedPixel() + hCos + wSin, depth, uvBounds.u + uvBounds.uWidth, uvBounds.v, colour)
	}));
}