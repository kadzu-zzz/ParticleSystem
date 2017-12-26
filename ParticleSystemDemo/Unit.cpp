#include "Unit.h"

Unit::Unit() : meter(0.0f) {
}

Unit::Unit(float meter) : meter(meter) {
}

Unit::Unit(double meter) : meter(static_cast<float>(meter)) {
}

Unit::Unit(int meter) : meter(static_cast<float>(meter)) {
}

Unit::Unit(long meter) : meter(static_cast<float>(meter)) {
}

const int Unit::getPixel() {
	return static_cast<int>(meter * MeterPixelConversion());
}

const float Unit::asUnalignedPixel() {
	return meter * MeterPixelConversion();
}

Unit Unit::setAsPixel(float pixel) {
	meter = static_cast<float>(pixel) * PixelMeterConversion();
	return *this;
}