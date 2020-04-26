#include "biblioteki.h"


void zakolejkujStrzaly(struct pointersShipShot *strzaly, struct cannon *dzialo, int x, int y){ // Dodajemy nowy strzal do listy srzalow statku
    struct shipShot *nowy = (struct shipShot *) malloc(sizeof(struct shipShot)); // Stworzenie nowej struktury
    if(nowy){ // Jesli sie powiodlo, przypisujemy wartosci i przepinamy wskazniki
        nowy->x= x-dzialo->x;
        nowy->y= y-dzialo->y;
        nowy->dmg = dzialo->dmg;
        nowy->next = NULL;
        nowy->strzalBitmap = dzialo->strzalBitmap;
        if(strzaly->head==NULL)strzaly->head = strzaly->tail = nowy;
        else{
            strzaly->tail->next=nowy;
            strzaly->tail=nowy;
        }
    }
};

void wystrzelZDzial(struct pointersShipShot *strzaly,struct ship *statek){ // Funkcja wywoluje wczesniejsza funkcje na kazdej z 5 mozliwosci przy tylko jednym kliknieciu przycisku myszy
    if(statek->srodkoweDzialo!=NULL)zakolejkujStrzaly(strzaly,statek->srodkoweDzialo,statek->x,statek->y); // Jesli przedmiot NIESPECJALNY znajduje sie na statku to wywolana zostaje funkcja strzalu
    if(statek->leweDzialo!=NULL)zakolejkujStrzaly(strzaly,statek->leweDzialo,statek->x,statek->y);
    if(statek->praweDzialo!=NULL)zakolejkujStrzaly(strzaly,statek->praweDzialo,statek->x,statek->y);
    if(statek->lewyDron!=NULL)zakolejkujStrzalyDrona(strzaly,statek->lewyDron);
    if(statek->prawyDron!=NULL)zakolejkujStrzalyDrona(strzaly,statek->prawyDron);
    statek->y += 30; // 'Odskok" statku po strzale
    al_play_sample(statek->strzalDzwiek,1,0,1,ALLEGRO_PLAYMODE_ONCE, NULL); // Odtworzenie dzwieku wystrzalu
};

void rysujStrzaly(struct pointersShipShot strzaly){ // Rysowanie strzalow na planszy
    while(strzaly.head){
        if(strzaly.head->dmg >0){ // Dopóki mają jakąs wartosc obrazeń to są rysowane
            al_draw_bitmap(strzaly.head->strzalBitmap,strzaly.head->x,strzaly.head->y,0);
        }
    strzaly.head = strzaly.head->next;
    }
}

void ruchStrzalow(struct pointersShipShot *strzaly){ // Ruch strzalow, dodajemy stalą wartosc do poprzedniej wartosci pozycji y strzalu, w celu uzyskania efektu ruchu
    strzaly->q=strzaly->head;
    while(strzaly->q){
        strzaly->q->y -= 360/FPS;
        if(strzaly->q->y <= -20 ){
                struct shipShot *tmp = strzaly->q;
                strzaly->q = strzaly->q->next;
                usunStrzaly(&strzaly,tmp);
                continue;
        }
        strzaly->q = strzaly->q->next;
    }
}

void usunStrzaly(struct pointersShipShot *strzaly, struct shipShot *strzal){ // Usuniecie strzalu ktory wypadl poza mape z listy strzalow staku
    strzaly->q = strzaly->head;
    struct alienShot *tmp = strzaly->q;
    while(strzaly->q!=NULL){
        if(strzaly->q==strzal){
            if(strzaly->head == strzal){
                strzaly->head = strzaly->head->next;
            }
            else{
                tmp->next = strzaly->q->next;
            }
                free(strzaly->q);
            break;
        }
    tmp=strzaly->q;
    strzaly->q=strzaly->q->next;
    }
}


void ruchStatku(struct ship *statek,int myszX, int myszY){ // Funkcja odpowiada za ruch statku w kierunku kursora myszy
    if(statek->x-myszX > 0 && statek->x-myszX > statek->movement) statek->x -= statek->movement; // Jesli statek znajduje sie na prawo i dalej niz wartosc ruchu od kursora to odejmujemy wartosc ruchu od pozycji statku, w ten sposob statek przemieszcza sie w lewo
    else if(statek->x-myszX < 0 && statek->x-myszX < -statek->movement) statek->x += statek->movement;// Jesli statek znajduje sie na lewo i dalej niz wartosc ruchu od kursora to odejmujemy wartosc ruchu od pozycji statku, w ten sposob statek przemieszcza sie w prawo
    else statek->x = myszX; // Jesli statek w osi x znajduje sie blizej kursora niz wartosc ruchu statku to zostaje on poprostu przeteleportowany na kursor
    if(statek->y-myszY > 0 && statek->y-myszY > statek->movement) statek->y -= statek->movement; // Jesli statek znajduje sie w dol i dalej niz wartosc ruchu od kursora to odejmujemy wartosc ruchu od pozycji statku, w ten sposob statek przemieszcza sie w gore
    else if(statek->y-myszY < 0 && statek->y-myszY < -statek->movement) statek->y += statek->movement;// Jesli statek znajduje sie w gore i dalej niz wartosc ruchu od kursora to odejmujemy wartosc ruchu od pozycji statku, w ten sposob statek przemieszcza sie w dol
    else statek->y = myszY;// Jesli statek w osi y znajduje sie blizej kursora niz wartosc ruchu statku to zostaje on poprostu przeteleportowany na kursor
}

