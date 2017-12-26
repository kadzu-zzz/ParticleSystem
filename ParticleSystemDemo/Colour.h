#pragma once

#include <GL\glew.h>
#include <array>

struct Colour {
	Colour();
	Colour(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);
	Colour(std::array<GLubyte, 4> components);

	static std::array<GLubyte, 4> AsArray(Colour c) {
		return{ c.r, c.g, c.b, c.a };
	};

	Colour lerp(Colour b, float percent) {
		Colour c = Colour(0, 0, 0, 0);
		c.r = r + static_cast<GLubyte>(static_cast<float>(((b.r - r)) * percent));
		c.g = g + static_cast<GLubyte>(static_cast<float>(((b.g - g)) * percent));
		c.b = this->b + static_cast<GLubyte>(static_cast<float>(((b.b - this->b)) * percent));
		c.a = a + static_cast<GLubyte>(static_cast<float>(((b.a - a)) * percent));

		return c;
	}

	GLubyte r, g, b, a;
};


constexpr GLubyte MinGLuByte(int a, int b) { return a < b ? a : b; };
constexpr GLubyte MaxGLuByte(int a, int b) { return a > b ? a : b; };

bool operator ==(const Colour& left, const Colour& right);
bool operator !=(const Colour& left, const Colour& right);
Colour operator +(const Colour& left, const Colour& right);
Colour operator -(const Colour& left, const Colour& right);
Colour operator *(const Colour& left, const Colour& right);
Colour operator *(const Colour& left, const float& right);
Colour& operator +=(Colour& left, const Colour& right);
Colour& operator -=(Colour& left, const Colour& right);
Colour& operator *=(Colour& left, const Colour& right);