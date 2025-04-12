#include "wyswietlacz.h"
#include "algorithm"

void Wyswietlacz::wyswietlGre(std::vector<std::vector<Karta>> kolumny, std::vector<std::vector<Karta>> stosyKoncowe, std::vector<Karta> stosRezerwowy, int indeksRezerwowy){
    //Pętla usuwająca wszystkie puste karty
    for(int i = 0; i < kolumny.size(); i++){ //Przechodzimy przez karzdą kolumne
        while(kolumny[i][kolumny[i].size()-1].tekst == "PustaKarta"){ //Jeżeli ostatnim elementem listy jest pusta karta, usuwamy ją
            kolumny[i].pop_back();
        }
    }

    //Pętla sprawdzająca jak długa jest najdłuższa kolumna
    int dlugoscNajdluzszejKolumny = 0; //Licznik najdłuższej kolumny
    for(const auto& kolumna : kolumny){ //Przechodzimy przez karzdą kolumne
        if(kolumna.size() > dlugoscNajdluzszejKolumny){ //Jeżeli aktualna kolumna jest najdłuższa do tej pory, aktualizujemy licznik
            dlugoscNajdluzszejKolumny = kolumna.size();
        }
    }


    std::cout << "\n=============================\n|";
    for(int i = 0; i < 4; i++){
        if(stosyKoncowe[i].size() >= 1){
            std::cout << stosyKoncowe[i][stosyKoncowe[i].size()-1].tekst << "|";
        }
        else{
            switch(i){
                case(0):
                    std::cout << " ♣ |";
                    break;
                case(1):
                    std::cout << " ♦ |";
                    break;
                case(2):
                    std::cout << " ♥ |";
                    break;
                case(3):
                    std::cout << " ♠ |";
                    break;

            }
        }
    }

    std::cout << "   |XX |" << stosRezerwowy[indeksRezerwowy].tekst << "|";

    std::cout << "\n=============================";

    //Pętla wyświetlająca wszystkie karty
    for(int i = 0; i < dlugoscNajdluzszejKolumny; i++){ //Przechodzimy przez karty w kolumnach(góra-dół w konsoli)
        std::cout << "\n|";
        for(const auto& kolumna : kolumny){ //Przechodzimy przez kolumny(lewo-prawo w konsoli)
            if(i < kolumna.size()){ //Jeżeli istnieje element z aktualnym indeksem, to wyświetlamy go
                std::cout << kolumna[i].tekst << "|"; 
            }
            else{ //Jeżeli nie wyświetlamy puste miejsce
                std::cout << "   |";
            }
        }
    }

    std::cout << "\n=============================\n";
}