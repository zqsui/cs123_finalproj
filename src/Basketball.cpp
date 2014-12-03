#include "Basketball.h"

Basketball::Basketball(glm::vec3 pos, float mass)
{
    m_pos = pos;
    m_mass = mass;
    m_vel = glm::vec3(0.0);
    updateEnergy();


    m_isScored = false;
    m_isDisappeard = false;
    m_isFired = false;

}

Basketball::~Basketball()
{
}

bool Basketball::isFired()
{
    return m_isFired;
}

bool Basketball::isScored()
{
    return m_isScored;
}

float Basketball::getEnergy()
{
    return m_energy;
}

void Basketball::updateEnergy()
{
    m_energy = m_mass * GRAVITY * m_pos.y + 1.0 /2 * m_mass * glm::length(m_vel)*glm::length(m_vel);
}

glm::vec3 Basketball::getPos()
{
    return m_pos;
}

glm::vec3 Basketball::getVel()
{
    return m_vel;
}

float Basketball::getMass()
{
    return m_mass;
}

void Basketball::updateVel(glm::vec3 vel)
{
    m_vel = vel;
    updateEnergy();
}

void Basketball::updatePos(glm::vec3 pos)
{
    m_pos = pos;
    updateEnergy();
}
void Basketball::fireBasketball()
{
    m_isFired = true;
}
