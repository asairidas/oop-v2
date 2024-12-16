#ifndef MOKINYS_CPP
#define MOKINYS_CPP
#include "mokinys.h"
#include "statistika.h"

std::istream &Mokinys::readStudent(std::istream &is)
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

Mokinys::Mokinys(std::istream &is)
{
    readStudent(is);
}

inline std::string Mokinys::vardas() const { return vardas_; }   // getters, inline
inline std::string Mokinys::pavarde() const { return pavarde_; } // getters, inline

double Mokinys::galBalas(double (*func)(std::vector<double>) = skaiciuoti_mediana) const
{
    return func(nd_) * 0.4 + egzaminas_ * 0.6;
}

bool compare(const Mokinys &a, const Mokinys &b)
{
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Mokinys &a, const Mokinys &b)
{
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Mokinys &a, const Mokinys &b)
{
    return a.galBalas() < b.galBalas();
}

#endif MOKINYS_CPP
