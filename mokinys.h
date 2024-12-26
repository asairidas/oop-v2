#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

#include "statistika.h"
#include "zmogus.h"

using namespace std;

class Mokinys : public Zmogus
{
private:
    double egzaminas_;
    vector<double> nd_;

public:
    double galutinis;
    Mokinys() : Zmogus(), egzaminas_(0), galutinis(0) {}; // numatytasis konstruktorius
    Mokinys(istream &);                                   // konstruktorius

    // kopijavimo konstruktorius
    inline Mokinys(const Mokinys &m) : Zmogus(m), egzaminas_(m.egzaminas_), nd_(m.nd_) {}
    inline ~Mokinys() {} // destruktorius

    // kopijavimo priskyrimo operatorius
    Mokinys &operator=(const Mokinys &m);

    double galBalas(double (*)(std::vector<double>)) const;
    inline string vardas() const { return vardas_; }   // geteriai
    inline string pavarde() const { return pavarde_; } // geteriai

    inline int ndSize() const { return nd_.size(); } // geteris

    istream &readStudent(istream &); // seteris

    friend istream &operator>>(istream &is, Mokinys &m)
    {
        return m.readStudent(is);
    }

    friend ostream &operator<<(ostream &os, const Mokinys &m)
    {
        os << m.vardas() << " " << m.pavarde() << " ";
        for (auto pazymys : m.nd_)
        {
            os << pazymys << " ";
        }
        os << m.egzaminas_ << endl;
        return os;
    }

    virtual void spausdink() const override;
};

bool compare(const Mokinys &, const Mokinys &);
bool comparePagalPavarde(const Mokinys &, const Mokinys &);
bool comparePagalEgza(const Mokinys &, const Mokinys &);

#endif
