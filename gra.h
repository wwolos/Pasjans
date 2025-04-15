#ifndef GRA_H
#define GRA_H

#include <iostream>
#include <string>
#include <vector>
#include "karta.h"
#include "komenda.h"

class Gra{
    public:
    std::vector<std::vector<Karta>> kolumny; //Stworzenie listy kart w każdej kolumnie
    std::vector<std::vector<Karta>> stosyKoncowe; //Stworzenie listy kart w stosach końcowych | W kolejności Trefl(♣) Karo(♦) kier(♥) pik(♠)
    std::vector<Karta> stosRezerwowy; //Stworzenie listy kart w stosie rezerwowym
    int indeksRezerwowy = 0; //Indeks aktualnie oglądanej karty w stosie rezerwowym
    std::vector<std::string> uzyteKarty; //Stworzenie listy które przechowuje już wylosowane/uzyte karty

    void wyswietlGre(); //Wyświetlenie planszy gry
    void przetworzWejscie(std::string wejscie); //Przetwarza wejście | Odpowiada za sterowanie
    Gra();
};

#endif // GRA_H