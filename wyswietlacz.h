#ifndef WYSWIETLACZ_H
#define WYSWIETLACZ_H

#include <iostream>
#include <string>
#include <vector>
#include "karta.h"

class Wyswietlacz{
    public:
        void wyswietlGre(std::vector<std::vector<Karta>> kolumny); //Wyświetlenie planszy gry
};

#endif // WYSWIETLACZ_H