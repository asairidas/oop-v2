#ifndef mokinys_h
#define mokinys_h

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

#include "statistika.h"

using namespace std;

class Mokinys
{
private:
    string vardas_;
    string pavarde_;
    double egzaminas_;
    vector<double> nd_;

public:
    double galutinis;
    Mokinys() : egzaminas_(0), galutinis(0) {}; // numatytasis konstruktorius
    Mokinys(istream &);                         // konstruktorius

    // kopijavimo konstruktorius

    inline Mokinys(const Mokinys &m) : vardas_(m.vardas_), pavarde_(m.pavarde_), egzaminas_(m.egzaminas_), nd_(m.nd_) {}
    inline ~Mokinys() {} // destruktorius

    // kopijavimo priskyrimo operatorius
    Mokinys &operator=(const Mokinys &m);

    inline std::string vardas() const { return vardas_; }   // geteriai
    inline std::string pavarde() const { return pavarde_; } // geteriai
    double galBalas(double (*)(vector<double>)) const;

    inline int ndSize() const { return nd_.size(); } // geteriai

    std::istream &readStudent(istream &); // seteris

    friend istream &operator>>(istream &is, Mokinys &m)
    {
        return m.readStudent(is);
    }

    // funkcija rasymui i faila

    /*
    Operatorius friend, skirtas išvesti Mokinys objektą į srautą, naudojant << operatoriu.
    friend leidzia nuskaityti duomenis is privaciu kintamuju.
    Jis išveda mokinio vardą, pavardę, namų darbų pažymius ir egzamino pažymį.

    os Išvesties srautas.

    m Mokinys objektas, kurio duomenys bus išvesti.
    */

    friend ostream &operator<<(ostream &os, const Mokinys &m)
    {
        os << m.vardas_ << " " << m.pavarde_ << " ";
        for (auto pazymys : m.nd_)
        {
            os << pazymys << " ";
        }
        os << m.egzaminas_ << endl;
        return os;
    }
};

bool compare(const Mokinys &, const Mokinys &);
bool comparePagalPavarde(const Mokinys &, const Mokinys &);
bool comparePagalEgza(const Mokinys &, const Mokinys &);

#endif
