

![greicio palyginimas](paveiksliukai/palyginimas.png)

Procesorius(CPU): AMD Ryzen 5 6600H, 12 CPUs


Atmintis(RAM): 7.4 GB RAM


Kietas Diskas(HDD): HDD



# Algoritmo greičio palyginimas naudojant `std::vector` ir `std::list`


## Naudojant `vector`

| Eilučių skaičius | Failo nuskaitymas (ms) | Rikiavimas (ms) | Galutinių pažymių skaičiavimas (ms) | Skirstymas į dvi grupes (ms) | Silpnųjų mokinių išvedimas (ms) | Protingų mokinių išvedimas (ms) | Visa trukmė (ms) |
|------------------|-------------------------|-----------------|-------------------------------------|-----------------------------|--------------------------------|--------------------------------|-------------------|
| 1000             | 2.38552                 | 1.66622         | 0.126857                            | 0.41286                     | 1.62094                        | 2.32377                        | 8.53756          |
| 10000            | 17.4443                 | 23.7773         | 1.12072                             | 4.25869                     | 14.6326                        | 22.6747                        | 83.9115          |
| 100000           | 162.39                  | 237.227         | 10.0711                             | 30.1741                     | 115.13                         | 161.405                        | 716.401          |
| 1000000          | 1444.15                 | 2997.06         | 94.0012                             | 353.791                     | 1215.5                         | 1627.72                        | 7732.24          |
| 10000000         | 15537                   | 35993           | 1030.01                             | 3595.79                     | 12233.2                        | 16928.1                        | 85317.1          |

## Naudojant `list`

| Eilučių skaičius | Failo nuskaitymas (ms) | Rikiavimas (ms) | Galutinių pažymių skaičiavimas (ms) | Skirstymas į dvi grupes (ms) | Silpnųjų mokinių išvedimas (ms) | Protingų mokinių išvedimas (ms) | Visa trukmė (ms) |
|------------------|-------------------------|-----------------|-------------------------------------|-----------------------------|--------------------------------|--------------------------------|-------------------|
| 1000             | 137.769                 | 0.3465          | 0.0937535                           | 0.25492                     | 13.5619                        | 55.3361                         | 207.364          |
| 10000            | 13.7834                 | 4.19733         | 0.960657                            | 2.98541                     | 12.4856                        | 16.6529                         | 51.0672          |
| 100000           | 153.955                 | 47.8844         | 9.5618                              | 31.2733                     | 125.723                        | 170.715                         | 539.118          |
| 1000000          | 1488.69                 | 532.031         | 95.3246                             | 296.557                     | 1252.57                        | 1734.94                         | 5400.13          |
| 10000000         | 14545.5                 | 6051.33         | 962.225                             | 3106.41                     | 12380.8                        | 16985.8                         | 54032.1          |
