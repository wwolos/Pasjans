#include <iostream>
#include <string>
#include <vector>
#include "karta.h"
#include "wyswietlacz.h"

std::vector<std::vector<Karta>> kolumny; //Stworzenie listy kart w każdej kolumnie
std::vector<std::vector<Karta>> stosyKoncowe; //Stworzenie listy kart w stosach końcowych | W kolejności Trefl(♣) Karo(♦) kier(♥) pik(♠)
std::vector<Karta> stosRezerwowy; //Stworzenie listy kart w stosie rezerwowym
int indeksRezerwowy = 0; //Indeks aktualnie oglądanej karty w stosie rezerwowym
std::vector<std::string> uzyteKarty; //Stworzenie listy które przechowuje już wylosowane/uzyte karty


int main() {
    Wyswietlacz wyswietlacz;
    srand(time(0)); //Ustawienie seed'u generatora losowych numerów na aktualny czas.
    kolumny.resize(7); //Upewniamy się że mamy 7 kolumn
    stosyKoncowe.resize(4); //Upewniamy się że mamy 4 stosy rezerwowe


    //Pętla dodająca odopwiednia ilosc kart(losowych) do każdej kolumny
    for(int kolumna = 0; kolumna < 7; kolumna++){
        kolumny[kolumna].resize(7); //Ustawiamy ilosc możliwych kart na 7 tak abysmy mogli te karty dodac
        for(int rzad = 0; rzad < kolumna+1; rzad++){ //Dodanie do każdej kolumny odpowiedniej ilosci kart np. kolumna 3 - 3 karty
            kolumny[kolumna][rzad] = Karta(uzyteKarty); //Losowanie karty innej niż użyte już
            uzyteKarty.push_back(kolumny[kolumna][rzad].tekst); //Dodanie karty do już użytych kart
            if(rzad != kolumna){ //Jeżeli karta nie jest pierwsza z brzegu
                kolumny[kolumna][rzad].zakryj(); //Zakrywamy ją
            }
        }
    }

    //Pętla dodająca losowe karty do stosu rezerwowego
    while(uzyteKarty.size() < 52){
        stosRezerwowy.push_back(Karta(uzyteKarty));
        uzyteKarty.push_back(stosRezerwowy[stosRezerwowy.size()-1].tekst);
    }

    wyswietlacz.wyswietlGre(kolumny,stosyKoncowe,stosRezerwowy,indeksRezerwowy);



    
    return 0;
}
