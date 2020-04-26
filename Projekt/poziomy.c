#include "biblioteki.h"
void zaladujMapy(struct level *poziom){ // Funkcja ładuje do struktury poziom kolejne bitmapy poziomow
    poziom->bitmapa[0]=al_load_bitmap("grafiki/mapa4.png");
    poziom->bitmapa[1]=al_load_bitmap("grafiki/mapa1.png");
    poziom->bitmapa[2]=al_load_bitmap("grafiki/mapa2.png");
    poziom->bitmapa[3]=al_load_bitmap("grafiki/mapa3.png");
    poziom->bitmapa[4]=al_load_bitmap("grafiki/mapa4.png");
    poziom->bitmapa[5]=al_load_bitmap("grafiki/mapa3.png");
    poziom->bitmapa[6]=al_load_bitmap("grafiki/mapa2.png");
    poziom->bitmapa[7]=al_load_bitmap("grafiki/mapa1.png");
    poziom->bitmapa[8]=al_load_bitmap("grafiki/mapa2.png");
    poziom->bitmapa[9]=al_load_bitmap("grafiki/mapa3.png");
}
