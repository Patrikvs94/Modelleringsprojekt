#pragma once
#include<glm/glm.hpp>
#include<iostream>

class Particle
{
	glm::vec3 m_pos[2];
	glm::vec3 m_oldPos[2];
	glm::vec3 m_force[2];
	glm::vec3 m_gravity;

	float fTimeStep;
	float restlength = 5.0f;

public:

	Particle(glm::vec3 position[]);
	~Particle();

	void TimeStep();
	glm::vec3 GetFirstPos();
	glm::vec3 GetSecPos();

private:

	void verlet();
	void satisfyConstraints();
	void AccumulateForces();

};

