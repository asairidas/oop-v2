
#include "mokinys.h"
#include "statistika.h"

using namespace std;

Mokinys::Mokinys() : Zmogus(), egzaminas_(0), galutinis(0) {}; // numatytasis konstruktorius
Mokinys::Mokinys(const Mokinys &m) : Zmogus(m), egzaminas_(m.egzaminas_), nd_(m.nd_) {}

Mokinys::~Mokinys() {} // destruktorius
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

double Mokinys::galBalas(double (*priskyrimoFunkcija)(vector<double>) = skaiciuoti_mediana) const
{
    return priskyrimoFunkcija(nd_) * 0.4 + egzaminas_ * 0.6;
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

void Mokinys::spausdink() const
{
    cout << vardas_ << " " << pavarde_ << " ";
    for (auto pazymys : nd_)
    {
        cout << pazymys << " ";
    }
    cout << egzaminas_ << std::endl;
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

istream &operator>>(istream &is, Mokinys &m)
{
    return m.readStudent(is);
}

ostream &operator<<(ostream &os, const Mokinys &m)
{
    os << m.vardas() << " " << m.pavarde() << " ";
    for (auto pazymys : m.nd_)
    {
        os << pazymys << " ";
    }
    os << m.egzaminas_ << endl;
    return os;
}
