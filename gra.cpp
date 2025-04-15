#include "gra.h"


Gra::Gra(){
    srand(time(0)); //Ustawienie seed'u generatora losowych numerów na aktualny czas.
    kolumny.resize(7); //Upewniamy się że mamy 7 kolumn
    stosyKoncowe.resize(4); //Upewniamy się że mamy 4 stosy rezerwowe

    //Wiadomość startowa
    std::cout << "Witaj w grze: Pasjans\n";
    std::cout << "Aby sterować w tej grze będziesz używać komend\n";
    std::cout << "Każda komenda składa się z miejsca startowego,końcowego oraz dwukropka między nimi\n";
    std::cout << "Komenda może wyglądać np tak: k3x2:k1\n";
    std::cout << "To oznacza przenieść trzy karty(\"x3\") z trzeciej kolumny(\"k3\") do(\":\") pierwszej kolumny(\"k1\")\n";
    std::cout << "Gdy chcesz przeniesc karte na stos końcowy możesz użyć np. k1:sk\n";
    std::cout << "Czyli karta z kolumny pierwszej(\"k1\") na(\":\") odpowiedni stos końcowy(\"sk\")\n";
    std::cout << "Branie kart ze stosu rezerwowego też jest proste możesz do tego użyć np. sr:k3\n";
    std::cout << "Czyli karta ze stosu rezerwowego(\"sr\") na trzecia kolumne\n";
    std::cout << "Aby przeglądać stos rezerwowy możesz użyć sr:sr\n";
    std::cout << "\n Jeśli chcesz już grać nacisnij enter\n";


    std::cin.get();


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

}

void Gra::wyswietlGre(){
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

void Gra::przetworzWejscie(std::string wejscie){
    Komenda komenda(wejscie);
    if(komenda.czyPoprawna){
        std::cout << wejscie;
    }
    else{
        std::cout << "Komenda: " << wejscie << " jest niepoprawna, ponieważ:\n" << komenda.powodNiepoprawnosci;
    }
}