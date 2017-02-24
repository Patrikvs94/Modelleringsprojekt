#pragma once
#include<glm/glm.hpp>
#include<iostream>

#define NUM_PARTICLES 4

class Particle
{
	glm::vec3 m_pos[8];
	glm::vec3 m_oldPos[8];
	glm::vec3 m_force[8];
	glm::vec3 m_gravity;

	float fTimeStep;
	float restlength = 5.0f;

public:

	Particle(glm::vec3 position[]);
	~Particle();

	void TimeStep();
	glm::vec3 GetPos(int i);

private:

	void verlet();
	void satisfyConstraints();
	void AccumulateForces();

};

