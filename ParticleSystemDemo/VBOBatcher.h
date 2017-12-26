#pragma once

#include "VBO.h"
#include "Glyph.h"
#include "RenderBatch.h"
#include "Vertex.h"

#include <concurrent_unordered_map.h>
#include <concurrent_vector.h>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <thread>

template<typename GlyphType>
struct GlyphContainer {
	GlyphContainer(GlyphType glyph) : texture(glyph.texture), glyphs() {
		glyphs.push_back(glyph);
	}

	void addGlyph(GlyphType glyph) {
		glyphs.push_back(glyph);
	}

	void clear() {
		glyphs.clear();
	}

	GLTexture* texture;
	concurrency::concurrent_vector<GlyphType> glyphs;
};

class VBOBatcher {
public:
	VBOBatcher();
	~VBOBatcher();

	void initialise();

	void add(LineGlyph glyph);
	void add(RectangleGlyph glyph);
	void add(TriangleGlyph glyph);
	void add(TriangleStripGlyph glyph);
	void add(TriangleFanGlyph glyph);

	//Add array of line glyphs 
	template<std::size_t SIZE>
	void add(std::array<LineGlyph, SIZE> glyphs) {
		for (unsigned int i = 0; i < glyphs.size(); i++)
			add(glyphs[i]);
	}
	//Add array of rectangle glyphs
	template<std::size_t SIZE>
	void add(std::array<RectangleGlyph, SIZE> glyphs) {
		for (unsigned int i = 0; i < glyphs.size(); i++)
			add(glyphs[i]);
	}
	//Add array of triangle glyphs
	template<std::size_t SIZE>
	void add(std::array<TriangleGlyph, SIZE> glyphs) {
		for (unsigned int i = 0; i < glyphs.size(); i++)
			add(glyphs[i]);
	}
	//Add array of triangle glyphs
	template<std::size_t SIZE>
	void add(std::array<TriangleStripGlyph, SIZE> glyphs) {
		for (unsigned int i = 0; i < glyphs.size(); i++)
			add(glyphs[i]);
	}
	//Add array of triangle glyphs
	template<std::size_t SIZE>
	void add(std::array<TriangleFanGlyph, SIZE> glyphs) {
		for (unsigned int i = 0; i < glyphs.size(); i++)
			add(glyphs[i]);
	}

	void prepare();
	bool isPrepared();

	void render();
	void renderLines();

	void clear();
	std::vector<Vertex> verticies;
private:
	VBO vbo;
	std::unordered_map<GLTexture*, GlyphContainer<TriangleGlyph>> glyphs;
	std::unordered_map<GLTexture*, GlyphContainer<TriangleStripGlyph>> stripGlyphs;
	std::unordered_map<GLTexture*, GlyphContainer<TriangleFanGlyph>> fanGlyphs;
	GlyphContainer<LineGlyph> lineGlyphs;

	bool bPrepared;
	std::vector<RenderBatch> batches;
	RenderBatch lineBatch;

	std::atomic_uint vertexCount;

	std::shared_timed_mutex lock;
};

