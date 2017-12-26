#include "Colour.h"

Colour::Colour() : r(255), g(255), b(255), a(255) {
}

Colour::Colour(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {
}

Colour::Colour(std::array<GLubyte, 4> components) : r(components[0]), g(components[1]), b(components[2]), a(components[3]) {
}

bool operator==(const Colour & left, const Colour & right) {
	return (left.r == right.r &&
			left.g == right.g &&
			left.b == right.b &&
			left.a == right.a);
}

bool operator!=(const Colour & left, const Colour & right) {
	return (left.r != right.r ||
			left.g != right.g ||
			left.b != right.b ||
			left.a != right.a);
}

Colour operator+(const Colour & left, const Colour & right) {
	return Colour(MinGLuByte(left.r + static_cast<int>(right.r), 255),
				  MinGLuByte(left.g + static_cast<int>(right.g), 255),
				  MinGLuByte(left.b + static_cast<int>(right.b), 255),
				  MinGLuByte(left.a + static_cast<int>(right.a), 255));
}

Colour operator-(const Colour & left, const Colour & right) {
	return Colour(MaxGLuByte(left.r - static_cast<int>(right.r), 0),
				  MaxGLuByte(left.g - static_cast<int>(right.g), 0),
				  MaxGLuByte(left.b - static_cast<int>(right.b), 0),
				  MaxGLuByte(left.a - static_cast<int>(right.a), 0));
}

Colour operator*(const Colour & left, const Colour & right) {
	return Colour(MinGLuByte(left.r * static_cast<int>(right.r), 255),
				  MinGLuByte(left.g * static_cast<int>(right.g), 255),
				  MinGLuByte(left.b * static_cast<int>(right.b), 255),
				  MinGLuByte(left.a * static_cast<int>(right.a), 255));
}

Colour operator*(const Colour & left, const float & right) {
	return Colour(MinGLuByte(left.r * static_cast<int>(right), 255),
				  MinGLuByte(left.g * static_cast<int>(right), 255),
				  MinGLuByte(left.b * static_cast<int>(right), 255),
				  MinGLuByte(left.a * static_cast<int>(right), 255));
}

Colour& operator+=(Colour & left, const Colour & right) {
	return left = left + right;
}

Colour& operator-=(Colour & left, const Colour & right) {
	return left = left - right;
}

Colour& operator*=(Colour & left, const Colour & right) {
	return left = left * right;
}
