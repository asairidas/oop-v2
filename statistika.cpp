#include <algorithm>
#include "mokinys.h"

double skaiciuoti_vidurki(Mokinys &m)
{
    // jeigu pazymiu nera grazina 0
    if (m.namu_darbu_rezultatai.size() == 0)
    {
        return 0;
    }

    double nd_suma = 0;
    double vidurkis = 0;
    for (int j = 0; j < m.namu_darbu_rezultatai.size(); j++)
    {
        nd_suma += m.namu_darbu_rezultatai[j];
    }
    vidurkis = nd_suma / m.namu_darbu_rezultatai.size();
    return vidurkis;
}

double skaiciuoti_mediana(Mokinys &m)
{
    double mediana = 0;
    sort(m.namu_darbu_rezultatai.begin(), m.namu_darbu_rezultatai.end());
    if (m.namu_darbu_rezultatai.size() % 2 == 0)
    {
        auto pirmas = m.namu_darbu_rezultatai[m.namu_darbu_rezultatai.size() / 2 - 1];
        auto antras = m.namu_darbu_rezultatai[m.namu_darbu_rezultatai.size() / 2];
        mediana = (pirmas + antras) / 2.0;
    }
    else
    {
        mediana = m.namu_darbu_rezultatai[m.namu_darbu_rezultatai.size() / 2];
    }
    return mediana;
}