

![greicio palyginimas](paveiksliukai/palyginimas.png)

Procesorius(CPU): AMD Ryzen 5 6600H, 12 CPUs


Atmintis(RAM): 7.4 GB RAM


Kietas Diskas(HDD): HDD




# Algoritmo greičio palyginimas naudojant `std::vector` ir `std::list`

## Greičio eksperimentai naudojant `vector`

| Eilučių kiekis  | Failo nuskaitymas (ms) | Rikiavimas (ms) | Galutinių pažymių skaičiavimas (ms) | Skirstymas į du sąrašus (ms) | Silpnųjų mokinių išvedimas (ms) | Protingųjų mokinių išvedimas (ms) | Visa trukmė (ms) |
|-----------------|------------------------|-----------------|-------------------------------------|------------------------------|---------------------------------|-----------------------------------|------------------|
| 1000            | 0.935059               | 0.196684        | 0.034836                            | 0.113787                     | 0.910391                        | 1.34973                            | 3.5407           |
| 10000           | 7.3318                 | 7.20439         | 0.396134                            | 1.25571                      | 14.4801                         | 16.8448                            | 47.5134          |
| 100000          | 93.9962                | 41.5882         | 4.72499                             | 14.8127                      | 109.099                         | 145.986                            | 410.208          |
| 1000000         | 708.58                 | 527.017         | 33.2891                             | 116.225                      | 979.374                         | 1274.06                            | 3638.54          |
| 10000000        | 7500.52                | 6838.17         | 340.182                             | 1388.66                      | 9806.27                         | 13008.2                            | 38882            |

## Greičio eksperimentai naudojant `list`

| Eilučių kiekis  | Failo nuskaitymas (ms) | Rikiavimas (ms) | Galutinių pažymių skaičiavimas (ms) | Skirstymas į du sąrašus (ms) | Silpnųjų mokinių išvedimas (ms) | Protingųjų mokinių išvedimas (ms) | Visa trukmė (ms) |
|-----------------|------------------------|-----------------|-------------------------------------|------------------------------|---------------------------------|-----------------------------------|------------------|
| 1000            | 0.652371               | 0.043122        | 0.032883                            | 0.061497                     | 26.0982                         | 38.6205                            | 65.5087          |
| 10000           | 6.31865                | 0.501705        | 0.319447                            | 0.607966                     | 9.52224                         | 12.7733                            | 30.0434          |
| 100000          | 64.1822                | 8.99959         | 13.6393                             | 15.0855                      | 96.5232                         | 129.883                            | 328.314          |
| 1000000         | 710.011                | 106.716         | 33.9455                             | 114.931                      | 981.715                         | 1328.22                            | 3275.54          |
| 10000000        | 7363.2                 | 1481.16         | 573.688                             | 1411.18                      | 9568.22                         | 13653.7                            | 34051.2          |


## Klasės Žmogus ir Studentas

Darbe naudojama abstrakti klasė "Žmogus" kuri atsakinga už vardo ir pavardės saugojimą.
Ši klasė yra abstrakti, tai pasiekiama sukuriant gryną virtualųjį metodą spausdink.
Studentas klasė paveldi iš žmogaus ir įgyvendina su studento gyvenimu susijusius metodus - galutinio balo skaičiavimą. Ji, taip pat, įgyvendina spausdink metodą tam, kad klasė nebutų abstrakti ir galėtų būti sukuriama.