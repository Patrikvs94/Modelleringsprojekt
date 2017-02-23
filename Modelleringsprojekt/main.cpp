#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{

	Display display(1064, 800, "Modelleringsprojektet #1!");

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };

	unsigned int indices[] = { 0, 1 ,2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");

	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Transform transform;
	Camera camera(glm::vec3(0, 0, 50), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	// Set the objects startposition here
	transform.SetPos(glm::vec3( -15.0f , 30.0f , 0.0f));

	glm::vec3 oldPos = transform.GetPos() + glm::vec3( -0.01f, 0.0f, 0.0f);
	glm::vec3 newPos = transform.GetPos();
	glm::vec3 acceleration = glm::vec3(0.0f, -9.82f, 0.0f);
	float timeStep = 0.001f;

	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.GetRot().y = counter;
		newPos += (transform.GetPos() - oldPos) + (acceleration * timeStep * timeStep);
		oldPos = transform.GetPos();
		transform.SetPos(newPos);
		glm::vec3 position = transform.GetPos();
		std::cout << "Y Position: " << position.y << "X Position: " << position.x << " counter: " << counter << std::endl;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		
		shader.Bind();
		shader.Update(transform, camera);
		texture.Bind(0);
		mesh2.Draw();

		display.Update();
		counter += 0.001f;
	}

	return 0;
}