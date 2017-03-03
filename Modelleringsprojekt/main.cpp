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

	// 
	Vertex vertices[] = {	Vertex(glm::vec3(-20.0, 0.0, -10.0), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(-20.0, 0.0, 20.0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(20.0, 0.0, -10.0), glm::vec2(1.0, 0.0)),
							Vertex(glm::vec3(20.0, 0.0, 20.0), glm::vec2(1.0, 1.0))
	};

	unsigned int indices[] = {  1, 3 ,2,
								2, 0, 1};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");

	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Transform transform;
	Camera camera(glm::vec3(0, 20, 150), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	SDL_Event e;

	// This sets the start positions of the particles, 
	// they must be approximately the distance from each other that is set to be the constraint in the "Particle.cpp"
	glm::vec3 particleArray[NUM_PARTICLES] = {  glm::vec3(1.0f , 40.0f , 1.0f), 
								    glm::vec3(1.0f, 45.0f, 1.0f),
									glm::vec3(6.0f, 40.0f, 1.0f), 
									glm::vec3(1.0f, 40.0f, 6.0f), 
									};

	// This is where the object is declared, it is required to send in a set of particle positions that make up the tetrahedron,
	// At this point it is only possible to send in an array of size 4.
	Particle tinyP(particleArray);

	float counter = 0.0f;



	while (!display.IsClosed())
	{
		// Setting the background color
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		// Initialiaze the movement of tinyP, which in this cas is our tetrahedron,
		tinyP.TimeStep();

		// This is needed to bind all what is happening to the shader
		shader.Bind();

		// This loop is going through and updates the position from the tinyP to the shader and drawing a line between particles
		glPushMatrix();
		for (int j = 0; j < NUM_PARTICLES; j++)
		{
			shader.Update(tinyP.GetPos(j), camera);

			//start drawin particles
			glLineWidth(2.5f);
			glBegin(GL_LINES);

			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				for (int k = i + 1; k < NUM_PARTICLES; k++)
				{
					glVertex3f(tinyP.GetPos(i).x, tinyP.GetPos(i).y, tinyP.GetPos(i).z);
					glVertex3f(tinyP.GetPos(k).x, tinyP.GetPos(k).y, tinyP.GetPos(k).z);
				}
			}
				

			glEnd();

		}
		glPopMatrix();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					tinyP.applyForce();
					std::cout << "force Applied" << std::endl;
				}
			}
		}
		// Updates the screen
		//shader.Update(transform, camera);
		//transform.SetScale(glm::vec3(2.5f, 2.5f, 2.5f));
		//mesh.Draw();
		display.Update();
	}



	return 0;
}