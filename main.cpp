#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <iterator>
#include <chrono>

#include "mokinys.h"
#include "statistika.h"

using namespace std;

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

double skaiciuoti_galutini(Mokinys &m, const string &pasirinkimas)
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

template <class K>
K duomenu_nuskaitymas_is_failo(string failo_vardas)
{
    K mokiniai;

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

// sukursiu funkcija, kuri sugeneruos faila su atsitiktiniais duomenimis
void failu_generavimas(int eiluciu_skaicius)
{
    ofstream failas("mokiniai.txt");
    if (!failas)
    {
        cerr << "Nepavyko sukurti failo mokiniai.txt" << endl;
        return;
    }

    // irasom pirma eilute
    failas << "Vardas Pavarde ";
    for (int i = 1; i <= 15; i++)
    {
        failas << "ND" << i << " ";
    }
    failas << "Egz." << endl;

    for (int i = 0; i < eiluciu_skaicius; i++)
    {
        failas << "vardas" << i << " pavarde" << i << " ";
        for (int j = 0; j < 15; j++)
        {
            failas << rand() % 10 + 1 << " ";
        }
        failas << rand() % 10 + 1 << endl;
    }
}

template <class K>
void failu_irasymas(K &mokiniai, string failo_vardas)
{
    ofstream failas(failo_vardas);
    if (!failas)
    {
        cerr << "Nepavyko sukurti failo " << failo_vardas << "." << endl;
        return;
    }

    // irasom pirma eilute
    failas << "Vardas Pavarde ";

    auto pazymiu_kiekis = mokiniai.front().namu_darbu_rezultatai.size();

    for (int i = 1; i <= pazymiu_kiekis; i++)
    {
        failas << "ND" << i << " ";
    }
    failas << "Egz." << endl;

    for (auto mokinys : mokiniai)
    {
        failas << mokinys.vardas << " " << mokinys.pavarde << " ";
        for (auto pazymys : mokinys.namu_darbu_rezultatai)
        {
            failas << pazymys << " ";
        }
        failas << mokinys.egzamino_rezultatas << endl;
    }
}

// naudojame nuoroda, kad nedarytume kopijos
template <class K>
void rikiuok(K &mokiniai);

template <>
void rikiuok<vector<Mokinys>>(vector<Mokinys> &mokiniai)
{
    sort(mokiniai.begin(), mokiniai.end(), mokiniu_palygintojas);
}

template <>
void rikiuok<list<Mokinys>>(list<Mokinys> &mokiniai)
{
    mokiniai.sort(mokiniu_palygintojas);
}

struct Laikai
{
    chrono::duration<double, milli> nuskaitymo_trukmes{0};
    chrono::duration<double, milli> rikiavimo_trukmes{0};
    chrono::duration<double, milli> galutinio_skaiciavimo_trukmes{0};
    chrono::duration<double, milli> atskyrimas_trukmes{0};
    chrono::duration<double, milli> silpnu_irasymas_trukmes{0};
    chrono::duration<double, milli> protingu_irasymas_trukmes{0};
    chrono::duration<double, milli> bendras_trukmes{0};
};

template <class K>
Laikai eksperimentas(string eksperimento_failas)
{
    K mokiniai;

    auto pradzia_nuskaitymas = chrono::high_resolution_clock::now();
    auto pradzia_bendras = pradzia_nuskaitymas;
    mokiniai = duomenu_nuskaitymas_is_failo<K>(eksperimento_failas);
    auto pabaiga_nuskaitymas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> nuskaitymo_trukme = pabaiga_nuskaitymas - pradzia_nuskaitymas;

    auto pradzia_rikiavimas = chrono::high_resolution_clock::now();
    rikiuok(mokiniai);
    auto pabaiga_rikiavimas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> rikiavimo_trukme = pabaiga_rikiavimas - pradzia_rikiavimas;

    // kiekvieno mokinio galutinis pazymys bus skaiciuojamas pagal vidurki

    auto pradzia_galutinio_skaiciavimas = chrono::high_resolution_clock::now();
    // for (int i = 0; i < mokiniai.size(); i++)
    // {
    //     mokiniai[i].galutinis = skaiciuoti_galutini(mokiniai[i], "vid");
    // }

    for (auto &mokinys : mokiniai)
    {
        mokinys.galutinis = skaiciuoti_galutini(mokinys, "vid");
    }

    auto pabaiga_galutinio_skaiciavimas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> galutinio_skaiciavimo_trukme = pabaiga_galutinio_skaiciavimas - pradzia_galutinio_skaiciavimas;

    K protingi;
    K silpni_moksluose;

    auto pradzia_atskyrimas = chrono::high_resolution_clock::now();
    for (auto mokinys : mokiniai)
    {
        if (mokinys.galutinis >= 5)
        {
            protingi.push_back(mokinys);
        }
        else
        {
            silpni_moksluose.push_back(mokinys);
        }
    }
    auto pabaiga_atskyrimas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli>
        atskyrimas_trukme = pabaiga_atskyrimas - pradzia_atskyrimas;

    auto pradzia_protingu_irasymas = chrono::high_resolution_clock::now();
    failu_irasymas(protingi, "protingi.txt");
    auto pabaiga_protingu_irasymas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> protingu_irasymas_trukme = pabaiga_protingu_irasymas - pradzia_protingu_irasymas;

    auto pradzia_silpnu_irasymas = chrono::high_resolution_clock::now();
    failu_irasymas(silpni_moksluose, "silpni_moksluose.txt");
    auto pabaiga_silpnu_irasymas = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> silpnu_irasymas_trukme = pabaiga_silpnu_irasymas - pradzia_silpnu_irasymas;

    auto pabaiga_bendras = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> bendras_trukme = pabaiga_bendras - pradzia_bendras;

    Laikai laikai;
    laikai.nuskaitymo_trukmes = nuskaitymo_trukme;
    laikai.rikiavimo_trukmes = rikiavimo_trukme;
    laikai.galutinio_skaiciavimo_trukmes = galutinio_skaiciavimo_trukme;
    laikai.atskyrimas_trukmes = atskyrimas_trukme;
    laikai.silpnu_irasymas_trukmes = silpnu_irasymas_trukme;
    laikai.protingu_irasymas_trukmes = protingu_irasymas_trukme;
    laikai.bendras_trukmes = bendras_trukme;
    return laikai;

    // cout << "---------[ Programos greicio analize naudojant faila:  " << eksperimento_failas << "]---------" << endl
    //      << endl;
    // cout << "failo nuskaitymas uztruko: " << nuskaitymo_trukme.count() << " ms" << endl;
    // cout << "rikiavimas uztruko: " << rikiavimo_trukme.count() << " ms" << endl;
    // cout << "galutiniu pazymiu skaiciavimas uztruko: " << galutinio_skaiciavimo_trukme.count() << " ms" << endl;
    // cout << "skirstymas i du sarasus uztruko: " << atskyrimas_trukme.count() << " ms" << endl;
    // cout << "silpnuju mokiniu isvedimas i faila uztruko: " << silpnu_irasymas_trukme.count() << " ms" << endl;
    // cout << "protingu mokiniu isvedimas i faila uztruko: " << protingu_irasymas_trukme.count() << " ms" << endl;
    // cout << "visa trukme: " << bendras_trukme.count() << " ms" << endl;

    // cout << endl
    //      << endl;
}

void spausdink_laikus(Laikai laikai, int eksperimento_kartojimai)
{
    cout << "failo nuskaitymas uztruko: " << laikai.nuskaitymo_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "rikiavimas uztruko: " << laikai.rikiavimo_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "galutiniu pazymiu skaiciavimas uztruko: " << laikai.galutinio_skaiciavimo_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "skirstymas i du sarasus uztruko: " << laikai.atskyrimas_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "silpnuju mokiniu isvedimas i faila uztruko: " << laikai.silpnu_irasymas_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "protingu mokiniu isvedimas i faila uztruko: " << laikai.protingu_irasymas_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
    cout << "visa trukme: " << laikai.bendras_trukmes.count() / eksperimento_kartojimai << " ms" << endl;
}

void sudek_laikus(Laikai &acc, Laikai l)
{
    acc.nuskaitymo_trukmes += l.nuskaitymo_trukmes;
    acc.rikiavimo_trukmes += l.rikiavimo_trukmes;
    acc.galutinio_skaiciavimo_trukmes += l.galutinio_skaiciavimo_trukmes;
    acc.atskyrimas_trukmes += l.atskyrimas_trukmes;
    acc.silpnu_irasymas_trukmes += l.silpnu_irasymas_trukmes;
    acc.protingu_irasymas_trukmes += l.protingu_irasymas_trukmes;
    acc.bendras_trukmes += l.bendras_trukmes;
}

int main()
{

    vector<string> eksperimentai{"sugeneruoti_duomenys1000.txt", "sugeneruoti_duomenys10000.txt", "sugeneruoti_duomenys100000.txt"};
    const int eksperimento_kartojimai = 2;
    // vector<int> eksperimentai{1000, 10000, 100000};
    // vector<int> eksperimentai{1000, 10000, 100000, 1000000, 10000000};
    // negeneruosiu 1000000 ir 10000000 eiluciu failu, nes programa veiks labai letai uzluzti

    cout << "Greicio eksperimentai naudojant vector" << endl;
    for (string eksperimento_failas : eksperimentai)
    {
        Laikai laikai;
        for (int i = 0; i < eksperimento_kartojimai; i++)
        {
            auto l = eksperimentas<vector<Mokinys>>(eksperimento_failas);
            sudek_laikus(laikai, l);
        }

        cout << "---------[ Programos greicio analize naudojant faila:  " << eksperimento_failas << " ir atliekant eksperimenta " << eksperimento_kartojimai << " kartus ]---------" << endl
             << endl;
        spausdink_laikus(laikai, eksperimento_kartojimai);
    }

    cout << "Greicio eksperimentai naudojant list" << endl;
    for (string eksperimento_failas : eksperimentai)
    {
        Laikai laikai;
        for (int i = 0; i < eksperimento_kartojimai; i++)
        {
            auto l = eksperimentas<list<Mokinys>>(eksperimento_failas);
            sudek_laikus(laikai, l);
        }
        cout << "---------[ Programos greicio analize naudojant faila:  " << eksperimento_failas << " ir atliekant eksperimenta " << eksperimento_kartojimai << " kartus ]---------" << endl
             << endl;
        spausdink_laikus(laikai, eksperimento_kartojimai);
    }
}
