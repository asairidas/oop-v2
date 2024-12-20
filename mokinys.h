#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

#include "statistika.h"

class Mokinys
{
private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    std::vector<double> nd_;

public:
    double galutinis;
    Mokinys() : egzaminas_(0), galutinis(0) {}; // defult constructor
    Mokinys(std::istream &);

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    double galBalas(double (*)(std::vector<double>)) const;

    inline int ndSize() const { return nd_.size(); }

    std::istream &readStudent(std::istream &); // setters
    // funkcija rasymui i faila

    friend std::ostream &operator<<(std::ostream &os, const Mokinys &m)
    {
        os << m.vardas_ << " " << m.pavarde_ << " ";
        for (auto pazymys : m.nd_)
        {
            os << pazymys << " ";
        }
        os << m.egzaminas_ << std::endl;
        return os;
    }
};

bool compare(const Mokinys &, const Mokinys &);
bool comparePagalPavarde(const Mokinys &, const Mokinys &);
bool comparePagalEgza(const Mokinys &, const Mokinys &);

#endif
