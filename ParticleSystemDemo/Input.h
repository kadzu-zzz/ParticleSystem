#pragma once

struct KeyPress {
	bool bPrevious;
	bool bCurrent;

	void set(bool current) {
		bPrevious = this->bCurrent;
		this->bCurrent = current;
	}

	bool isKeyJustUp() {
		return bPrevious && !bCurrent;
	}

	bool isKeyJustDown() {
		return !bPrevious && bCurrent;
	}

	bool isKeyPressed() {
		return bCurrent;
	}
};

struct Mouse {
	KeyPress left; //< Maps to SDL_BUTTON_LEFT
	KeyPress right; //< Maps to SDL_BUTTON_RIGHT
	KeyPress middle; //< Maps to SDL_BUTTON_MIDDLE
};