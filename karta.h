#ifndef KARTA_H
#define KARTA_H

#include <iostream>
#include <string>
#include <vector>



class Karta{
    public:
        std::string tekst; //Tekst do wyswietlania karty czyli np. "10♠"
        int wartosc,kolor; //Wartosc i kolor karty, przechowywany jako indeks list wartosci, i kolory
        bool czyZakryta; //Mówi nam czy karta jest zakryta czy nie.
        Karta(int wartosc, int kolor);
        Karta(std::vector<std::string> wykorzystane); //Daje możliwość wylosowania karty, które nie jest w liscie już wylosowanych kart.
        Karta(); //Podstawowy konstuktor, tworzacy "pusta" karte
        void zakryj(); //Zakrywa czyli zamienia tekst karty na "XX"
        void odkryj(); //Odkrywa czyli ustawia z powrotem tekst karty na odpowiedni

};

#endif