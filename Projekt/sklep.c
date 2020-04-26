#include "biblioteki.h"
struct item *stworzPrzedmiot(char *nazwa, int x, int y, int koszt, bool dostepny, bool spec, ALLEGRO_BITMAP *bitmapa){ // Funkcja tworzy nowy przedmiot w sklepie, o podanej nazwie, pozycji, koszcie, dostepnosci
    struct item *nowy = (struct item *) malloc(sizeof(struct item)); // przyjmuje takze argumeent 'spec' ktory jest odpowiedzialny za oznaczenie specjalnego (nie posiadajacego dziala) przedmiotu takiego jak naped.
    if(nowy){
        nowy->nazwa = nazwa;
        nowy->x = x;
        nowy->y = y;
        nowy->poziom = 0;
        nowy->koszt = koszt;
        nowy->kosztPocz = koszt;
        nowy->dostepny = dostepny;
        nowy->posiadany = false;
        nowy->kursor = false;
        nowy->dmg = 0;
        nowy->spec = spec;
        nowy->bitmapa = bitmapa;
        return nowy;
    }
};

void sprawdzSklep(int x, int y, struct shop *sklep){ // Funkcja sprawdza czy kursor myszy na pozycji przekazanej w argumencie x i y, NIE znajduje sie nad jakims przedmiotem w sklepie, jesli jednak sie znajduje to zwraca ustawia na tym przedmiocie wartosc bool kursor na true
    for(int i=0;i<6;i++){
        if((x > sklep->przedmiot[i]->x + sklep->szerokoscPola-1) ||
            (y > sklep->przedmiot[i]->y + sklep->wysokoscPola-1) ||
            (sklep->przedmiot[i]->x > x) ||
            (sklep->przedmiot[i]->y > y)){
                sklep->przedmiot[i]->kursor = false;
            }
        else sklep->przedmiot[i]->kursor = true;
    }
}
int zwrocKoszt(struct item *przedmiot){ // Funkcja zwraca obliczony koszt przedmiotu
    return przedmiot->kosztPocz*przedmiot->poziom;
}
void ustawSklep(struct shop *sklep, struct ship *statek){ //Funkcja ustawia sklep pobierajac dane ze statku i przypisuje je do kolejnych przedmiotow sklepu o indexach od 0 do 5
    if(statek->srodkoweDzialo!=NULL){ // Jesli przedmiot znajduje sie juz na statku
        sklep->przedmiot[0]->poziom=statek->srodkoweDzialo->poziom; // Skopiowanie poziomu danego przedmiotu ze statku do sklepu
        sklep->przedmiot[0]->dmg=statek->srodkoweDzialo->dmg; // Skopiowanie obrazen danego przedmiotu ze statku do sklepu
        sklep->przedmiot[0]->posiadany=true; // Ustawienie go jako posiadanego w sklepie
        sklep->przedmiot[0]->koszt=zwrocKoszt(sklep->przedmiot[0]); // Koszt zostaje obliczony funkcja zwrocKoszt
    }
    if(statek->leweDzialo!=NULL){
        sklep->przedmiot[1]->poziom=statek->leweDzialo->poziom;
        sklep->przedmiot[1]->dmg=statek->leweDzialo->dmg;
        sklep->przedmiot[1]->posiadany=true;
        sklep->przedmiot[1]->koszt=zwrocKoszt(sklep->przedmiot[1]);
    }
    if(statek->praweDzialo!=NULL){
        sklep->przedmiot[2]->poziom=statek->praweDzialo->poziom;
        sklep->przedmiot[2]->dmg=statek->praweDzialo->dmg;
        sklep->przedmiot[2]->posiadany=true;
        sklep->przedmiot[2]->koszt=zwrocKoszt(sklep->przedmiot[2]);
    }
    if(statek->movement!=NULL){
        sklep->przedmiot[3]->poziom=statek->movement/10;
        sklep->przedmiot[3]->dmg=statek->movement;
        sklep->przedmiot[3]->koszt=zwrocKoszt(sklep->przedmiot[3]);
    }
    if(statek->lewyDron!=NULL){
        sklep->przedmiot[4]->poziom=statek->lewyDron->poziom;
        sklep->przedmiot[4]->dmg=statek->lewyDron->dmg;
        sklep->przedmiot[4]->poziom = statek->lewyDron->poziom;
        sklep->przedmiot[4]->posiadany=true;
        sklep->przedmiot[4]->koszt=zwrocKoszt(sklep->przedmiot[4]);
    }
    if(statek->prawyDron!=NULL){
        sklep->przedmiot[5]->poziom=statek->prawyDron->poziom;
        sklep->przedmiot[5]->dmg=statek->prawyDron->dmg;
        sklep->przedmiot[5]->poziom = statek->prawyDron->poziom;
        sklep->przedmiot[5]->posiadany=true;
        sklep->przedmiot[5]->koszt=zwrocKoszt(sklep->przedmiot[5]);
    }

}

