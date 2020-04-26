#include "biblioteki.h"

void wyczyscStatek(struct ship *statek){ // Funkcja czysci pamiec statku
    if(statek->srodkoweDzialo!=NULL){ // Jesli statek posiada dany przedmio
    free(statek->srodkoweDzialo); // Uwalniamy pamiec
    statek->srodkoweDzialo=NULL; // Przepinamy wkaznik na NULL
    }
    if(statek->leweDzialo!=NULL){
    free(statek->leweDzialo);
    statek->leweDzialo=NULL;
    }
    if(statek->praweDzialo!=NULL){
    free(statek->praweDzialo);
    statek->praweDzialo=NULL;
    }
    if(statek->lewyDron!=NULL){
    free(statek->lewyDron);
    statek->lewyDron=NULL;
    }
    if(statek->prawyDron!=NULL){
    free(statek->prawyDron);
    statek->prawyDron=NULL;
    }
}

void wyczyscPamiec(struct pointersAlien *kosmici, struct pointersAlienShot *strzalyKosmitow, struct pointersShipShot *strzaly){ // Funkcja czysci pamiec zajetą przez kosmitow, ich strzaly i strzaly gracza, uzywana przy przejsciach miedzy poziomami i galaktykami
    while(kosmici->head){ // Dopóki wskaznik na kosmici->head nie jest nullem
        struct alien *tmp = kosmici->head->next; // Robimy tymczasowy wskaznik tmp wskazujacy na nastepny element z listy
        free(kosmici->head); // Uwalniamy pamiec z danego kosmity
        kosmici->head = tmp; // Przepinamy wskaznik ze struktury wskaznikow 'kosmici' na strukture wskazywana przez tymczasowy wskaznik tmp
        if(tmp==NULL)kosmici->tail = NULL; // Jesli tmp to null to wskaznik tail ze struktury wskaznikow ustawiamy na NULL
    }
    while(strzalyKosmitow->head){
        struct alienShot *tmp2 = strzalyKosmitow->head->next;
        free(strzalyKosmitow->head);
        strzalyKosmitow->head = tmp2;
        if(tmp2==NULL) strzalyKosmitow->tail = NULL;
    }
    while(strzaly->head){
        struct shipShot *tmp3 = strzaly->head->next;
        free(strzaly->head);
        strzaly->head = tmp3;
        if(tmp3==NULL)strzaly->tail = NULL;
    }
}
