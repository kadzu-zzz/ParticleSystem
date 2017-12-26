#pragma once

#include <glm\vec2.hpp>
#include <unordered_map>

struct KeyPress;
struct Mouse;

class InputManager {
public:
	static void update();
	static void updateKey(unsigned int key, bool state);
	static void updateMouseButton(unsigned int button, bool state);
	static void updateMouseWheel(int verticalDelta);

	static glm::vec2 getMouseLocation();

	static bool isMouseJustDown(unsigned int button);
	static bool isMouseJustUp(unsigned int button);
	static bool isMousePressed(unsigned int button);

	static bool isKeyJustDown(unsigned int key);
	static bool isKeyJustUp(unsigned int key);
	static bool isKeyPressed(unsigned int key);

	static int GetVerticalDelta();
private:
	static std::unordered_map<unsigned short, KeyPress> keys;
	static Mouse mouse;
	static int MouseWheelDelta;
};

