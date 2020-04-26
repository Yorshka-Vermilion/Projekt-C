#include "biblioteki.h"

void zakolejkujStrzalyDrona(struct pointersShipShot *strzaly, struct drone *dron){ // Dodaje do kolejko/listy strzal ze struktury drona
    struct shipShot *nowy = (struct shipShot *) malloc(sizeof(struct shipShot)); // Zwykle alokowanie pamieci i dodanie elementu do listy
    if(nowy){
        nowy->x= statek.x-dron->x-48; // Przypisanie pozycji strzalu drona
        nowy->y= statek.y-dron->y-al_get_bitmap_height(dron->dronBitmap);
        nowy->dmg = dron->dmg;
        nowy->next = NULL;
        nowy->strzalBitmap = dron->strzalBitmap;
        if(strzaly->head==NULL)strzaly->head = strzaly->tail = nowy;
        else{
            strzaly->tail->next=nowy;
            strzaly->tail=nowy;
        }
    }
};

struct cannon *stworzNoweDzialo(int x, int y,ALLEGRO_BITMAP **strzalBitmap){ // Tworzenie nowej struktury dziala, funkcja zwraca wkaznik na nowa strukture
    struct cannon *nowy = (struct cannon *) malloc(sizeof(struct cannon));
    if(nowy){
            nowy->x = x;
            nowy->y = y;
            nowy->dmg = statek.dmg;
            nowy->strzalBitmap = strzalBitmap;
            nowy->poziom = 1;
            return nowy;
        }
}

struct drone *stworzNowegoDrona(int x, int y,ALLEGRO_BITMAP **dronBitmap,ALLEGRO_BITMAP **strzalBitmap){ // Tworzenie nowego drona, funkcja zwraca wskaznik na nowego drona
    struct drone *nowy = (struct drone *) malloc(sizeof(struct drone));
    if(nowy){
            if(x>0)nowy->x = x-al_get_bitmap_width(dronBitmap);
            else nowy->x = x;
            nowy->y = y-al_get_bitmap_height(dronBitmap);
            nowy->dmg = statek.dmg;
            nowy->dronBitmap = dronBitmap;
            nowy->strzalBitmap = strzalBitmap;
            nowy->poziom = 1;
            return nowy;
        }
}


