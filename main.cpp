#include <iostream>
#include <string>
#include <vector>
#include "karta.h"
#include "gra.h"

int main() {
    Gra gra;
    for(int i = 0; i < 100; i++){
            std::cout << "\n";
    }
    while(true){
        gra.wyswietlGre();
        std::string wejscie;
        std::cin >> wejscie;
        for(int i = 0; i < 100; i++){
            std::cout << "\n";
        }
        gra.przetworzWejscie(wejscie);
    }
    return 0;
}
