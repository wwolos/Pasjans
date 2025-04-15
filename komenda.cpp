#include "komenda.h"

Komenda::Komenda(std::string wejscie){
    czyPoprawna = true;
    lewa = wejscie.substr(0,wejscie.find(":"));
    prawa = wejscie.substr(wejscie.find(":")+1);

    if(!(lewa.length() == 2 || lewa.length() == 4 || lewa.length() == 5) || prawa.length() != 2){
        czyPoprawna = false;
        powodNiepoprawnosci = "W poprawnej komendzie lewa strona(przed dwukropkiem) ma 2 lub 4 znaki, a prawa 2.";
        return;
    }
    if(!(lewa[0] == 'k'|| (lewa[0] == 's' && (lewa[1] == 'r' || lewa[1] == 'k')))){
        czyPoprawna = false;
        powodNiepoprawnosci = "W poprawnej komendzie lewa strona(przed dwukropkiem) musi zaczynać się od k,sk, lub sr";
        return;
    }
    if(!(prawa[0] == 'k' ||(prawa[0] == 's' && prawa[1] == 'k'))){
        czyPoprawna = false;
        powodNiepoprawnosci = "W poprawnej komendzie prawa strona(po dwukropku) musi zaczynać się od k lub sk";
        return;
    }
    if(!(lewa[0] == 'k' && isdigit(lewa[1]) && lewa[1] > '0' && lewa[1] <= '7')){
        czyPoprawna = false;
        powodNiepoprawnosci = "Po lewej stronie(przed dwukropkiem) po literze k zawsze musi być numer od 1-7";
        return;
    }
    if(!(prawa[0] == 'k' && isdigit(prawa[1]) && prawa[1] > '0' && prawa[1] <= '7')){
        czyPoprawna = false;
        powodNiepoprawnosci = "Po prawej stronie(po dwukropku) po literze k zawsze musi byc liczba od 1-7";
        return;
    }
    if(lewa.length() == 4 && !(lewa[2] == 'x' && isdigit(lewa[3]))){
        czyPoprawna = false;
        powodNiepoprawnosci = "Jeśli lewa strona(przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 1";
        return;
    }
    if(lewa.length() == 5 && !(lewa[2] == 'x' && isdigit(lewa[3]) && isdigit(lewa[4]))){
        czyPoprawna = false;
        powodNiepoprawnosci = "Jeśli lewa strona(przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 2";
        return;
    }

    if(lewa[0] == 'k'){
        rodzajZrodla = 1;
    }
    if(lewa[0] == 's' && lewa[1] == 'k'){
        rodzajZrodla = 2;
    }
    if(lewa[0] == 's' && lewa[1] == 'r'){
        rodzajZrodla = 3;
    }

    if(prawa[0] == 'k'){
        rodzajMiejscaDoc = 1;
    }
    else{
        rodzajMiejscaDoc = 2;
    }

    indexZrodla = lewa[1]-'0';
    indexMiejscaDoc = prawa[1]-'0';

    if(lewa.length() == 4){
        iloscKart = lewa[3]-'0';
    }
    else if(lewa.length() == 5){
        iloscKart = std::stoi(lewa.substr(3,2));
    }
    else{
        iloscKart = 1;
    }
}