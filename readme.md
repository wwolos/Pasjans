# Uruchomienie projektu
W poniżej zawartej sekcji opisałem jak uruchomic projekt na:
* Windowsie
* Linuxie(Ubuntu)

## Windows
### Przygotowanie kompilatora
Aby uruchomić projekt najpierw musimy go skompilować. Aby to zrobić użyjemy kompilatora - MSVC  
Aby pobrać i zainstalować go:
* Przejdź na [oficjalna stronę visual studio](https://visualstudio.microsoft.com/en/)
* Kliknij `Download Visual Studio`
* Po pobraniu instalatora uruchom go i przejdź przez proces instalacji.
* Pamiętaj aby przy wybieraniu obciążeń zaznaczyć `Desktop development with C++`

### Kompilacja
Aby skompilować projekt:
* Otwórz `x64 Native Tools Command Prompt for VS` z menu wyszukiwania na dole
* Przejdź do folderu projektu a następnie do folderu `build`, użyj do tego komendy `cd`
* Uruchom komende `cmake .. -G "Visual Studio 17 2022" -A x64` - generuje ona pliki potrzebne do kompilacji
* Następnie uzyj `cmake --build . --config Release` aby skompilować projekt

### Uruchomienie
Skompilowany plik `.exe` powinien znajdować się teraz w folderze `Pasjans/build/Release`
Możesz go uruchomic za pomocą eksploatora plików lub poprzez uruchomienie tych komend:
* `cd Release`
* `Pasjans.exe`

## Linux(Ubuntu)
### Przygotowanie kompilatora
Tak samo jak na windowsie musimy zaistalowac kompilator.  
Aby to zrobić uruchom:
* `sudo apt update`
* `sudo apt install build-essential cmake`
### Kompilacja
Aby skompilować projekt:
* Przejdź do folderu Pasjans/build za pomocą `cd`
* Uruchom `cmake ..` aby wygenrować pliki potrzebne do kompilacji
* Użyj `make -j$(nproc)` aby skompilować projekt
### Uruchomienie
Uruchomienie jest bardzo proste bedąc w folderze `Pasjans/build` wykonaj `Pasjans`

## Zależności
Ten projekt posiada dwie zależności:
* [Rang](https://github.com/agauniyal/rang) - Uzywany do wyswietlania kolorów
* [Catch2](https://github.com/catchorg/Catch2) - Uzywane do testów jednostkowych  
Natomiast nie jest wymagane ich pobierane, rang jest w folderze `include/rang`, razem z projektem.
A Catch2 jest autmatycznie pobierane przez cmake.

---

# Sterowanie
W poniżej zawartej sekcji wytłumaczylem jak kontrolować grę.
### Podstawy sterowania
W tej grze aby wykonać jakikolwiek ruch będziesz używac **komend**.  
Najproszte z nich to:
* **settings** - używane do wyświetlenia ustawień
* **exit** - używane do wyjścia z gry  
### Struktura komendy
Każda komenda musi się składać z:
* **Miejsca startowego** - z którego bierzemy kartę/y
* **Dwukropka** - który oddziela miejsce startowe od koncowego
* **Miejsca docelowego** - na które odkładamy kartę/y     

Wszystkie te elementy musza byc w takiej kolejnosci jak powyżej, i nie mogą być oddzielane spacją/mi
### Możliwe miejsca startowe
Jako miejsce startowe możemy wykorzystac:
* **Kolumnę** - zapisywaną jako `k` oraz numer od 1-7 np. `k5`
* **Stos rezerwowy** - zapisywany jako `sr`
### Możliwe miejsca docelowe
Miejscem docelowym może być:
* **Kolumna** - tak samo jak w miejscu startowym `k` oraz numer od 1-7 np. `k6`
* **Stos końcowy** - oznaczony jest jako `sk` 

### Ilosc kart do przeniesienia
Oczywiście czasami chcemy przenieść więcej niż jedną kartę, aby tego dokonać po miejscu startowym mozemy dodać:
* **Konkretną liczbe kart** - zapisujemy ją poprzez napisanie `x` oraz liczby kart do przeniesienia po miejscu startowym. np. `x5`
* **Wszystkie mozliwe karty** - zapisywane jako `xa` (z ang. all-wszystko), przenosi wszystkie możliwe karty

### Przykłady komend oraz ich działanie
> `k1:k4`  
>  Najbardziej podstawowy rodzaj komendy, czyli przeniesienie jednej kart z **pierwszej kolumny**(`k1`) **na**(`:`) **czwartą kolumnę**(`k4`)  
  
> `k2x3:k7`  
> Bardzo podobna do poprzedniej, jedyne co się zmieniło to numery kolumn oraz ilosc kart do przeniesienia  
> Teraz nasza komenda to przeniesienie **trzech kart**(`x3`) z **drugiej kolumny**(`k2`) **na**(`:`) **siódmą kolumnę**(`k7`)   

> `k3xa:k6`  
> Również podobna do poprzedniej, jedyne co sie zmienilo to ilosc kart i numery kolumn  
> Teraz nasza komenda to przeniesienie **wszystkich możliwych kart**(`xa`) z **trzeciej kolumny**(`k3`) **na**(`:`) **szóstą kolumnę**(`k6`)   

> `sr:k1`  
> Ta komenda przenosi jedną kartę ze **stosu rezerwowego**(`sr`) **na**(`:`) **pierwszą kolumnę**(`k1`)

> `k6:sk`  
> Przenoszenie na stos koncowy to jeden z ważniejszych elementów gry w Pasjansa, bez tego nie da się wygrać :)  
> W tej komendzie przenosimy jedną kartę z **szóstej kolumny**(`k6`) na **stos koncowy**(`sk`)

### Stos koncowy
Być może zauważyłes że tak na prawdę w Pasjansie są cztery stosy końcowe?  
Masz rację! Każdy odpowiada jednemu z czterech rodzaji kart.  
Ale w tej grze aby nie komplikować rozgrywki gra sama wykrywa na który stos przeniesc kartę.

### Stos rezerwowy
Podobnie jak ze stosem końcowym mogłes zauważyc że w Pasjansie da się przeglądać stos rezerwowy.  
Znowu masz rację! Aby to wykonac użyj komendy `sr:sr` lub jeszcze krócej `sr`.

> Porada: wszystkie te informacje są zawarte w krótszej formie przy rozpoczęciu gry
