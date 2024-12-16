#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>

#include "statistika.h"

class Studentas
{
private:
    std::string vardas_;
    std::string pavarde_;
    double egzaminas_;
    std::vector<double> nd_;

public:
    Studentas() : egzaminas_(0) {} // default constructor
    Studentas(std::istream &);

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    double galBalas(double (*)(std::vector<double>) = skaiciuoti_mediana) const;

    std::istream &readStudent(std::istream &); // setters
};

bool compare(const Studentas &, const Studentas &);
bool comparePagalPavarde(const Studentas &, const Studentas &);
bool comparePagalEgza(const Studentas &, const Studentas &);

#endif
