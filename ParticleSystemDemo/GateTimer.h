#pragma once
class GateTimer {
public:
	GateTimer();
	~GateTimer();

	//Returns true when the timer is finished
	bool update(float delta);

	void reset();
	void setLength(float t);
	float getProgress();

	float time;
	float timeMax;
};

