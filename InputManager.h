#pragma once

#include <unordered_map>
#include <glm\glm.hpp>

namespace Guiengine {


class InputManager
{
public:
	InputManager();
	~InputManager();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	//true if the key is held down
	bool isKeyDown(unsigned int keyID);
	//true if key pressed only on this frame
	bool isKeyPressed(unsigned int keyID);
	void setMouseCoords(glm::vec2 coords);
	glm::vec2 getMouseCords() { return m_mouseCoords; }
	void update();
private:
	bool wasKeyDown(unsigned int keyID);
	std::unordered_map<unsigned int, bool> m_mapKey;
	std::unordered_map<unsigned int, bool> m_previousMapKey;
	glm::vec2 m_mouseCoords;
};
}

