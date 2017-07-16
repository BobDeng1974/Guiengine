#pragma once
#include "GLSLProgram.h"
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>
namespace Guiengine {
	class DebugRender
	{
	public:
		DebugRender();
		~DebugRender();

		void init();
		void end();
		void drawLine(const glm::vec2& a, const glm::vec2& b, const ColorRGBA& color);
		void drawBox(const glm::vec4& destRect, const ColorRGBA& color, float angle);
		void drawCircle(const glm::vec2& center, const ColorRGBA& color, float radius);
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		void dispose();

		struct DebugVertex {
			glm::vec2 position;
			ColorRGBA color;
		};

	private:
		GLSLProgram m_program;
		std::vector<DebugVertex> m_verts;
		std::vector<GLuint> m_indices;
		GLuint m_vbo, m_vao,m_ibo;
		int m_numElements = 0;
	};
}

