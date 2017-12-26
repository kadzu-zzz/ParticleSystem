#pragma once

#include <chrono>

/*Stopwatch Class, allows a simple way to update a deltatime*/
class StopWatch {
public:
	/***
	* StopWatch Constructor
	* Sets up variables...
	*/
	StopWatch() :
		last(std::chrono::high_resolution_clock::now()),
		current(std::chrono::high_resolution_clock::now()) {
	};

	/***
	* StopWatch Deconstructor
	* Nothing Interesting
	*/
	~StopWatch() {};

	/**
	* Update
	* update the current time in Delta to be the time between the current and last.
	*/
	void update() {
		last = current;
		current = std::chrono::high_resolution_clock::now();
	};

	float getCurrentDeltaSecond() {
		return std::chrono::duration<float>(current - last).count();
		//return (static_cast<long>(std::chrono::duration_cast<std::chrono::seconds>((current - last)).count()) / 1000000.0f);
		//return ((current - last)).count() / 1000000000.0;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> last; //< last time.
	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> current; //< current time
};