#pragma once

class Wombleroot;
class Wittentoot;
class Woreroot;

/// class of the abstract Radiations
class Radiation {
public:
    virtual Radiation* changeRad(Wombleroot *p) = 0;
    virtual Radiation* changeRad(Wittentoot *p) = 0;
    virtual Radiation* changeRad(Woreroot   *p) = 0;
    virtual ~Radiation() {}
};

/// class of Alpha
class Alpha : public Radiation
{
public:
    static Alpha* instance();
    Radiation* changeRad(Wombleroot *p) override;
    Radiation* changeRad(Wittentoot *p) override;
    Radiation* changeRad(Woreroot   *p) override;
    static void destroy() ;
protected:
    Alpha(){}
private:
    static Alpha* m_instance;
};

/// class of Delta
class Delta : public Radiation
{
public:
    static Delta* instance();
    Radiation* changeRad(Wombleroot *p) override;
    Radiation* changeRad(Wittentoot *p) override;
    Radiation* changeRad(Woreroot   *p) override;
    static void destroy() ;
protected:
    Delta(){}
private:
    static Delta* m_instance;
};

/// class of noRadiation
class noRadiation : public Radiation
{
public:
    static noRadiation* instance();
    Radiation* changeRad(Wombleroot *p) override;
    Radiation* changeRad(Wittentoot *p) override;
    Radiation* changeRad(Woreroot   *p) override;
    static void destroy() ;
protected:
    noRadiation(){}
private:
    static noRadiation* m_instance;
};

