#ifndef BASKETBALL_H
#define BASKETBALL_H

#include "GL/glew.h"
#include "glm/glm/glm.hpp"

#define GRAVITY 9.8

class Basketball
{
public:
    Basketball(glm::vec3 pos, float mass);
    virtual ~Basketball();

    bool isFired();
    bool isScored();
    bool isDisappeared();
    float getEnergy();
    void updateEnergy();
    glm::vec3 getPos();
    glm::vec3 getVel();
    float getMass();
    void updateVel(glm::vec3 vel);
    void updatePos(glm::vec3 pos);
    void fireBasketball();


private:
     glm::vec3 m_pos;
     glm::vec3 m_vel;
     float m_energy;
     bool m_isScored;
     bool m_isDisappeard;
     float m_mass;
     bool m_isFired;

};

#endif // BASKETBALL_H
