
#include "mokinys.h"
#include "statistika.h"

using namespace std;

istream &Mokinys::readStudent(istream &is)
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

Mokinys::Mokinys(istream &is)
{
    readStudent(is);
}

double Mokinys::galBalas(double (*skaiciavimoFunkcija)(vector<double>) = skaiciuoti_mediana) const
{
    return skaiciavimoFunkcija(nd_) * 0.4 + egzaminas_ * 0.6;
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
    // Patikriname, ar nepriskiriame objekto pačiam sau
    if (this != &m)
    {
        // Priskiriame visus laukus iš objekto m į esamą objektą
        vardas_ = m.vardas_;
        pavarde_ = m.pavarde_;
        egzaminas_ = m.egzaminas_;
        nd_ = m.nd_;
    }
    // Grąžiname nuorodą į esamą objektą
    return *this;
}
