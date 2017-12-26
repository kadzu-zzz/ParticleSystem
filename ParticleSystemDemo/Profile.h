#pragma once

#include <chrono>
#include <iostream>
#include <string>

#define PROFILE_START(name) Profile __Profile = Profile(name);
#define PROFILE_END __Profile.end();

#define PROFILE_START_S(name, profilerName) Profile profilerName = Profile(name);
#define PROFILE_END_S(profilerName) profilerName.end();

struct Profile {
public:
	Profile(std::string name) {
		s = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		std::cout << "Profiling Start: \"" << (this->name = name) << "\"\n";
	}

	void end() {
		s = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()) - s;
		std::cout << "Profiling Complete: \"" << name << "\" took " << s.count() / 1000.0f << "sec.\n";
	}

private:
	std::string name;
	std::chrono::milliseconds s;
};
