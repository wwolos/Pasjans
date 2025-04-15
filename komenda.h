#ifndef KOMENDA_H
#define KOMENDA_H

#include <iostream>
#include <string>
#include <vector>
#include "gra.h"
#include "karta.h"

class Komenda{
    public:
        Komenda(std::string wejscie);
        bool czyPoprawna;
        std::string powodNiepoprawnosci;
        int rodzajZrodla; // 1 kolumna, 2 stos koncowy, 3 stos rezerwowy
        int rodzajMiejscaDoc;
        int indexZrodla; //Tylko przy 'k' czyli kolumnach
        int indexMiejscaDoc; //Tylko przy 'k' czyli kolumnach
        int iloscKart;

    private:
        std::string lewa;
        std::string prawa;

};

#endif