void rysujStatek (struct ship statek){ // Rysowanie statku
                if(statek.hp>0 && statek.zycia>=0){ // Jesli ma jakies hp i zycie
                        int INV = statek.niewrazliwosc; // Do zmiennej INV zostaje przypisana wartosc niewrazliwosci statku
                        if(INV%2!=0); // Jesli jest nie podzielna przez dwa, to nie rob nic
                        else  al_draw_bitmap(statek.statekBitmap,statek.x-(statek.szerokosc/2),statek.y-(statek.wysokosc/2),0); // Jesli tak to rysuj statek (daje to efekt migania przy straceniu zycia)
                        if(statek.lewyDron!=NULL){ // Jesli dron jest w posiadaniu gracza to rysuj
                        al_draw_bitmap(statek.lewyDron->dronBitmap,statek.x-(statek.szerokosc/2)-statek.lewyDron->x,statek.y-(statek.wysokosc/2)-statek.lewyDron->y,0);
                        }
                        if(statek.prawyDron!=NULL){ // Jesli dron jest w posiadaniu gracza to rysuj
                        al_draw_bitmap(statek.prawyDron->dronBitmap,statek.x-(statek.szerokosc/2)-statek.prawyDron->x,statek.y-(statek.wysokosc/2)-statek.prawyDron->y,0);
                        }
                }
        }


bool dokladnaKolizjaStatku(struct ship *statek,int xOBJ, int yOBJ, int szerOBJ, int wysOBJ){ // Sprawdzenie dokladniej kolizji obiektu kwadratowego/prostokątnego ze statkiem w ksztalcie trojkąta

            for(int k=0;k<statek->wysokosc/2;k++){ // Jesli znajdziemy kolizje to funkcja zwraca fartosc false
                if(statek->x-(k*0.75)<xOBJ+szerOBJ-1 &&
                statek->x+(k*0.75)>xOBJ+1 &&
                statek->y-(statek->wysokosc/3)+k<yOBJ+wysOBJ-1 &&
                statek->y-(statek->wysokosc/3)+k > yOBJ+1) return false;
                }
            return true; // inaczej zwraca true
}

void sprawdzKolizjeStatkuZKosmita(struct pointersAlien *kosmici,struct ship *statek){ // Sprawdza kolizje statku i kosmity
    kosmici->q=kosmici->head;
    while(kosmici->q && statek->hp>0 && statek->niewrazliwosc<=0){
        if(kosmici->q->hp <= 0); // Jesli kosmita nie ma hp to pomijamy
        else if(dokladnaKolizjaStatku(statek,kosmici->q->x,kosmici->q->y,kosmici->q->szerokoscKosmity,kosmici->q->wysokoscKosmity)); // Jesli ma, to sprawdzana jest dokladna kolizja, jesli zwroci true to pomijamy
        else{ // Jesli false to odbieramy hp graczowi, i kosmicie
                int hpK = kosmici->q->hp;
                kosmici->q->hp -= statek->hp;
                statek->hp -= hpK;

            }
     kosmici->q=kosmici->q->next;
    }
    if(statek->hp<=0 && statek->zycia >=0){ // Jesli statek straci cale hp, to odbierane jest mu zycie i ustawiana zostaje wartosc niewrazliwosci
        statek->zycia -= 1;
        statek->hp =100;
        statek->niewrazliwosc=360/FPS;
    }
}

void dostosujNiewrazliwosc(struct ship *statek,struct settings ustawienia){ // Jesli statek ma jakas niewrazliwosc to zostaje ona zmniejszona o wartosc podaną w ustawieniach
    if(statek->niewrazliwosc>0){
        statek->niewrazliwosc-=ustawienia.spadekNiewrazliwosci;
    }
    else if(statek->niewrazliwosc<0)statek->niewrazliwosc=0; // Jesli spadnie ponizej zera to jest ustawiana na zero
}

void sprawdzKolizjeStatkuZeStrzalem(struct pointersAlienShot *strzaly, struct ship *statek){// Sprawdzanie kolizji statku ze strzalem
    strzaly->q=strzaly->head;
    while(strzaly->q){
            if(statek->niewrazliwosc>0)break; // Jesli statek ma niewrazliwosc to funkcja sie konczy, nie ma sensu sprawdzania jej dalej
            if(strzaly->q->dmg<=0){strzaly->q=strzaly->q->next;continue;} // Jesli strzal nie ma obrazen to przechodzimy do nastepnego
            else if(dokladnaKolizjaStatku(statek,strzaly->q->x,strzaly->q->y,szerokoscStrzalu,wysokoscStrzalu)); // Jesli ma to sprawdzamy dokladna kolizje ze statkiem
            else{ // Jesli fukncja zwroci wartosc false to zabieramy obrazenia strzalu i hp statku
                int hpK = statek->hp;
                statek->hp -=strzaly->q->dmg;
                strzaly->q->dmg -=hpK;
            }
    strzaly->q=strzaly->q->next;
    }
}
