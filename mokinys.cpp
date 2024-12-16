#ifndef MOKINYS_CPP
#define MOKINYS_CPP
#include "mokinys.h"
#include "statistika.h"

std::istream &Studentas::readStudent(std::istream &is)
{
    is >> vardas_ >> pavarde_;
    double nd_pazymys;
    while (is >> nd_pazymys)
    {
        nd_.push_back(nd_pazymys);
    }
    egzaminas_ = nd_.back();
    nd_.pop_back();
    return is;
}

Studentas::Studentas(std::istream &is)
{
    readStudent(is);
}

inline std::string Studentas::vardas() const { return vardas_; }   // getters, inline
inline std::string Studentas::pavarde() const { return pavarde_; } // getters, inline

double Studentas::galBalas(double (*func)(std::vector<double>) = skaiciuoti_mediana) const
{
    return func(nd_) * 0.4 + egzaminas_ * 0.6;
}

bool compare(const Studentas &a, const Studentas &b)
{
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas &a, const Studentas &b)
{
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas &a, const Studentas &b)
{
    return a.galBalas() < b.galBalas();
}

#endif MOKINYS_CPP
