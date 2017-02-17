#pragma once

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	//use the code from this shader to the GPU
	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();
protected:
private:
	//number of shaders; 2 in this case; fragment and vertex
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	void operator=(const Shader& other) {}

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	//a handle 
	GLuint m_program;

	//an array of GLuints; the number of shaders used
	GLuint m_shaders[NUM_SHADERS];

	GLuint m_uniforms[NUM_UNIFORMS];

};

