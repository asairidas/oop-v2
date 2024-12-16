#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>

#include "statistika.h"

class Mokinys
{
private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    std::vector<double> nd_;

public:
    Mokinys() : egzaminas_(0) {} // default constructor
    Mokinys(std::istream &);

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    double galBalas(double (*)(std::vector<double>) = skaiciuoti_mediana) const;

    std::istream &readStudent(std::istream &); // setters
};

bool compare(const Mokinys &, const Mokinys &);
bool comparePagalPavarde(const Mokinys &, const Mokinys &);
bool comparePagalEgza(const Mokinys &, const Mokinys &);

#endif
