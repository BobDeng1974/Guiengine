#pragma once
#include <GL/glew.h>
#include <string>

namespace Guiengine {

    struct GLTexture {
		std::string filePath = "";
		GLuint id;
        int width;
        int height;
    };
}