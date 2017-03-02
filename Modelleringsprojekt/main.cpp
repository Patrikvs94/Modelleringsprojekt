#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Particle.h"

#define WIDTH 1064
#define HEIGHT 800

int main(int argc, char** argv)
{

	Display display(WIDTH, HEIGHT, "Modelleringsprojektet #1!");

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
	Transform transform[8];
	Camera camera(glm::vec3(0, 0, 100), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	// Set the objects startposition here
	transform[0].SetPos(glm::vec3(1.0f, 8.0f, 1.0f));
	transform[1].SetPos(glm::vec3(1.0f, 13.0f, 1.0f));
	transform[2].SetPos(glm::vec3(1.0f, 7.0f, 1.0f));
	transform[3].SetPos(glm::vec3(-1.0f, 7.0f, 1.0f));

	glm::vec3 particleArray[NUM_PARTICLES] = {  glm::vec3(1.0f , 20.0f , 1.0f), 
								    glm::vec3(1.0f, 25.0f, 1.0f),
									glm::vec3(6.0f, 20.0f, 1.0f), 
									glm::vec3(1.0f, 20.0f, 6.0f), 
									};

	Particle tinyP(particleArray);

	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
 
		tinyP.TimeStep();

		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			transform[i].SetPos(tinyP.GetPos(i));
		}
	
		shader.Bind();

		for (int j = 0; j < NUM_PARTICLES; j++)
		{
			shader.Update(transform[j], camera);
			mesh2.Draw();

		}

		display.Update();
		counter += 0.001f;
	}



	return 0;
}