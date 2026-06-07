#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "Shader.h"
#include "VertexData.h"

class QuadRenderer
{
	private:
		Shader shader;
		VertexData vertexData;
		unsigned int textureId;
		unsigned int width;
		unsigned int height;
		float* pixels;

	public:
		QuadRenderer(unsigned int width, unsigned int height);
		~QuadRenderer();
		void setPixel(unsigned int i, unsigned int j, float r, float g, float b);
		void render();

};

#endif // !QUADRENDERER_H

