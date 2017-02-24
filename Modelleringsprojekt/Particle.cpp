#include "Particle.h"


Particle::Particle(glm::vec3 position[])
{
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		m_pos[i] = position[i] + glm::vec3(0.0f, 0.0f, 0.0f);
		m_oldPos[i] = position[i];
		m_force[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		m_gravity = glm::vec3(0.0f, -9.82f, 0.0f);
		fTimeStep = 0.01f;
	}

	//Applying velocity on the positions
	//m_pos[0] += glm::vec3(0.1f, 0.0f, 0.0f);
	//m_pos[1] += glm::vec3(0.0f, 0.0f, 0.2f);
}


Particle::~Particle()
{

}

void Particle::verlet() 
{
	for (int i = 0; i < NUM_PARTICLES; i++) 
	{
		glm::vec3& x = m_pos[i];
		glm::vec3 temp = x;
		glm::vec3& oldx = m_oldPos[i];
		glm::vec3& a = m_force[i];
		x += x - oldx + a*fTimeStep*fTimeStep;
		oldx = temp;
	}
}

void Particle::satisfyConstraints()
{

	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		for (int j = 0; j < NUM_PARTICLES; j++)
		{
			float& x = m_pos[j].x;
			float& y = m_pos[j].y;
			float& z = m_pos[j].z;

			x = glm::min(glm::max(x, -10.0f), 20.0f);
			y = glm::min(glm::max(y, 0.0f), 100.0f);
			z = glm::min(glm::max(z, 0.0f), 20.0f);


		}
		
		glm::vec3& x1 = m_pos[i];

		for (int k = i + 1; k < NUM_PARTICLES; k++)
		{
			glm::vec3& x2 = m_pos[k];



			std::cout << "Y positionen 1: " << m_pos[i].y << std::endl;
			std::cout << "Y positionen 2: " << m_pos[k].y << std::endl;

			glm::vec3 delta = x2 - x1;
			float deltalength = glm::sqrt((delta.x*delta.x) + (delta.y*delta.y) + (delta.z*delta.z));
			std::cout << "Deltalength: " << deltalength << std::endl;
			std::cout << "Restlength: " << restlength << std::endl;
			float diff = (deltalength - restlength) / deltalength;
			x1 += delta*0.5f*diff;
			x2 -= delta*0.5f*diff;
		}
	}
}

void Particle::AccumulateForces() 
{
	for(int i = 0; i < NUM_PARTICLES ; i++)
		m_force[i] = m_gravity;

}

void Particle::TimeStep() 
{
	AccumulateForces();
	verlet();
	satisfyConstraints();
}

glm::vec3 Particle::GetPos(int i)
{
	return m_pos[i];
}
