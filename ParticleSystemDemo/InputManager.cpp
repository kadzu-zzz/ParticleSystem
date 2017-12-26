#include "InputManager.h"

#include "Input.h"

#include <SDL2\SDL.h>

std::unordered_map<unsigned short, KeyPress> InputManager::keys = std::unordered_map<unsigned short, KeyPress>();
Mouse InputManager::mouse = Mouse();
int InputManager::MouseWheelDelta = 0;

void InputManager::update() {
	for (auto it = keys.begin(); it != keys.end(); it++) {
		it->second.set((it->second.bCurrent ? true : false));
	}

	mouse.left.set(mouse.left.bCurrent);
	mouse.right.set(mouse.right.bCurrent);
	mouse.middle.set(mouse.middle.bCurrent);
	MouseWheelDelta = 0;
}

void InputManager::updateKey(unsigned int key, bool state) {
	auto iter = keys.find(key);

	if (iter == keys.end()) {
		keys.insert(std::make_pair(key, KeyPress()));
		updateKey(key, false);
		updateKey(key, state);
		return;
	}

	iter->second.bCurrent = state;
}

void InputManager::updateMouseButton(unsigned int button, bool state) {
	if (button == SDL_BUTTON_LEFT) {
		mouse.left.set(state);
	} else if (button == SDL_BUTTON_RIGHT) {
		mouse.right.set(state);
	} else if (button == SDL_BUTTON_MIDDLE) {
		mouse.middle.set(state);
	}
}

void InputManager::updateMouseWheel(int veticalDelta) {
	MouseWheelDelta = veticalDelta;
}

glm::vec2 InputManager::getMouseLocation() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return glm::vec2(x, y);
}

bool InputManager::isMouseJustDown(unsigned int button) {
	if (button == SDL_BUTTON_LEFT)
		return mouse.left.isKeyJustDown();

	if (button == SDL_BUTTON_RIGHT)
		return mouse.right.isKeyJustDown();

	if (button == SDL_BUTTON_MIDDLE)
		return mouse.middle.isKeyJustDown();


	return false;
}

bool InputManager::isMouseJustUp(unsigned int button) {
	if (button == SDL_BUTTON_LEFT)
		return mouse.left.isKeyJustUp();

	if (button == SDL_BUTTON_RIGHT)
		return mouse.right.isKeyJustUp();

	if (button == SDL_BUTTON_MIDDLE)
		return mouse.middle.isKeyJustUp();

	return false;
}

bool InputManager::isMousePressed(unsigned int button) {
	if (button == SDL_BUTTON_LEFT)
		return mouse.left.isKeyPressed();

	if (button == SDL_BUTTON_RIGHT)
		return mouse.right.isKeyPressed();

	if (button == SDL_BUTTON_MIDDLE)
		return mouse.middle.isKeyPressed();

	return false;
}


bool InputManager::isKeyJustDown(unsigned int key) {
	bool b = false;
	auto iter = keys.find(key);
	if (iter != keys.end())
		b = iter->second.isKeyJustDown();

	return b;
}

bool InputManager::isKeyJustUp(unsigned int key) {
	bool b = false;
	auto iter = keys.find(key);
	if (iter != keys.end())
		b = iter->second.isKeyJustUp();

	return b;
}

bool InputManager::isKeyPressed(unsigned int key) {
	bool b = false;
	auto iter = keys.find(key);
	if (iter != keys.end())
		b = iter->second.isKeyPressed();

	return b;
}

int InputManager::GetVerticalDelta() {
	return MouseWheelDelta;
}
