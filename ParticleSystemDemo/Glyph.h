#pragma once

#include "Vertex.h"
#include "GLTexture.h"

#include <array>
#include <vector>

const constexpr int lineVerts() { return 2; }
const constexpr int triangleVerts() { return 3; }
const constexpr int rectangleAsSingleVerts() { return 4; }
const constexpr int rectangleAsTriangleVerts() { return 6; }

struct GlyphBase {};

template<int numberOfVerts>
struct Glyph : public GlyphBase {
public:
	Glyph(GLTexture* texture, std::array<Vertex, numberOfVerts> nVerts) : texture(texture), vertexes(nVerts) {
	}

	GLTexture* texture;
	std::array<Vertex, numberOfVerts> vertexes;
};

struct TriangleGlyph : public Glyph<triangleVerts()> {
public:
	TriangleGlyph(GLTexture* texture, std::array<Vertex, triangleVerts()> nVerts) : Glyph(texture, nVerts) {
	}
};

struct RectangleGlyph : public Glyph<rectangleAsTriangleVerts()> {
public:
	RectangleGlyph(GLTexture* texture, std::array<Vertex, rectangleAsSingleVerts()> nVerts) : Glyph(texture,
																									std::array<Vertex, rectangleAsTriangleVerts()>({ nVerts[0], nVerts[1], nVerts[2], nVerts[2], nVerts[3], nVerts[1] })) {
	}
	RectangleGlyph(GLTexture* texture, std::array<Vertex, rectangleAsTriangleVerts()> nVerts) : Glyph(texture, nVerts) {
	}
	RectangleGlyph() : Glyph(texture, std::array<Vertex, 6>({ Vertex(), Vertex(), Vertex(), Vertex(), Vertex(), Vertex() })) {
	}

	std::array<TriangleGlyph, 2> disposeIntoTriangles() {
		return std::array<TriangleGlyph, 2>({ TriangleGlyph(texture, std::array<Vertex, 3>({ vertexes[0], vertexes[1], vertexes[2] })),
											TriangleGlyph(texture, std::array<Vertex, 3>({ vertexes[3], vertexes[4], vertexes[5] })) });
	}
};

struct LineGlyph : public Glyph<lineVerts()> {
	LineGlyph(std::array<Vertex, lineVerts()> nVerts) : Glyph(nullptr, nVerts) {
	}

	LineGlyph(Vertex a, Vertex b) : Glyph(nullptr, std::array<Vertex, lineVerts()>({ a, b })) {
	}
	LineGlyph() : Glyph(nullptr, std::array<Vertex, lineVerts()>({ Vertex(0,0,0), Vertex(0,0,0) })) {
	}
};

struct TriangleStripGlyph : public GlyphBase {
	TriangleStripGlyph(GLTexture* texture, int size) : texture(texture), vertexes(size) {
	}

	GLTexture* texture;
	std::vector<Vertex> vertexes;
};

struct TriangleFanGlyph : public GlyphBase {
	TriangleFanGlyph(GLTexture* texture, int size) : texture(texture), vertexes(size) {
	}

	GLTexture* texture;
	std::vector<Vertex> vertexes;
};