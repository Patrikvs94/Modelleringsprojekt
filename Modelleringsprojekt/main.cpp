#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Particle.h"

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
	Transform transform2;
	Camera camera(glm::vec3(0, 0, 50), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	// Set the objects startposition here
	transform.SetPos(glm::vec3(0.0f , 17.0f , 0.0f));
	transform2.SetPos(glm::vec3(0.0f, 10.0f, 0.0f));

	glm::vec3 particleArray[2] = { glm::vec3(0.0f , 17.0f , 0.0f), glm::vec3(0.0f, 10.0f, 0.0f) };

	Particle tinyP(particleArray);


	// Setting up for verlet, the old position and new position are default set to the apes position
	//glm::vec3 oldPos = transform.GetPos() + glm::vec3( 0.0f, 0.0f, 0.0f);
	//glm::vec3 newPos = transform.GetPos();
	//glm::vec3 acceleration = glm::vec3(0.0f, -9.82f, 0.0f);
	//float timeStep = 0.001f;

	glm::vec3 floor = glm::vec3(-20.0f, 0.0f, -20.0f);
	glm::vec3 roof = glm::vec3(25.0f, 50.0f, 20.0f);


	float counter = 0.0f;

	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		transform.GetRot().y = counter;

		tinyP.TimeStep();

		//std::cout << "TinyP position x: " << tinyP.GetFirstPos().x << " position y: " << tinyP.GetFirstPos().y << " position z: " << tinyP.GetFirstPos().z << std::endl ;
		//std::cout << "TinyP 2 position x: " << tinyP.GetSecPos().x << " position y: " << tinyP.GetSecPos().y << " position z: " << tinyP.GetSecPos().z << std::endl;

		transform.SetPos(tinyP.GetFirstPos());

		transform2.SetPos(tinyP.GetSecPos());
	
		shader.Bind();

		shader.Update(transform, camera);
		mesh.Draw();


		shader.Update(transform2, camera);
		mesh2.Draw();


		display.Update();
		counter += 0.001f;
	}



	return 0;
}