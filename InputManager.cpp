#include "InputManager.h"

namespace Guiengine {

	InputManager::InputManager():m_mouseCoords(0.0f,0.0f)
	{
	}

	void InputManager::update() {
		for (auto& it : m_mapKey) {
			m_previousMapKey[it.first] = it.second;
		}
	}
	void InputManager::pressKey(unsigned int keyID) {
		m_mapKey[keyID] = true;

	}
	void InputManager::releaseKey(unsigned int keyID) {
		m_mapKey[keyID] = false;
	}
	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = m_mapKey.find(keyID);
		if (it != m_mapKey.end()) {
			return (*it).second;
		}
		else {
			return false;
		}
	}

	void InputManager::setMouseCoords(glm::vec2 coords) {
		m_mouseCoords = coords;
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		auto it = m_previousMapKey.find(keyID);
		if (it != m_previousMapKey.end()) {
			return (*it).second;
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		return !wasKeyDown(keyID) && isKeyDown(keyID);
	}

	InputManager::~InputManager()
	{
	}
}