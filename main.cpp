#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Mokinys {
    string vardas;
    string pavarde;
    int namu_darbu_kiekis{0};
    vector<int> namu_darbu_rezultatai;
    int egzamino_rezultatas{0};
};

int main()
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

//   for ( <paruosiamieji veiksmai atliekami pries cikla> ; <salyga - ciklas vykdomas tol, kas salyga tenkinama> ; <kiekvieno ciklo pabaigoje vykdomi veiksmai>)



    for (int i=0; i < m.namu_darbu_kiekis; i++)
    {
       int pazymys;
       cout << "Iveskite pazymi nr " << i+1 << endl;
       cin >> pazymys;
       m.namu_darbu_rezultatai.push_back(pazymys);
    }

    double vidurkis=0;
    for (int j = 0; j < m.namu_darbu_rezultatai.size(); j++)
    {
        cout << m.namu_darbu_rezultatai[j];
        vidurkis += m.namu_darbu_rezultatai[j];
        if (j < (m.namu_darbu_rezultatai.size()-1))
        {
            cout << ", ";
        }
        else
        {
            cout << endl;
            cout << endl;
        }
    }
    cout << "vidurkis:" << vidurkis / m.namu_darbu_rezultatai.size();

    return 0;
}
