#include "Camera2D.h"

namespace Guiengine {

    Camera2D::Camera2D() : m_position(0.0f, 0.0f),
        m_cameraMatrix(1.0f),
        m_orthoMatrix(1.0f),
        m_scale(1.0f),
        m_needsMatrixUpdate(true),
        m_screenWidth(500),
        m_screenHeight(500)
    {
    }


    Camera2D::~Camera2D()
    {
    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
    }

    //updates the camera matrix if needed
    void Camera2D::update() {

        //Only update if our position or scale have changed
        if (m_needsMatrixUpdate) {
            
            //Camera Translation
            glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

            //Camera Scale
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

            m_needsMatrixUpdate = false;
        }
    }

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCords) {
		//Invert y
		screenCords.y = m_screenHeight - screenCords.y;
		//Make that 0 is the center
		screenCords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		//Scale the coords
		screenCords /= m_scale;
		//translate the camara position.
		screenCords += m_position;
		return screenCords;
	}
	


	bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimentions) {
		glm::vec2 scaleScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);
		//Get the center position of player
		glm::vec2 centerPos = position + dimentions / (float)2;
		//Get the distance with the possible tile to colide
		glm::vec2 dist = centerPos - m_position;
		//Set the minumum distance
		const float MIN_DIST_Y = dimentions.y / (float)2 + scaleScreenDimensions.y/(float)2;
		const float MIN_DIST_X = (dimentions.x / (float)2) + scaleScreenDimensions.x/(float)2;

		float xdepth = MIN_DIST_X - abs(dist.x);
		float ydepth = MIN_DIST_Y - abs(dist.y);

		if (xdepth > 0 && ydepth > 0) {
			//There was colison
			return true;
		}
		return false;
	}
}