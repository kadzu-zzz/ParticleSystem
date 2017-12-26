#include "UVBounds.h"

const constexpr float fCast(int in) { return static_cast<float>(in); }

UVBounds::UVBounds(int left, int top, int width, int height, int textureWidth, int textureHeight) : u(fCast(left) / fCast(textureWidth)), v(fCast(top) / fCast(textureHeight)), uWidth(fCast(width) / fCast(textureWidth)), vHeight(fCast(height) / fCast(textureHeight)) {
}

UVBounds::UVBounds(float u, float v, float uWidth, float vHeight) : u(u), v(v), uWidth(uWidth), vHeight(vHeight) {
}