void rysujInfo(struct item *przedmiot,ALLEGRO_FONT *font){ // Funkcja rysuje informacje o przedmiocie po najechaniu na niego kursorem
    if(przedmiot->spec==true){
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.3,ALLEGRO_ALIGN_LEFT,"%s",przedmiot->nazwa);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.33,ALLEGRO_ALIGN_LEFT,"Poziom: %d",przedmiot->poziom);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.36,ALLEGRO_ALIGN_LEFT,"Koszt ulepszenia: %d",przedmiot->koszt);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.39,ALLEGRO_ALIGN_LEFT,"Szybkosc: %d",przedmiot->dmg);
    }
    else{
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.3,ALLEGRO_ALIGN_LEFT,"%s",przedmiot->nazwa);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.33,ALLEGRO_ALIGN_LEFT,"Poziom: %d",przedmiot->poziom);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.36,ALLEGRO_ALIGN_LEFT,"Koszt ulepszenia: %d",przedmiot->koszt);
        al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.39,ALLEGRO_ALIGN_LEFT,"DMG %d",przedmiot->dmg);
    }
}


int kupPrzedmiot(int x, int y,struct shop *sklep, struct ship *statek, ALLEGRO_BITMAP *strzalBitmap, ALLEGRO_BITMAP *dronBitmap){ // Funkcja kupuje przedmiot nad ktorym aktualnie znajduje sie kursor i ktory ma ustawiana wartosc bool kursor na true
    int szukany = -1;
    for(int i=0;i<6;i++){
        if(sklep->przedmiot[i]->kursor == true) szukany=i;; // Jesli nad przedmiotem jest aktualnie kursor to zmienna szukany przyjmuje wartosc o numerze indexu danego przedmiotu
    }
    if(szukany>=0){
        switch(szukany){ // Szukamy przedmiotu o podanym indeksie
            case 0:
                if(statek->kredyty >= sklep->przedmiot[1]->koszt){ // Sprawdzenie czy gracza stac na zakup
                    if(statek->srodkoweDzialo==NULL){ // Sprawdzenie czy przedmiotu aktualnie nie ma, jesli tak to kupujemy przedmiot
                            statek->srodkoweDzialo = stworzNoweDzialo(statek->szerokosc/2,0,strzalBitmap);
                            statek->kredyty -= sklep->przedmiot[1]->koszt;
                    }
                    else{ // Jesli jest to kupujemy tylko ulepszenie
                        statek->kredyty -= sklep->przedmiot[1]->koszt; // Usuniecie wymaganej ilosci kredytow
                        statek->srodkoweDzialo->dmg += 50; // Zwiekszenie dmg
                        statek->srodkoweDzialo->poziom += 1; // Zwiekszenie poziomu
                        if(statek->srodkoweDzialo->poziom==5)statek->srodkoweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal3.png"); // Jesli ulepszymy wystarczajaco przdmiot niespecjalny to zmieni on grafike strzalu
                        if(statek->srodkoweDzialo->poziom==10)statek->srodkoweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal4.png");
                    }
                }
                else return 1; // Jesli gracza nie stac na zakup, funkcja zwraca wartosc 1 co w glownym kodzie powoduje wyswietlenie informacji o niewystarczajacej ilosci srodkow na koncie
            break;
            case 1:
                if(statek->kredyty >= sklep->przedmiot[1]->koszt){
                    if(statek->leweDzialo==NULL){
                            statek->leweDzialo = stworzNoweDzialo(statek->szerokosc/4,0,strzalBitmap);
                            statek->kredyty -= sklep->przedmiot[1]->koszt;
                    }
                    else{
                        statek->kredyty -= sklep->przedmiot[1]->koszt;;
                        statek->leweDzialo->dmg += 50;
                        statek->leweDzialo->poziom += 1;
                        if(statek->leweDzialo->poziom==5)statek->leweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal3.png");
                        if(statek->leweDzialo->poziom==10)statek->leweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal4.png");
                    }
                }
                else return 1;
            break;
            case 2:
                if(statek->kredyty >= sklep->przedmiot[2]->koszt){
                    if(statek->praweDzialo==NULL){
                            statek->praweDzialo = stworzNoweDzialo((-statek->szerokosc/4+3),0,strzalBitmap);
                            statek->kredyty -= sklep->przedmiot[2]->koszt;
                    }
                    else{
                        statek->kredyty -= sklep->przedmiot[2]->koszt;;
                        statek->praweDzialo->dmg += 50;
                        statek->praweDzialo->poziom += 1;
                        if(statek->praweDzialo->poziom==5)statek->praweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal3.png");
                        if(statek->praweDzialo->poziom==10)statek->praweDzialo->strzalBitmap = al_load_bitmap("grafiki/strzal4.png");
                    }
                }
                else return 1;
            break;
            case 3:
                if(statek->kredyty >= sklep->przedmiot[3]->koszt){
                        statek->kredyty -= sklep->przedmiot[3]->koszt;;
                        statek->movement += 10;
                }
                else return 1;
            break;
            case 4:
                if(statek->kredyty >= sklep->przedmiot[4]->koszt){
                    if(statek->lewyDron==NULL){
                            statek->lewyDron = statek->lewyDron = stworzNowegoDrona(statek->szerokosc/2,0,dronBitmap,strzalBitmap);
                            statek->kredyty -= sklep->przedmiot[4]->koszt;
                    }
                    else{
                        statek->kredyty -= sklep->przedmiot[4]->koszt;;
                        statek->lewyDron->dmg += 25;
                        statek->lewyDron->poziom += 1;
                        if(statek->lewyDron->poziom==5)statek->lewyDron->strzalBitmap = al_load_bitmap("grafiki/strzal3.png");
                        if(statek->lewyDron->poziom==10)statek->lewyDron->strzalBitmap = al_load_bitmap("grafiki/strzal4.png");
                    }
                }
                else return 1;
            break;
            case 5:
                if(statek->kredyty >= sklep->przedmiot[4]->koszt){
                    if(statek->prawyDron==NULL){
                            statek->prawyDron = statek->prawyDron = stworzNowegoDrona(-statek->szerokosc,0,dronBitmap,strzalBitmap);
                            statek->kredyty -= sklep->przedmiot[4]->koszt;
                    }
                    else{
                        statek->kredyty -= sklep->przedmiot[4]->koszt;;
                        statek->prawyDron->dmg += 25;
                        statek->prawyDron->poziom += 1;
                        if(statek->prawyDron->poziom==5)statek->prawyDron->strzalBitmap = al_load_bitmap("grafiki/strzal3.png");
                        if(statek->prawyDron->poziom==10)statek->prawyDron->strzalBitmap = al_load_bitmap("grafiki/strzal4.png");
                    }
                }
                else return 1;
            break;

        }
    }

}
