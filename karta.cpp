#include "karta.h"

std::string wartosci[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}; //Lista wartosci kart, czyli np 10♦ (Dziesiątka karo) | Wykorzystywane do wyświetlania kart
//                                                                                                                 ^^
std::string kolory[4] = {"♣","♦","♥","♠"}; //Lista kolorów kart, czyli np 10♠ (Dziesiątka pik) | Wykorzystywane do wyświetlania kart
//                                                                          ^

Karta::Karta(int wartosc, int kolor){
    Karta::wartosc = wartosc;
    Karta::kolor = kolor;
    Karta::tekst = wartosci[wartosc] + kolory[kolor]; //Ustawienie poprawnego tekstu wyswietlania
    if(Karta::tekst.size() == 2){//Upewniamy się że nasz tekst ma dlugosc 3 znaki, tak aby wszystko się równo wyświetlało
        Karta::tekst += " ";
    }
}

Karta::Karta(std::vector<std::string> wykorzystane){
    while(true){
        Karta::wartosc = rand() % 13; // Wylosowanie wartosci
        Karta::kolor = rand() % 4; //Wylosowanie koloru
        Karta::tekst = wartosci[wartosc] + kolory[kolor]; //Ustawienie poprawnego tekstu wyswietlania        
        if(Karta::tekst.size() == 4){//Upewniamy się że nasz tekst ma dlugosc 3 znaki, tak aby wszystko się równo wyświetlało | Czemu sprawdzamy czy tekst ma 4 znaki zamiast 2? znak takie jak "♠" są niestety uznawane za dwa znaki.
            Karta::tekst += " ";
        }
        bool wykorzystana = false; //Czy karta jest wykorzystana?
        for(int i = 0; i < wykorzystane.size(); i++){ //Sprawdzamy czy karta jest w wykorzystanych
            if(tekst == wykorzystane[i]){
                wykorzystana = true;
                break; //Jeśli jest, losujemy jeszcze raz
            }
        }
        if(!wykorzystana){
            return; //Jeżeli nie jest wykorzystana nic więcej nie musimy robić
        }
    }
    
    
}

Karta::Karta(){
    Karta::wartosc = NULL;
    Karta::kolor = NULL;
    Karta::tekst = "PustaKarta";
}

void Karta::zakryj(){
    Karta::tekst = "XX";
    if(Karta::tekst.size() == 2){//Upewniamy się że nasz tekst ma dlugosc 3 znaki, tak aby wszystko się równo wyświetlało
        Karta::tekst += " ";
    }
    Karta::czyZakryta = true;
}

void Karta::odkryj(){
    Karta::tekst = wartosci[wartosc] + kolory[kolor]; //Ustawienie poprawnego tekstu wyswietlania
    if(Karta::tekst.size() == 2){//Upewniamy się że nasz tekst ma dlugosc 3 znaki, tak aby wszystko się równo wyświetlało
        Karta::tekst += " ";
    }
    Karta::czyZakryta = false;
}
