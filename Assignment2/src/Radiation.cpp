#include "Radiation.h"
#include "Plants.h"

Alpha* Alpha::m_instance = nullptr;
Alpha* Alpha::instance()
{
    if(m_instance == nullptr) {
       m_instance = new Alpha();
    }
    return m_instance;
}

Radiation* Alpha::changeRad(Wombleroot* p){
    p->changeNutritient(2);
    return this;
}

Radiation* Alpha::changeRad(Wittentoot *p){
    p->changeNutritient(-3);
    return this;
}

Radiation* Alpha::changeRad(Woreroot *p){
    p->changeNutritient(1);
    return this;
}

Delta* Delta::m_instance = nullptr;
Delta* Delta::instance()
{
    if(m_instance == nullptr) {
       m_instance = new Delta();
    }
    return m_instance;
}

Radiation* Delta::changeRad(Wombleroot* p){
    p->changeNutritient(-2);
    return this;
}

Radiation* Delta::changeRad(Wittentoot *p){
    p->changeNutritient(4);
    return this;
}

Radiation* Delta::changeRad(Woreroot *p){
    p->changeNutritient(1);
    return this;
}

noRadiation* noRadiation::m_instance = nullptr;
noRadiation* noRadiation::instance()
{
    if(m_instance == nullptr) {
       m_instance = new noRadiation();
    }
    return m_instance;
}

Radiation* noRadiation::changeRad(Wombleroot* p){
    p->changeNutritient(-1);
    return this;
}

Radiation* noRadiation::changeRad(Wittentoot *p){
    p->changeNutritient(-1);
    return this;
}

Radiation* noRadiation::changeRad(Woreroot *p){
    p->changeNutritient(-1);
    return this;
}
