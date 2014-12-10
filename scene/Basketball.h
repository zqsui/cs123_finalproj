#ifndef BASKETBALL_H
#define BASKETBALL_H

#include "GL/glew.h"
#include "glm/glm/glm.hpp"

#define GRAVITY 15.8

class Basketball
{
public:
    Basketball(glm::vec3 pos, float mass, float radius);
    virtual ~Basketball();

    bool isFired();
    bool isScored();
    bool isDisappeared();
    float getEnergy();
    void updateEnergy();
    glm::vec3 getPos();
    glm::vec3 getVel();
    void setScored();
    float getMass();
    void updateVel(glm::vec3 vel);
    void updatePos(glm::vec3 pos);
    void fireBasketball();
    void setRadius(float radius);
    float getRadius();
    void setPower(int power);
    int getPower();
    void setDisappear();
    void updateSpin(int spin);
    int getSpin();



private:
     glm::vec3 m_pos;
     glm::vec3 m_vel;
     float m_energy;
     bool m_isScored;
     bool m_isDisappeard;
     float m_mass;
     bool m_isFired;
     float m_radius;

     int m_power;
     int m_spin;

};

#endif // BASKETBALL_H
