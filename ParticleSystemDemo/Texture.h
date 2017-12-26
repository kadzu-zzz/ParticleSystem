#pragma once

#include "GLTexture.h"

#include "AABB.h"
#include "UVBounds.h"
#include <array>
#include <unordered_map>
#include <string>

class Texture;

struct TextureResource {
	TextureResource(Texture* texture, std::string resourceName, std::string RawResourceName);
	void reinitialize(Texture* texture, std::string resourceName, std::string RawResourceName);

	GLTexture* getGLTexture();
	Texture* getTexture();
	UVBounds getBounds();
	std::string getResourceName();
	std::string getRawResourceName();
	std::array<unsigned int, 2> getTextureSizeInPixel();
protected:
	Texture* texture;
	std::string resourceName;
	std::string RawResourceName;
};

class Texture {
public:
	Texture(GLTexture* texture);
	~Texture();

	GLTexture* getGLTexture();
	bool hasBounds(std::string resourceName);
	UVBounds getBounds(std::string resourceName);

	virtual void addBounds(std::string resourceName, UVBounds bounds);
protected:
	GLTexture* texture;
	std::unordered_map<std::string, UVBounds> bounds;
};

class AtlasTexture : public Texture {
public:
	AtlasTexture(GLTexture* texture);
	~AtlasTexture();

	AABB getSpace(unsigned int textureWidth, unsigned int textureHeight);
	void addSpace(AABB aabb);

	bool filled;
protected:
	std::vector<AABB> filledSpace;

	bool aabbInFilledSpace(AABB aabb);
};