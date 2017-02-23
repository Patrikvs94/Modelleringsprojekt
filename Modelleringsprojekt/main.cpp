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

	Vertex vertices[] = {	Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(0, -0.5, -0.5), glm::vec2(1.0, 1.0))
	};

	unsigned int indices[] = {  0, 2 ,1,
								2, 3 ,1,
								3, 0, 1,
								0, 3, 2};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");

	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Transform transform;
	Camera camera(glm::vec3(0, 0, 4), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	// Set the objects startposition here
	transform.SetPos(glm::vec3(0.0f , 3.0f , 0.0f));


	// Setting up for verlet, the old position and new position are default set to the apes position
	glm::vec3 oldPos = transform.GetPos() + glm::vec3( 0.0f, 0.0f, 0.0f);
	glm::vec3 newPos = transform.GetPos();
	glm::vec3 acceleration = glm::vec3(0.0f, -9.82f, 0.0f);
	float timeStep = 0.001f;

	glm::vec3 floor = glm::vec3(-20.0f, 0.0f, -20.0f);
	glm::vec3 roof = glm::vec3(25.0f, 50.0f, 20.0f);


	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		// en liten rotation, ej verlet
		transform.GetRot().y = 0.02f*counter;

		// Verlet part
		newPos += (transform.GetPos() - oldPos) + (acceleration * timeStep * timeStep);
		//newPos = glm::min(glm::max(newPos, floor), roof); //boundaries a la axel

		oldPos = transform.GetPos();

		//bound check a la patrik
		if (oldPos.y < 0)
			newPos.y = 0;


		transform.SetPos(newPos);
		glm::vec3 position = transform.GetPos();

		//test om det går att manipulera enkilda vertices, det gick men man måste skapa ny mesh varje gång
		//vertices[0] = Vertex(glm::vec3(sinf(counter), -0.5, 0.5), glm::vec2(0.0, 0.0));
		//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));


		// Prints the x and y coordinates to console, to see what happens with the ape
		std::cout << "Y Position: " << position.y << " X Position: " << position.x << " counter: " << counter << std::endl;

		
		shader.Bind();
		shader.Update(transform, camera);
		texture.Bind(0);
		mesh.Draw();
		mesh2.Draw();

		display.Update();
		counter += 0.001f;
	}



	return 0;
}