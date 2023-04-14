#pragma once

#include <string>
#include "Radiation.h"

///class of Plants
class Plants{
protected:
    std::string name;
    int nutrient;
    Plants (const std::string &name, int n = 0) :name(name), nutrient(n) {}
public:
    std::string getName() const { return name; }
    int getNutrient() const {
        return nutrient;
    }
    virtual bool alive() const { return nutrient > 0; }
    void changeNutritient(int n) { nutrient += n; }
    virtual void changeRad(Radiation* &radiation) = 0;
    virtual std::string getType() = 0;
    virtual ~Plants () {}
};

///class of Womblerootes
class Wombleroot : public Plants {
public:
    Wombleroot(const std::string &name, int n = 0) : Plants(name, n){}
    void changeRad(Radiation* &radiation) override {
        radiation = radiation->changeRad(this);
    }
    bool alive() const override{
        if(nutrient > 0 && nutrient <= 10){
            return true;
        }
        return false;
    }
    std::string getType() override {
        return "wom";
    }
};

/// class of Wittentoot
class Wittentoot : public Plants {
public:
    Wittentoot(const std::string &name, int n = 0) : Plants(name, n){}
    void changeRad(Radiation* &radiation) override {
        radiation = radiation->changeRad(this);
    }
    std::string getType() override {
        return "wit";
    }
};

/// class of Woreroot
class Woreroot : public Plants {
public:
    Woreroot(const std::string &name, int n = 0) : Plants(name, n){}
    void changeRad(Radiation* &radiation) override{
        radiation = radiation->changeRad(this);
    }
    std::string getType() override {
        return "wor";
    }
};


