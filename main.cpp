#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <iterator>

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
    cout << "Iveskite pazymi (arba paspauskite Enter, kad baigtumete). Jei ivesite 0, bus sugeneruotas atsitiktinis balas: ";
    cin.ignore(10, '\n'); // Ignoruojame likusią eilutę po paskutinio cin
    while (getline(cin, str_pazymys) && !str_pazymys.empty())
    {
        int pazymys = stoi(str_pazymys);
        // jei pazymys yra 0 tai pakeiciame ji atsitiktiniu skaiciumi is intervalo [1, 10]
        if (pazymys == 0)
        {
            pazymys = rand() % 10 + 1;
            cout << "Sugeneruotas atsitiktinis pazymys: " << pazymys << endl;
        }
        m.namu_darbu_rezultatai.push_back(pazymys);
        cout << "Iveskite pazymi (arba paspauskite Enter, kad baigtumete): ";
    }

    cout << "Iveskite egzamino rezultata. Jei ivesite 0, bus sugeneruotas atsitiktinis balas:" << endl;
    cin >> m.egzamino_rezultatas;
    // jei pazymys yra 0 tai pakeiciame ji atsitiktiniu skaiciumi is intervalo [1, 10]
    if (m.egzamino_rezultatas == 0)
    {
        m.egzamino_rezultatas = rand() % 10 + 1;
        cout << "Sugeneruotas atsitiktinis pazymys: " << m.egzamino_rezultatas << endl;
    }

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

vector<Mokinys> duomenu_nuskaitymas_is_klaviaturos()
{
    int studentu_skaicius(0);
    while (true)
    {
        cout << "Iveskite studentu skaiciu" << endl;
        cin >> studentu_skaicius;
        if (studentu_skaicius <= 0)
        {
            cerr << "Studentų skaičius turi būti teigiamas sveikasis skaičius." << endl;
            continue; // prasykime vartotoja ivesti teisinga skaiciu
        }
        else
        {
            break; // jei skaicius teigiamas, nutraukime cikla
        }
    }

    vector<Mokinys> mokiniai;

    for (int k = 0; k < studentu_skaicius; ++k)
    {
        Mokinys m = nuskaityti_mokinio_duomenis();
        mokiniai.push_back(m);
    }
    return mokiniai;
}

vector<Mokinys> duomenu_nuskaitymas_is_failo(string failo_vardas)
{
    vector<Mokinys> mokiniai;

    // nuskaitome likusias eilutes ir sudedame i mokinio struktura
    // pridedame mokini i mokiniu vektoriu

    // atidarome faila
    ifstream ivedimo_failas(failo_vardas);
    if (!ivedimo_failas)
    {
        cerr << "Nepavyko atidaryti failo " << failo_vardas << endl;
        return mokiniai;
    }

    string eilute;
    getline(ivedimo_failas, eilute);
    // kad galetume naudoti iteratoriu reikia paversti stringa i istringstream
    istringstream iss(eilute);
    // nuskaitome pirma eilute ir suskaiciuojame kiek joje yra zodziu atskirtu tarpais, pagal tai nustatome kiek namu darbu irasu yra

    int namu_darbu_kiekis = 0;
    string zodis;
    while (iss >> zodis)
    {
        namu_darbu_kiekis++;
    }
    namu_darbu_kiekis -= 3; // atimame vardą, pavardę ir egzamino rezultatą

    while (getline(ivedimo_failas, eilute))
    {
        istringstream iss(eilute);
        Mokinys m;
        iss >> m.vardas >> m.pavarde;
        for (int i = 0; i < namu_darbu_kiekis; ++i)
        {
            int pazymys;
            iss >> pazymys;
            m.namu_darbu_rezultatai.push_back(pazymys);
        }
        iss >> m.egzamino_rezultatas;
        mokiniai.push_back(m);
    }

    ivedimo_failas.close();
    return mokiniai;
}

bool mokiniu_palygintojas(const Mokinys &kairys, const Mokinys &desinys)
{
    if (kairys.pavarde == desinys.pavarde)
    {
        return kairys.vardas < desinys.vardas;
    }
    return kairys.pavarde < desinys.pavarde;
}

int main()
{
    // leidziame vartotojui pasirinkti, ar duomenis ivesime is klaviaturos ar nuskaitysime is failo
    cout << "Ar norite ivesti duomenis is klaviaturos ar nuskaityti is failo? (iveskite 'klav' arba 'failas')" << endl;
    string pasirinkimas;
    cin >> pasirinkimas;
    if (pasirinkimas != "klav" && pasirinkimas != "failas")
    {
        cerr << "Neteisingas pasirinkimas" << endl;
        return 1;
    }

    vector<Mokinys> mokiniai;
    if (pasirinkimas == "klav")
    {

        mokiniai = duomenu_nuskaitymas_is_klaviaturos();
    }
    else
    {
        // nuskaitymas is failo
        // iveskite failo varda:

        cout << "Iveskite failo varda" << endl;
        string failo_vardas;
        cin >> failo_vardas;

        mokiniai = duomenu_nuskaitymas_is_failo(failo_vardas);
    }

    cout << "Ko nori ar vidurkio ar medianos (iveskite 'vid' arba 'med')?" << endl;
    cin >> pasirinkimas;
    if (pasirinkimas != "vid" && pasirinkimas != "med")
    {
        cerr << "Neteisingas pasirinkimas" << endl;
        return 1;
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

    // surikiuojame mokinius pagal pavarde, tada pagal varda
    sort(mokiniai.begin(), mokiniai.end(), mokiniu_palygintojas);

    cout << "------------------------------------------" << endl;
    for (int i = 0; i < mokiniai.size(); i++)
    {
        auto galutinis = skaiciuoti_galutini(mokiniai[i], pasirinkimas);
        cout << left << setw(15) << mokiniai[i].vardas << setw(15) << mokiniai[i].pavarde << left << fixed << setprecision(2) << galutinis << endl;
    }

    return 0;
}
