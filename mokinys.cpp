
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

Mokinys &Mokinys::operator=(const Mokinys &m)
{
    if (this != &m)
    {
        vardas_ = m.vardas_;
        pavarde_ = m.pavarde_;
        egzaminas_ = m.egzaminas_;
        nd_ = m.nd_;
    }
    return *this;
}
