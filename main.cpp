#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;
// #include "MyLib.h"
struct Mokinys
{
    string vardas;
    string pavarde;
    int namu_darbu_kiekis{0};
    vector<int> namu_darbu_rezultatai;
    int egzamino_rezultatas{0};
};

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

Mokinys nuskaityti_mokinio_duomenis()
{
    Mokinys m;
    cout << "Iveskite varda:" << endl;
    cin >> m.vardas;
    cout << "Ivedete varda " << m.vardas << endl;
    cout << "Iveskite pavarde" << endl;
    cin >> m.pavarde;
    cout << "Ivedete pavarde " << m.pavarde << endl;

    string str_pazymys;
    cout << "Iveskite pazymi (arba paspauskite Enter, kad baigtumete): ";
    cin.ignore(10, '\n'); // Ignoruojame likusią eilutę po paskutinio cin
    while (getline(cin, str_pazymys) && !str_pazymys.empty())
    {
        int pazymys = stoi(str_pazymys);
        m.namu_darbu_rezultatai.push_back(pazymys);
        cout << "Iveskite pazymi (arba paspauskite Enter, kad baigtumete): ";
    }

    cout << "Iveskite egzamino rezultata" << endl;
    cin >> m.egzamino_rezultatas;
    cout << "Ivedete egzamino rezultata " << m.egzamino_rezultatas << endl;

    return m;
}

double skaiciuoti_galutini(Mokinys m, string pasirinkimas)
{
    double vid_med = 0;
    if (pasirinkimas == "med")
    {
        vid_med = skaiciuoti_mediana(m);
    }
    else
    {
        vid_med = skaiciuoti_vidurki(m);
    }
    double galutinis = 0.4 * vid_med + 0.6 * m.egzamino_rezultatas;
    return galutinis;
}

int main()
{

    int studentu_skaicius(0);
    cout << "Iveskite studentu skaiciu" << endl;
    cin >> studentu_skaicius;

    cout << "Ko nori ar vidurkio ar medianos (iveskite 'vid' arba 'med')?" << endl;
    string pasirinkimas;
    cin >> pasirinkimas;
    if (pasirinkimas != "vid" && pasirinkimas != "med")
    {
        cerr << "Neteisingas pasirinkimas" << endl;
        return 1;
    }

    if (studentu_skaicius <= 0)
    {
        cerr << "Studentų skaičius turi būti teigiamas sveikasis skaičius." << endl;
        return 1;
    }

    vector<Mokinys> mokiniai;

    for (int k = 0; k < studentu_skaicius; ++k)
    {
        Mokinys m = nuskaityti_mokinio_duomenis();
        mokiniai.push_back(m);
    }

    string skaiciavimo_budas;
    if (pasirinkimas == "vid")
    {
        skaiciavimo_budas = "(vid.)";
    }
    else
    {
        skaiciavimo_budas = "(med.)";
    }
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << left << "Galutinis" << skaiciavimo_budas << endl;

    cout << "------------------------------------------" << endl;
    for (int i = 0; i < mokiniai.size(); i++)
    {
        auto galutinis = skaiciuoti_galutini(mokiniai[i], pasirinkimas);
        cout << left << setw(15) << mokiniai[i].vardas << setw(15) << mokiniai[i].pavarde << left << galutinis << endl;
    }

    return 0;
}
