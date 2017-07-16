#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Guiengine{

enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

class Glyph {
public:
	Glyph() {}
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA& color,float angle);
	
    GLuint texture;
    float depth;
    
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(const glm::vec2& vect, float angle);
};

class RenderBatch {
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
        numVertices(NumVertices), texture(Texture) {
    }
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    void init();

    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();

	void dispose();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA& color);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA& color, float angle);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA& color, const glm::vec2& dir);
    void renderBatch();

private:
    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();

    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);

	

    GLuint m_vbo;
    GLuint m_vao;

    GlyphSortType m_sortType;
	std::vector<Glyph*> m_glyphPointers;///>This is the sorting
    std::vector<Glyph> m_glyphs;///<This are the actual glyphs
    std::vector<RenderBatch> m_renderBatches;
};

}