#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "Transform.h"

int main(int argc, char** argv)
{

	Display display(800, 600, "Hello world!");

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Transform transform;

	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear(1.0f, 1.0f, 0.15f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinf(counter);
		transform.GetRot().z = counter * 50;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		
		shader.Bind();
		shader.Update(transform);
		texture.Bind(0);
		mesh.Draw();

		display.Update();
		counter += 0.01f;
	}

	return 0;
}