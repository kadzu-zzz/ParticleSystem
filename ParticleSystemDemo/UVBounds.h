#pragma once

struct UVBounds {
	UVBounds(int left, int top, int width, int height, int textureWidth, int textureHeight);
	UVBounds(float u, float v, float uWidth, float vHeight);

	float u;
	float v;
	float uWidth;
	float vHeight;
};