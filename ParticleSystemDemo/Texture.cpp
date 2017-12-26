#include "Texture.h"

Texture::Texture(GLTexture * texture) : texture(texture) {
}

Texture::~Texture() {
}

GLTexture * Texture::getGLTexture() {
	return texture;
}

bool Texture::hasBounds(std::string resourceName) {
	return (bounds.find(resourceName) != bounds.end());
}

UVBounds Texture::getBounds(std::string resourceName) {
	auto res = bounds.find(resourceName);
	if (res != bounds.end())
		return res->second;
	return UVBounds(0.0f, 0.0f, 1.0f, 1.0f);
}

void Texture::addBounds(std::string resourceName, UVBounds bounds) {
	this->bounds.insert(std::make_pair(resourceName, bounds));
}

TextureResource::TextureResource(Texture * texture, std::string resourceName, std::string RawResourceName) : texture(texture), resourceName(resourceName), RawResourceName(RawResourceName) {
}

void TextureResource::reinitialize(Texture * texture, std::string resourceName, std::string RawResourceName) {
	this->texture = texture;
	this->resourceName = resourceName;
	this->RawResourceName = RawResourceName;
}

GLTexture * TextureResource::getGLTexture() {
	return texture->getGLTexture();
}

Texture * TextureResource::getTexture() {
	return texture;
}

UVBounds TextureResource::getBounds() {
	return texture->getBounds(resourceName);
}

std::string TextureResource::getResourceName() {
	return resourceName;
}

std::string TextureResource::getRawResourceName() {
	return RawResourceName;
}

std::array<unsigned int, 2> TextureResource::getTextureSizeInPixel() {
	return{ static_cast<unsigned int>(this->getBounds().uWidth * texture->getGLTexture()->size[0]),
		static_cast<unsigned int>(this->getBounds().vHeight * texture->getGLTexture()->size[1]) };
}

AtlasTexture::AtlasTexture(GLTexture * texture) : Texture(texture), filled(false) {
}

AtlasTexture::~AtlasTexture() {
}

AABB AtlasTexture::getSpace(unsigned int textureWidth, unsigned int textureHeight) {
	float texWidthOver2 = static_cast<float>(textureWidth) / 2.0f;
	float texHeightOver2 = static_cast<float>(textureHeight) / 2.0f;

	Unit cX = Unit().setAsPixel(texWidthOver2);
	Unit cY = Unit().setAsPixel(texHeightOver2);
	Unit inW = Unit().setAsPixel(static_cast<float>(texture->size[0]) - texWidthOver2);
	Unit inH = Unit().setAsPixel(static_cast<float>(texture->size[1]) - texHeightOver2);

	AABB inputAABB = AABB(cX, cY, cX, cY);

	for (Unit h = cY; h < inH; h = h + Unit(0.0f).setAsPixel(50.0f)) {
		for (Unit w = cX; w < inW; w = w + Unit(0.0f).setAsPixel(10.0f)) {
			inputAABB.setCenter(w, h);
			if (!aabbInFilledSpace(inputAABB)) {
				filledSpace.push_back(inputAABB);
				return inputAABB;
			}
		}
	}

	filled = true;
	return AABB(-1.0f, -1.0f, -1.0f);
}

void AtlasTexture::addSpace(AABB aabb) {
	filledSpace.push_back(aabb);
}

bool AtlasTexture::aabbInFilledSpace(AABB aabb) {
	for (auto it : filledSpace) {
		if (it.intersectsAABB(aabb)) {
			return true;
		}
	}

	return false;
}
