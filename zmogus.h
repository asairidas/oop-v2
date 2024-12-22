#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus
{
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() : vardas_(""), pavarde_("") {};
    Zmogus(const std::string &vardas, const std::string &pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() = default;

    virtual void spausdink() const = 0; // grynoji virtualioji funkcija
};

#endif // ZMOGUS_H