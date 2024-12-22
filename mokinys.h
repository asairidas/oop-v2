#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

#include "statistika.h"
#include "zmogus.h"

class Mokinys : public Zmogus
{
private:
    double egzaminas_;
    std::vector<double> nd_;

public:
    double galutinis;
    Mokinys() : Zmogus(), egzaminas_(0), galutinis(0) {}; // default constructor
    Mokinys(std::istream &);

    // copy constructor
    inline Mokinys(const Mokinys &m) : Zmogus(m), egzaminas_(m.egzaminas_), nd_(m.nd_) {}
    inline ~Mokinys() {} // destructor

    // copy assignment operator
    Mokinys &operator=(const Mokinys &m);

    double galBalas(double (*)(std::vector<double>)) const;
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }

    inline int ndSize() const { return nd_.size(); }

    std::istream &readStudent(std::istream &); // setters

    friend std::istream &operator>>(std::istream &is, Mokinys &m)
    {
        return m.readStudent(is);
    }

    friend std::ostream &operator<<(std::ostream &os, const Mokinys &m)
    {
        os << m.vardas() << " " << m.pavarde() << " ";
        for (auto pazymys : m.nd_)
        {
            os << pazymys << " ";
        }
        os << m.egzaminas_ << std::endl;
        return os;
    }

    virtual void spausdink() const override;
};

bool compare(const Mokinys &, const Mokinys &);
bool comparePagalPavarde(const Mokinys &, const Mokinys &);
bool comparePagalEgza(const Mokinys &, const Mokinys &);

#endif
