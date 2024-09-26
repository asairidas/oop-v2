#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Mokinys
{
    string vardas;
    string pavarde;
    int namu_darbu_kiekis{0};
    vector<int> namu_darbu_rezultatai;
    int egzamino_rezultatas{0};
};

double skaiciuoti_vidurki(Mokinys m)
{
    double vidurkis = 0;
    for (int j = 0; j < m.namu_darbu_rezultatai.size(); j++)
    {
        vidurkis += m.namu_darbu_rezultatai[j];
    }
    return vidurkis / m.namu_darbu_rezultatai.size();
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
    return m;
}

int main()
{

    int studentu_skaicius(0);
    cout << "Iveskite studentu skaiciu" << endl;
    cin >> studentu_skaicius;

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
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis(vid.)" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < mokiniai.size(); i++)
    {
        auto vidurkis = skaiciuoti_vidurki(mokiniai[i]);
        cout << left << setw(15) << mokiniai[i].vardas << setw(15) << mokiniai[i].pavarde << setw(20) << vidurkis << endl;
    }

    return 0;
}
