#pragma once

#include<glm\glm.hpp>

class ParticleSystem
{
	glm::vec3 m_x[10];    // Current positions
	glm::vec3 m_oldx[10]; // Previous positions
	glm::vec3 m_a[10];    // Force accumulators
	glm::vec3 m_vGravity;            // Gravity
	float m_fTimeStep;
public:
	void TimeStep();
private:
	void Verlet();
	void SatisfyConstraints();
	void AccumulateForces();
	// (constructors, initialization etc. omitted)
};

