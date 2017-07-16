#pragma once

namespace Guiengine {
class FpsLimiter {
public:
	FpsLimiter();
	void init(float maxFps);
	void begin();
	int end();
private:
	float m_fps;
	unsigned int m_firstTicks;
	float m_maxFps;
	float m_frameTime;
	void calculateFps();

};



}