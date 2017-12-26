#pragma once

#include <cmath>

const constexpr float MeterPixelConversion() { return 100.0f; };
const constexpr float PixelMeterConversion() { return 0.01f; };

class Unit {
public:
	Unit();
	Unit(float meter);
	Unit(double meter);
	Unit(int meter);
	Unit(long meter);

	float meter;

	const int getPixel();
	const float asUnalignedPixel();
	Unit setAsPixel(float pixel);

	Unit operator+(Unit &rhs) {
		return meter + rhs.meter;
	}

	Unit operator+(const Unit &rhs) {
		return meter + rhs.meter;
	}

	Unit operator-(Unit &rhs) {
		return meter - rhs.meter;
	}

	Unit operator-(const Unit &rhs) {
		return meter - rhs.meter;
	}

	Unit operator*(Unit &rhs) {
		return meter * rhs.meter;
	}

	Unit operator*(float &rhs) {
		return meter * rhs;
	}

	Unit operator/(Unit &rhs) {
		return meter / rhs.meter;
	}

	Unit operator/(float &rhs) {
		return meter / rhs;
	}

	bool operator>(Unit &rhs) {
		return meter - 0.0001f > rhs.meter && meter > rhs.meter - 0.0001f;
	}

	bool operator<(Unit &rhs) {
		return meter < rhs.meter;
	}

	bool operator>=(Unit &rhs) {
		return (meter > rhs.meter) || (operator==(rhs));
	}

	bool operator<=(Unit &rhs) {
		return (meter < rhs.meter) || (operator==(rhs));
	}

	bool operator==(Unit &rhs) {
		return abs(meter - rhs.meter) < 0.00001f;
	}
	bool operator!=(Unit &rhs) {
		return !(operator==(rhs));
	}

	friend const Unit operator*(const Unit &lhs, const float & rhs) { return Unit(lhs.meter * rhs); }
	friend const Unit operator*(const Unit &lhs, const double & rhs) { return Unit(lhs.meter * rhs); }
	friend const Unit operator/(const Unit &lhs, const float & rhs) { return Unit(lhs.meter / rhs); }
	friend const Unit operator/(const Unit &lhs, const double & rhs) { return Unit(lhs.meter / rhs); }
};

