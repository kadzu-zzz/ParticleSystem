#include "VBOBatcher.h"

VBOBatcher::VBOBatcher() : vbo(), glyphs(), lineGlyphs(LineGlyph(Vertex(), Vertex())), batches(), vertexCount(0), lineBatch(nullptr, GL_LINES, 0, 0) {
	lineGlyphs.clear();
	glyphs.clear();
}

VBOBatcher::~VBOBatcher() {
}

void VBOBatcher::initialise() {
	vbo.initialise();
	batches.reserve(100);
	bPrepared = false;
}

void VBOBatcher::add(LineGlyph glyph) {
	vertexCount += lineVerts();
	lineGlyphs.addGlyph(glyph);
}

void VBOBatcher::add(RectangleGlyph glyph) {
	std::array<TriangleGlyph, 2> tri = glyph.disposeIntoTriangles();
	add(tri[0]);
	add(tri[1]);
}

void VBOBatcher::add(TriangleGlyph glyph) {
	vertexCount += triangleVerts();
	lock.try_lock_shared();
	auto gg = glyphs.find(glyph.texture);
	if (gg != glyphs.end()) {
		gg->second.addGlyph(glyph);
		lock.unlock_shared();
	} else {
		lock.unlock_shared();
		lock.try_lock();
		glyphs.insert(std::make_pair(glyph.texture, GlyphContainer<TriangleGlyph>(glyph)));
		lock.unlock();
	}
}

void VBOBatcher::add(TriangleStripGlyph glyph) {
	lock.try_lock_shared();
	vertexCount += glyph.vertexes.size();
	auto gg = stripGlyphs.find(glyph.texture);
	if (gg != stripGlyphs.end()) {
		gg->second.addGlyph(glyph);
		lock.unlock_shared();
	} else {
		lock.unlock_shared();
		lock.try_lock();
		stripGlyphs.insert(std::make_pair(glyph.texture, GlyphContainer<TriangleStripGlyph>(glyph)));
		lock.unlock();
	}
}

void VBOBatcher::add(TriangleFanGlyph glyph) {
	lock.try_lock_shared();
	vertexCount += glyph.vertexes.size();
	auto gg = fanGlyphs.find(glyph.texture);
	if (gg != fanGlyphs.end()) {
		gg->second.addGlyph(glyph);
		lock.unlock_shared();
	} else {
		lock.unlock_shared();
		lock.try_lock();
		fanGlyphs.insert(std::make_pair(glyph.texture, GlyphContainer<TriangleFanGlyph>(glyph)));
		lock.unlock();
	}
}

void VBOBatcher::prepare() {
	if (stripGlyphs.size() == 0 && fanGlyphs.size() == 0 && glyphs.size() == 0 && lineGlyphs.glyphs.size() == 0) {
		bPrepared = true;
		return;
	}

	verticies.resize(0);
	verticies.resize(vertexCount);

	unsigned int offset = 0;
	unsigned int cv = 0;

	if (glyphs.size() != 0) {
		//Get triangle glyphs in
		for (auto it : glyphs) {
			batches.push_back(RenderBatch(it.first, GL_TRIANGLES, offset, it.second.glyphs.size() * triangleVerts()));
			offset += it.second.glyphs.size() * triangleVerts();

			for (auto v = it.second.glyphs.begin(); v != it.second.glyphs.end(); v++) {
				verticies[cv++] = v->vertexes[0];
				verticies[cv++] = v->vertexes[1];
				verticies[cv++] = v->vertexes[2];
			}
		}
	}

	if (fanGlyphs.size() != 0) {
		//Get triangle fan glyphs in
		for (auto it : fanGlyphs) {
			for (auto g : it.second.glyphs) {
				batches.push_back(RenderBatch(it.first, GL_TRIANGLE_FAN, offset, g.vertexes.size()));
				offset += g.vertexes.size();

				for (unsigned int i = 0; i < g.vertexes.size(); i++)
					verticies[cv++] = g.vertexes[i];
			}
		}
	}

	if (stripGlyphs.size() != 0) {
		//Get triangle strip glyphs in
		for (auto it : stripGlyphs) {
			for (auto g : it.second.glyphs) {
				batches.push_back(RenderBatch(it.first, GL_TRIANGLE_STRIP, offset, g.vertexes.size()));
				offset += g.vertexes.size();

				for (unsigned int i = 0; i < g.vertexes.size(); i++)
					verticies[cv++] = g.vertexes[i];
			}
		}
	}


	if (lineGlyphs.glyphs.size() != 0) {
		//Get line glyphs in
		lineBatch = (RenderBatch(lineGlyphs.texture, GL_LINES, offset, lineGlyphs.glyphs.size() * lineVerts()));
		offset += lineGlyphs.glyphs.size() * lineVerts();
		for (auto v : lineGlyphs.glyphs) {
			verticies[cv++] = v.vertexes[0];
			verticies[cv++] = v.vertexes[1];
		}
	}

	if (vertexCount == 0) {
		bPrepared = true;
		return;
	}

	vbo.bufferData(&verticies[0], vertexCount);
	bPrepared = true;
}

bool VBOBatcher::isPrepared() {
	return bPrepared;
}

void VBOBatcher::render() {
	vbo.bindVertexArray();
	for (RenderBatch batch : batches) {
		if (batch.texture == nullptr)
			continue;
		glBindTexture(GL_TEXTURE_2D, batch.texture->id);

		vbo.render(batch.offset, batch.size, batch.renderMode);
	}
	//vbo.unbindVertexArray();
}

void VBOBatcher::renderLines() {
	if (lineBatch.size != 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
		vbo.bindVertexArray();
		vbo.render(lineBatch.offset, lineBatch.size, GL_LINES);
		//vbo.unbindVertexArray();
	}
}

void VBOBatcher::clear() {
	for (auto it = glyphs.begin(); it != glyphs.end(); it++)
		it->second.clear();
	lineGlyphs.clear();
	fanGlyphs.clear();
	stripGlyphs.clear();
	lineBatch.size = 0;
	batches.clear();
	vertexCount = 0;
	bPrepared = false;
}
