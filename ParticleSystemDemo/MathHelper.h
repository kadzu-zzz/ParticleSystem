#pragma once

#include <array>
#include <Box2D\Box2D.h>

namespace Math {

	template<typename T>
	T max(T a, T b) { return a > b ? a : b; }

	template<typename T>
	T min(T a, T b) { return a > b ? b : a; }

	template<typename T>
	T lerp(T a, T b, float percent) { return a + ((b - a) * percent); }

	template<typename T, unsigned int SIZE>
	std::array<T, SIZE> lerp(std::array<T, SIZE> a, std::array<T, SIZE> b, float percent) {
		std::array<T, SIZE> arr = std::array<T, SIZE>();
		for (unsigned int i = 0; i < SIZE; i++) {
			arr[i] = lerp(a[i], b[i], percent);
		}
		return arr;
	}

	template<typename T>
	T convertToRadian(T degree) {
		static double piOver180 = (3.141592653589793 / 180.0);
		return degree * static_cast<T>(piOver180);
	}

	template<typename T>
	T convertToDegree(T radian) {
		static double piUnder180 = (180.0 / 3.141592653589793);
		return radian * static_cast<T>(piUnder180);
	}

	template<typename T>
	bool getLineIntersection(T p0_x, T p0_y, T p1_x, T p1_y,
							 T p2_x, T p2_y, T p3_x, T p3_y, T *i_x, T *i_y) {
		T s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		T s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
			// Collision detected
			if (i_x != NULL)
				*i_x = p0_x + (t * s1_x);
			if (i_y != NULL)
				*i_y = p0_y + (t * s1_y);
			return true;
		}

		return false; // No collision
	}

	template<typename T>
	bool hasLineIntersection(T p0_x, T p0_y, T p1_x, T p1_y,
							 T p2_x, T p2_y, T p3_x, T p3_y) {
		T s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		T s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
			return true;
		}

		return false; // No collision
	}

}