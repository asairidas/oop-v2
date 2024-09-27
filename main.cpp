#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

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
    double nd_suma = 0;
    double vidurkis = 0;
    for (int j = 0; j < m.namu_darbu_rezultatai.size(); j++)
    {
        nd_suma += m.namu_darbu_rezultatai[j];
    }
    vidurkis = nd_suma / m.namu_darbu_rezultatai.size();
    return 0.4 * vidurkis + 0.6 * m.egzamino_rezultatas;
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
    return 0.4 * mediana + 0.6 * m.egzamino_rezultatas;
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
    cout << "Iveskite namu darbu skaiciu" << endl;
    cin >> m.namu_darbu_kiekis;
    cout << "Ivedete " << m.namu_darbu_kiekis << endl;

    for (int i = 0; i < m.namu_darbu_kiekis; i++)
    {
        int pazymys;
        cout << "Iveskite pazymi nr " << i + 1 << endl;
        cin >> pazymys;
        m.namu_darbu_rezultatai.push_back(pazymys);
    }

    cout << "Iveskite egzamino rezultata" << endl;
    cin >> m.egzamino_rezultatas;
    cout << "Ivedete egzamino rezultata " << m.egzamino_rezultatas << endl;

    return m;
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
        double vid_med = 0;
        if (pasirinkimas == "med")
        {
            vid_med = skaiciuoti_mediana(mokiniai[i]);
        }
        else
        {
            vid_med = skaiciuoti_vidurki(mokiniai[i]);
        }

        cout << left << setw(15) << mokiniai[i].vardas << setw(15) << mokiniai[i].pavarde << left << vid_med << endl;
    }

    return 0;
}
