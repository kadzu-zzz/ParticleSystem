#include "TextureAsset.h"

#include "Logger.h"
#include "Exit.h"
#include "Constants.h"
#include "AABB.h"
#include "UVBounds.h"

#include <SDL_image.h>
#include <vector>

std::vector<Texture*> TextureAsset::textures;
std::vector<AtlasTexture*> TextureAsset::atlasTextures;

const constexpr float atlasSize() { return 2048.0f; }

TextureResource TextureAsset::getTexture(std::string filename, bool atlasTexture, GLenum forceDifferentWrapping) {
	std::string RawName = filename;
	filename = TEXTURE_PATH + filename;

	for (unsigned int i = 0; i < textures.size(); i++) {
		if (textures[i]->hasBounds(filename)) {
			return TextureResource(textures[i], filename, RawName);
		}
	}

	Texture* texture = nullptr;
	if (atlasTexture) {
		AtlasTexture* atlas = nullptr;
		AABB atlasAABB = AABB(0, 0, 0);
		GLTexture* t = new GLTexture(loadTexture(filename, forceDifferentWrapping));
		for (unsigned int i = 0; i < atlasTextures.size(); i++) {
			if (!atlasTextures[i]->filled) {
				atlasAABB = atlasTextures[i]->getSpace(t->size[0], t->size[1]);
				if (atlasAABB.getHalfWidth() > Unit(0.0f)) {
					atlas = atlasTextures[i];
					break;
				}
			}
		}
		//No Atlas That can fit texture
		if (atlas == nullptr) {
			GLuint textureBuffer;
			glGenTextures(1, &textureBuffer);
			glBindTexture(GL_TEXTURE_2D, textureBuffer);

			//Set the stuff for the buffer...
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(atlasSize()), static_cast<GLsizei>(atlasSize()), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			std::vector<unsigned char> pixels = std::vector<unsigned char>();
			pixels.resize(t->size[0] * t->size[1] * 4);
			glBindTexture(GL_TEXTURE_2D, t->id);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
			glBindTexture(GL_TEXTURE_2D, textureBuffer);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, t->size[0], t->size[1], GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

			atlas = new AtlasTexture(new GLTexture(textureBuffer, static_cast<unsigned int>(atlasSize()), static_cast<unsigned int>(atlasSize())));
			texture = dynamic_cast<Texture*>(atlas);
			atlasTextures.push_back(atlas);
			textures.push_back(texture);
			atlas->addBounds(TEXTURE_PATH + "FULL", UVBounds(0, 0, 1, 1));
			atlas->addBounds(filename, UVBounds(0, 0, t->size[0] / atlasSize(), t->size[1] / atlasSize()));
			atlas->addSpace(AABB(Unit().setAsPixel(t->size[0] / 2.0f),
								 Unit().setAsPixel(t->size[1] / 2.0f),
								 Unit().setAsPixel(t->size[0] / 2.0f),
								 Unit().setAsPixel(t->size[1] / 2.0f)));
		} else {
			std::vector<unsigned char> pixels = std::vector<unsigned char>();
			pixels.resize(t->size[0] * t->size[1] * 4);
			glBindTexture(GL_TEXTURE_2D, t->id);
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
			glBindTexture(GL_TEXTURE_2D, atlas->getGLTexture()->id);
			glTexSubImage2D(GL_TEXTURE_2D, 0,
							(atlasAABB.getX() - atlasAABB.getHalfWidth()).getPixel(),
							(atlasAABB.getY() - atlasAABB.getHalfHeight()).getPixel(),
							t->size[0], t->size[1], GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);


			texture = dynamic_cast<Texture*>(atlas);
			atlas->addBounds(filename, UVBounds((atlasAABB.getX() - atlasAABB.getHalfWidth()).getPixel(),
												(atlasAABB.getY() - atlasAABB.getHalfHeight()).getPixel(),
												t->size[0], t->size[1],
												static_cast<int>(atlasSize()), static_cast<int>(atlasSize())));
		}

		glBindTexture(GL_TEXTURE_2D, t->id);
		glDeleteTextures(1, &t->id);
		delete t;
	} else {
		texture = new Texture(new GLTexture(loadTexture(filename, forceDifferentWrapping)));

		texture->addBounds(filename, UVBounds(0.0f, 0.0f, 1.0f, 1.0f));
		textures.push_back(texture);
	}

	return TextureResource(texture, filename, RawName);
}

GLTexture TextureAsset::loadTexture(std::string filename, GLenum wrapping) {

	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == nullptr) {
		return GLTexture(0, 0, 0);
	}

	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* rgbSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(surface, 0, rgbSurface, 0);

	int mode = GL_RGB;
	GLuint textureId;

	glGenTextures(1, &(textureId));
	glBindTexture(GL_TEXTURE_2D, textureId);

	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLTexture texture = GLTexture(textureId, surface->w, surface->h);

	SDL_FreeSurface(surface);
	SDL_FreeSurface(rgbSurface);

	return texture;
}
