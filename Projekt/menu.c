#include "biblioteki.h"
struct options *ustawOpcje(char *tresc, int x, int y){ // Funkcja zwraca wskaznik na nowa strukture opcji, potrzebna do tworzenia opcji w menu
    struct options *nowy = (struct options *) malloc(sizeof(struct options));
    if(nowy){
        nowy->tresc = tresc;
        nowy->x = x;
        nowy->y = y;
        return nowy;
    }
};

void wyborOpcji(int opcja,int *exit){ // Funkcja po wcisnieciu klawisza ENTER sprawdza jaka aktualnie opcja w menu zostala wybrana, a nastpenie ustawia odpowiednie wartosci
    switch(opcja){
        case 0:
            poziom.koniecPoziomu=false;
            poziom.koniecGry=false;
            poziom.set=false;
            galaktyka.set=false;
            poziom.start=true;
        break;
        case 1:
            wyniki.set = true;
        break;
        case 2:
            *exit=0;
        break;
    }
};
