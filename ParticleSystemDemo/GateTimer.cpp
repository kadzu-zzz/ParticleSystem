#include "GateTimer.h"

#include <cmath>

GateTimer::GateTimer() : time(0.0f), timeMax(0.0f) {
}

GateTimer::~GateTimer() {
}

bool GateTimer::update(float delta) {
	time = std::fmax(time - delta, 0.0f);
	return time == 0.0f;
}

void GateTimer::reset() {
	time = timeMax;
}

void GateTimer::setLength(float t) {
	timeMax = t;
	time = t;
}

float GateTimer::getProgress() {
	return 1.0f - (time / timeMax);
}
