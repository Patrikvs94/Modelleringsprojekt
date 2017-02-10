#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);

	//use the code from this shader to the GPU
	void Bind();

	virtual ~Shader();
protected:
private:
	//number of shaders; 2 in this case; fragment and vertex
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other){}
	void operator=(const Shader& other) {}


	

	//a handle 
	GLuint m_program;

	//an array of GLuints; the number of shaders used
	GLuint m_shaders[NUM_SHADERS];

};

