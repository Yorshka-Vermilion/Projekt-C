#include "biblioteki.h"

void rozstawKosmite(struct pointersAlien *kosmici,int pozX, int pozY,struct settingsAlien ustawieniaKosmitow, ALLEGRO_BITMAP **grafikiKosmitow, ALLEGRO_BITMAP **grafikiStrzalow, ALLEGRO_BITMAP **animacjaEksplozji,int rodzaj){ // Funkcja dodaje kosmite do listy kosmitow wskazywanej przez strukture wskaznikow, na pozycji x i y, z ustawieniami ustawieniaKosmitow i dobranymi grafikami
    struct alien *nowy = (struct alien *) malloc(sizeof(struct alien));
    if(nowy){


        if(rodzaj == -1){ // Jesli to 10 mapa to spawnujemy bossa
            nowy->hp = ustawieniaKosmitow.hp*100*poziom.galaktyka; // Przypisanie ustawien z ustawienKosmitow do nowego kosmity
            nowy->dmg = ustawieniaKosmitow.dmg*ustawieniaKosmitow.mnoznik*2;
            nowy->wartosc = ustawieniaKosmitow.wartosc*ustawieniaKosmitow.mnoznik*2;
            nowy->szybkoscStrzalu = ustawieniaKosmitow.szybkoscStrzalu*ustawieniaKosmitow.mnoznik*2;
            nowy->strzalBitmap=grafikiStrzalow[rand()%6];
            nowy->kosmitaBitmap=grafikiKosmitow[9];
            nowy->kosmitaBitmapDef=nowy->kosmitaBitmap;
            nowy->czestotliwoscStrzalow = ustawieniaKosmitow.czestotliwoscStrzalow*ustawieniaKosmitow.mnoznik*10;
        }
        else if(rodzaj==0){ // Losowanie specjalnego kosmity o wartosciach pomnozonych o mnoznik
            nowy->hp = ustawieniaKosmitow.hp*ustawieniaKosmitow.mnoznik*3; // Przypisanie ustawien z ustawienKosmitow do nowego kosmity
            nowy->dmg = ustawieniaKosmitow.dmg*ustawieniaKosmitow.mnoznik;
            nowy->wartosc = ustawieniaKosmitow.wartosc*ustawieniaKosmitow.mnoznik*4;
            nowy->szybkoscStrzalu = ustawieniaKosmitow.szybkoscStrzalu*ustawieniaKosmitow.mnoznik*2;
            nowy->strzalBitmap=grafikiStrzalow[2];
            nowy->kosmitaBitmap=grafikiKosmitow[1];
            nowy->kosmitaBitmapDef=nowy->kosmitaBitmap;
            nowy->czestotliwoscStrzalow = ustawieniaKosmitow.czestotliwoscStrzalow*ustawieniaKosmitow.mnoznik*2;
        }
        else if(rodzaj<5){
            nowy->hp = ustawieniaKosmitow.hp*ustawieniaKosmitow.mnoznik; // Przypisanie ustawien z ustawienKosmitow do nowego kosmity
            nowy->dmg = ustawieniaKosmitow.dmg*ustawieniaKosmitow.mnoznik*3;
            nowy->wartosc = ustawieniaKosmitow.wartosc*ustawieniaKosmitow.mnoznik*2;
            nowy->szybkoscStrzalu = ustawieniaKosmitow.szybkoscStrzalu*ustawieniaKosmitow.mnoznik;
            nowy->strzalBitmap=grafikiStrzalow[1];
            nowy->kosmitaBitmap=grafikiKosmitow[2];
            nowy->kosmitaBitmapDef=nowy->kosmitaBitmap;
            nowy->czestotliwoscStrzalow = ustawieniaKosmitow.czestotliwoscStrzalow*ustawieniaKosmitow.mnoznik;
        }
        else{
            nowy->hp = ustawieniaKosmitow.hp; // Przypisanie ustawien z ustawienKosmitow do nowego kosmity
            nowy->dmg = ustawieniaKosmitow.dmg;
            nowy->wartosc = ustawieniaKosmitow.wartosc;
            nowy->szybkoscStrzalu = ustawieniaKosmitow.szybkoscStrzalu;
            nowy->strzalBitmap=grafikiStrzalow[0];
            nowy->kosmitaBitmap=grafikiKosmitow[0];
            nowy->kosmitaBitmapDef=nowy->kosmitaBitmap;
            nowy->czestotliwoscStrzalow = ustawieniaKosmitow.czestotliwoscStrzalow;
        }
        nowy->szerokoscKosmity = al_get_bitmap_width(nowy->kosmitaBitmap);
        nowy->wysokoscKosmity = al_get_bitmap_height(nowy->kosmitaBitmap);
        nowy->x= pozX*nowy->szerokoscKosmity+10; // Spawnowanie kolejnych mobow
        nowy->y= pozY*nowy->wysokoscKosmity+10;
            if(rodzaj==-1){ // Boss spawnowany na srodku ekranu
                nowy->x= szerokoscEkranu/2-nowy->szerokoscKosmity/2;
                nowy->y= nowy->wysokoscKosmity/5;
            }

        nowy->klatka = ustawieniaKosmitow.klatka;
        nowy->spawn=0; // Wartosc odpowiada za klatke animacji spawnowania

        for(int i=0;i<11;i++){
            nowy->eksplozja[i]=animacjaEksplozji[i]; // Przypisanie 'animacji' eksplozji kosmity
        }

        nowy->dzwiekEksplozji=al_load_sample("dzwieki/eksplozja1.ogg"); // Przypisanie dzwieku eksplozji do danego kosmity
        nowy->next = NULL;

        if(kosmici->head==NULL)kosmici->head = kosmici->tail = nowy;
        else{
            kosmici->tail->next=nowy;
            kosmici->tail=nowy;
        }
    }
    else printf("Error kosmici");
}

void rozstawKosmitow(struct pointersAlien *kosmici,struct settingsAlien ustawieniaKosmitow,struct level poziom, ALLEGRO_BITMAP **grafikiKosmitow, ALLEGRO_BITMAP **grafikiStrzalow, ALLEGRO_BITMAP **animacjaEksplozji){ // Funkcjja uruchamia odpowiednią ilosc razy funkcje rozstawKosmite, na odpowiednich pozycjach na planszy
    if(poziom.mapa<10){ // Jesli mapa jest mniejsza niz 10, to spawnuje normalnie kosmitow
        for(int i=0;i<poziom.liczbaRzedow;i++){
            for(int j=0;j<poziom.liczbaWierszy;j++){
                rozstawKosmite(kosmici,i,j,ustawieniaKosmitow,grafikiKosmitow,grafikiStrzalow,animacjaEksplozji,rand()%40);
            }
        }
    }
    else{ // Jesli to 10 mapa, to spawnuje bossa
        rozstawKosmite(kosmici,0,0,ustawieniaKosmitow,grafikiKosmitow,grafikiStrzalow,animacjaEksplozji,-1);
    }
}

void rysujKosmitow(struct pointersAlien kosmici,struct level *poziom){ // Funkcja rysuje kosmitow
    poziom->pozostaliKosmici=0;
    while(kosmici.head){
        if(kosmici.head->hp>0){
            //al_draw_bitmap(kosmici.head->kosmitaBitmap,kosmici.head->x,kosmici.head->y,0);
            al_draw_scaled_bitmap(kosmici.head->kosmitaBitmap,0,0,al_get_bitmap_width(kosmici.head->kosmitaBitmap),al_get_bitmap_height(kosmici.head->kosmitaBitmap),kosmici.head->x,kosmici.head->y,kosmici.head->szerokoscKosmity,kosmici.head->wysokoscKosmity,0);
            poziom->pozostaliKosmici++;
        }
        else if(kosmici.head->eksplozja[kosmici.head->klatka] && kosmici.head->klatka<11){ // Jesli kosmita nie ma juz hp zostaje nraysowana kolejna klatka animacji wybuchu
                if(kosmici.head->klatka==0) al_play_sample(kosmici.head->dzwiekEksplozji,1,0,1,ALLEGRO_PLAYMODE_ONCE, NULL);
            //al_draw_bitmap(kosmici.head->eksplozja[kosmici.head->klatka],kosmici.head->x,kosmici.head->y,0);
            al_draw_scaled_bitmap(kosmici.head->eksplozja[kosmici.head->klatka],0,0,al_get_bitmap_width(kosmici.head->eksplozja[kosmici.head->klatka]),al_get_bitmap_height(kosmici.head->eksplozja[kosmici.head->klatka]),kosmici.head->x,kosmici.head->y,kosmici.head->szerokoscKosmity,kosmici.head->wysokoscKosmity,0);
            kosmici.head->klatka++;
        }
    kosmici.head = kosmici.head->next;
    }
}

void ruchKosmitow(struct pointersAlien *kosmici){ // Funkcja przesuwa wszystkich kosmitow po kolei
    static int kierunek=1; // Ustawia zmienna kierunek ktora odpowiada za kierunek poruszania sie kosmitow
    kosmici->q=kosmici->head;
    if(kosmici->tail->x+kosmici->q->szerokoscKosmity >  szerokoscEkranu) kierunek=1;
    else if(kosmici->head->x < 0) kierunek =2;

    while(kosmici->q){
        if(kierunek==1){
            kosmici->q->x -= 70/FPS;
        }
        else if(kierunek==2){
            kosmici->q->x += 70/FPS;
        }
        kosmici->q = kosmici->q->next;
    }
}

void sprawdzKolizjeZKosmita(struct pointersShipShot *strzaly, struct pointersAlien *kosmici, struct ship *statek){ // Funkcja sprawdza kolizje strzalow z kosmita
    strzaly->q=strzaly->head;
    while(strzaly->q){ // Dopóki wskaznik q nie wskazuje na NULL
        if(strzaly->q->dmg<=0){strzaly->q=strzaly->q->next;continue;} //Jesli nie posiada juz mocy to nastepuje przejscie do nastpnego strzalu
        kosmici->q=kosmici->head; // Ustawienie wskaznika q na pierwszego kosmite listy
        while(kosmici->q){ // Dopóki wskaznik q nie wskazuje na NULL
            if(kosmici->q->hp <= 0); // Jesli kosmita ma aktualnie jakies HP
            else if((strzaly->q->x > kosmici->q->x + kosmici->q->szerokoscKosmity-1) || // Sprawdzenie czy kosmita NIE koliduje ze strzalem
               (strzaly->q->y > kosmici->q->y + kosmici->q->wysokoscKosmity-1) ||
               (kosmici->q->x > strzaly->q->x + szerokoscStrzalu-1) ||
               (kosmici->q->y > strzaly->q->y + wysokoscStrzalu-1));
            else{ // Jesli kosmita koliduje ze strzalem
                int hpK = kosmici->q->hp; // przypisujemy do wartosci tymczasowej hpK aktualne zycie kosmity
                kosmici->q->hp -=strzaly->q->dmg; // Obnizamy HP kosmity o wartosc obrazen strzalu
                strzaly->q->dmg -=hpK; // Obnizamy obrazenia danego strzalu o wartosc tymczasowa hpK
                if(kosmici->q->hp<=0)statek->kredyty += kosmici->q->wartosc; // Jesli kosmita zginie to do kretydow gracza zostaje dodana jego wartosc
            }
        kosmici->q=kosmici->q->next; // Przepinanie wskaznika
        }
    strzaly->q=strzaly->q->next; // Przepinanie wskaznika
    }
}

void zakolejkujStrzalyKosmitow(struct pointersAlienShot *strzaly, struct pointersAlien kosmici, struct settingsAlien ustawieniaKosmitow){ // Dodajemy nowy strzal do listy srzalow kosmity
    int szansa = 0;
    while(kosmici.head){ // Do póki wskaznik head nie jest NULLEm
        if(kosmici.head->hp <= 0){// Jesli kosmita nie ma juz HP to przechodzimy dalej
                szansa = ustawieniaKosmitow.dodatkowaSzansa; // Nastepny kosmita ma dodatkowe szanse na strzal (w celu zbalansowania strzalow kiedy na mapie zostalo malo kosmitow)
                kosmici.head=kosmici.head->next; // Przepiecie wskaznika
                continue;
        }
            if((rand()%5000)<=kosmici.head->czestotliwoscStrzalow+szansa){ // Losujemy wartosc z przedzialu, jesli jest mniejsza lub rowna czestotliwosci strzalow opisanej w strukturze ustawieniaKosmitow to

                struct alienShot *nowy = (struct alienShot *) malloc(sizeof(struct alienShot)); // Tworzenie i wstawienie do listy nowego elementu
                if(nowy){
                    nowy->x= kosmici.head->x+(kosmici.head->szerokoscKosmity/2);
                    nowy->y= kosmici.head->y+kosmici.head->wysokoscKosmity;
                    nowy->strzalBitmap = kosmici.head->strzalBitmap;
                    nowy->dmg = kosmici.head->dmg;
                    nowy->next = NULL;
                    nowy->szybkosc = kosmici.head->szybkoscStrzalu;
                    if(strzaly->head==NULL)strzaly->head = strzaly->tail = nowy;
                    else{
                        strzaly->tail->next=nowy;
                        strzaly->tail=nowy;
                    }
                }
                if(kosmici.head->szerokoscKosmity>50){
                    struct alienShot *nowy2 = (struct alienShot *) malloc(sizeof(struct alienShot));
                    struct alienShot *nowy3 = (struct alienShot *) malloc(sizeof(struct alienShot));
                    nowy2->x= kosmici.head->x+(kosmici.head->szerokoscKosmity)-10;
                    nowy3->x= kosmici.head->x+10;
                    nowy2->y= kosmici.head->y+kosmici.head->wysokoscKosmity-1;
                    nowy3->y= kosmici.head->y+kosmici.head->wysokoscKosmity-2;
                    nowy2->strzalBitmap = kosmici.head->strzalBitmap;
                    nowy3->strzalBitmap = kosmici.head->strzalBitmap;
                    nowy2->dmg = kosmici.head->dmg;
                    nowy3->dmg = kosmici.head->dmg;
                    nowy2->szybkosc = kosmici.head->szybkoscStrzalu;
                    nowy3->szybkosc = kosmici.head->szybkoscStrzalu;
                    nowy->next = nowy2;
                    nowy2->next = nowy3;
                    nowy3->next = NULL;
                    strzaly->tail=nowy3;
                }
            szansa = 0;
        }
    kosmici.head=kosmici.head->next;
    }
};

void ruchStrzalowKosmitow(struct pointersAlienShot *strzaly){ // Funkcja 'rusza' strzaly kosmitow, czyli dodaje wartosc szybkosci poruszania sie strzalu podzielonej przez FPS do wartosci y danego strzalu jesli strzal wyjdzie poza mape+20px to zostaje usuniety z listy strzalow
    strzaly->q=strzaly->head;
    while(strzaly->q){
        strzaly->q->y += strzaly->q->szybkosc/FPS;
        if(strzaly->q->y > wysokoscEkranu+20){
                struct alienShot *tmp = strzaly->q;
                strzaly->q = strzaly->q->next;
                usunStrzalyKosmitow(&strzaly,tmp);
                continue;
        }
        strzaly->q = strzaly->q->next;
    }
}

void usunStrzalyKosmitow(struct pointersAlienShot *strzaly, struct alienShot *strzal){ // Usuwa strzaly kosmitow ktore wypadly poza mape
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

void rysujStrzalyKosmitow(struct pointersAlienShot strzaly,int *strzalyBitmap){ // Rysuje strzaly kosmitow
    while(strzaly.head){
        if(strzaly.head->dmg >0){
            al_draw_bitmap(strzaly.head->strzalBitmap,strzaly.head->x,strzaly.head->y,0);
        }
    strzaly.head = strzaly.head->next;
    }
}

void usunKosmitow(struct pointersAlien *kosmici){ // Czysci cala liste kosmitow (na koniec mapy/gry)
    while(kosmici->head){
        struct alien *tmp = kosmici->head->next;
        free(kosmici->head);
        kosmici->head = tmp;
        if(tmp==NULL)kosmici->tail = NULL;
    }
};

void zaladujAnimacjeSpawnuKosmity(ALLEGRO_BITMAP **spawnKosmity){ // Funkcja laduje animacje spawnowania kosmitow
    spawnKosmity[0]=al_load_bitmap("grafiki/spawn/frame0017.png");
    spawnKosmity[1]=al_load_bitmap("grafiki/spawn/frame0018.png");
    spawnKosmity[2]=al_load_bitmap("grafiki/spawn/frame0019.png");
    spawnKosmity[3]=al_load_bitmap("grafiki/spawn/frame0020.png");
    spawnKosmity[4]=al_load_bitmap("grafiki/spawn/frame0021.png");
    spawnKosmity[5]=al_load_bitmap("grafiki/spawn/frame0022.png");
    spawnKosmity[6]=al_load_bitmap("grafiki/spawn/frame0023.png");
    spawnKosmity[7]=al_load_bitmap("grafiki/spawn/frame0024.png");
    spawnKosmity[8]=al_load_bitmap("grafiki/spawn/frame0025.png");
    spawnKosmity[9]=al_load_bitmap("grafiki/spawn/frame0026.png");
    spawnKosmity[10]=al_load_bitmap("grafiki/spawn/frame0027.png");
    spawnKosmity[11]=al_load_bitmap("grafiki/spawn/frame0028.png");
    spawnKosmity[12]=al_load_bitmap("grafiki/spawn/frame0029.png");
    spawnKosmity[13]=al_load_bitmap("grafiki/spawn/frame0030.png");
    spawnKosmity[14]=al_load_bitmap("grafiki/spawn/frame0031.png");
    spawnKosmity[15]=al_load_bitmap("grafiki/spawn/frame0032.png");
    spawnKosmity[16]=al_load_bitmap("grafiki/spawn/frame0033.png");
    spawnKosmity[17]=al_load_bitmap("grafiki/spawn/frame0034.png");
    spawnKosmity[18]=al_load_bitmap("grafiki/spawn/frame0035.png");
    spawnKosmity[19]=al_load_bitmap("grafiki/spawn/frame0036.png");
    spawnKosmity[20]=al_load_bitmap("grafiki/spawn/frame0037.png");
    spawnKosmity[21]=al_load_bitmap("grafiki/spawn/frame0038.png");
    spawnKosmity[22]=al_load_bitmap("grafiki/spawn/frame0039.png");
    spawnKosmity[23]=al_load_bitmap("grafiki/spawn/frame0040.png");
    spawnKosmity[24]=al_load_bitmap("grafiki/spawn/frame0041.png");
    spawnKosmity[25]=al_load_bitmap("grafiki/spawn/frame0042.png");
    spawnKosmity[26]=al_load_bitmap("grafiki/spawn/frame0043.png");
    spawnKosmity[27]=al_load_bitmap("grafiki/spawn/frame0044.png");
    spawnKosmity[28]=al_load_bitmap("grafiki/spawn/frame0045.png");
    spawnKosmity[29]=al_load_bitmap("grafiki/spawn/frame0046.png");
    spawnKosmity[30]=al_load_bitmap("grafiki/spawn/frame0047.png");
    spawnKosmity[31]=al_load_bitmap("grafiki/spawn/frame0048.png");
    spawnKosmity[32]=al_load_bitmap("grafiki/spawn/frame0049.png");
    spawnKosmity[33]=al_load_bitmap("grafiki/spawn/frame0050.png");
    spawnKosmity[34]=al_load_bitmap("grafiki/spawn/frame0051.png");
    spawnKosmity[35]=al_load_bitmap("grafiki/spawn/frame0052.png");
    spawnKosmity[36]=al_load_bitmap("grafiki/spawn/frame0053.png");
    spawnKosmity[37]=al_load_bitmap("grafiki/spawn/frame0054.png");
    spawnKosmity[38]=al_load_bitmap("grafiki/spawn/frame0055.png");
    spawnKosmity[39]=al_load_bitmap("grafiki/spawn/frame0056.png");
    spawnKosmity[40]=al_load_bitmap("grafiki/spawn/frame0057.png");
    spawnKosmity[41]=al_load_bitmap("grafiki/spawn/frame0058.png");
    spawnKosmity[42]=al_load_bitmap("grafiki/spawn/frame0059.png");
    spawnKosmity[43]=al_load_bitmap("grafiki/spawn/frame0060.png");
    spawnKosmity[44]=al_load_bitmap("grafiki/spawn/frame0061.png");
    spawnKosmity[45]=al_load_bitmap("grafiki/spawn/frame0062.png");
    spawnKosmity[46]=al_load_bitmap("grafiki/spawn/frame0063.png");
    spawnKosmity[47]=al_load_bitmap("grafiki/spawn/frame0064.png");
    spawnKosmity[48]=al_load_bitmap("grafiki/spawn/frame0065.png");
    spawnKosmity[49]=al_load_bitmap("grafiki/spawn/frame0066.png");
    spawnKosmity[50]=al_load_bitmap("grafiki/spawn/frame0067.png");
    spawnKosmity[51]=al_load_bitmap("grafiki/spawn/frame0068.png");
    spawnKosmity[52]=al_load_bitmap("grafiki/spawn/frame0069.png");
    spawnKosmity[53]=al_load_bitmap("grafiki/spawn/frame0070.png");
    spawnKosmity[54]=al_load_bitmap("grafiki/spawn/frame0071.png");
    spawnKosmity[55]=al_load_bitmap("grafiki/spawn/frame0072.png");
    spawnKosmity[56]=al_load_bitmap("grafiki/spawn/frame0073.png");
    spawnKosmity[57]=al_load_bitmap("grafiki/spawn/frame0074.png");
    spawnKosmity[58]=al_load_bitmap("grafiki/spawn/frame0075.png");
    spawnKosmity[59]=al_load_bitmap("grafiki/spawn/frame0076.png");
    spawnKosmity[60]=al_load_bitmap("grafiki/spawn/frame0077.png");
    spawnKosmity[61]=al_load_bitmap("grafiki/spawn/frame0078.png");
    spawnKosmity[62]=al_load_bitmap("grafiki/spawn/frame0079.png");
    spawnKosmity[63]=al_load_bitmap("grafiki/spawn/frame0080.png");
    spawnKosmity[64]=al_load_bitmap("grafiki/spawn/frame0081.png");
    spawnKosmity[65]=al_load_bitmap("grafiki/spawn/frame0082.png");
    spawnKosmity[66]=al_load_bitmap("grafiki/spawn/frame0083.png");
    spawnKosmity[67]=al_load_bitmap("grafiki/spawn/frame0084.png");
    spawnKosmity[68]=al_load_bitmap("grafiki/spawn/frame0085.png");
    spawnKosmity[69]=al_load_bitmap("grafiki/spawn/frame0086.png");
    spawnKosmity[70]=al_load_bitmap("grafiki/spawn/frame0087.png");
    spawnKosmity[71]=al_load_bitmap("grafiki/spawn/frame0088.png");
    spawnKosmity[72]=al_load_bitmap("grafiki/spawn/frame0089.png");
    spawnKosmity[73]=al_load_bitmap("grafiki/spawn/frame0090.png");
    spawnKosmity[74]=al_load_bitmap("grafiki/spawn/frame0091.png");
    spawnKosmity[75]=al_load_bitmap("grafiki/spawn/frame0092.png");
    spawnKosmity[76]=al_load_bitmap("grafiki/spawn/frame0093.png");
    spawnKosmity[77]=al_load_bitmap("grafiki/spawn/frame0094.png");
    spawnKosmity[78]=al_load_bitmap("grafiki/spawn/frame0095.png");
    spawnKosmity[79]=al_load_bitmap("grafiki/spawn/frame0096.png");
    spawnKosmity[80]=al_load_bitmap("grafiki/spawn/frame0097.png");
    spawnKosmity[81]=al_load_bitmap("grafiki/spawn/frame0098.png");
    spawnKosmity[82]=al_load_bitmap("grafiki/spawn/frame0099.png");
    spawnKosmity[83]=al_load_bitmap("grafiki/spawn/frame0100.png");
    spawnKosmity[84]=al_load_bitmap("grafiki/spawn/frame0101.png");
    spawnKosmity[85]=al_load_bitmap("grafiki/spawn/frame0102.png");
    spawnKosmity[86]=al_load_bitmap("grafiki/spawn/frame0103.png");
    spawnKosmity[87]=al_load_bitmap("grafiki/spawn/frame0104.png");
    spawnKosmity[88]=al_load_bitmap("grafiki/spawn/frame0105.png");
    spawnKosmity[89]=al_load_bitmap("grafiki/spawn/frame0106.png");
    spawnKosmity[90]=al_load_bitmap("grafiki/spawn/frame0107.png");
    spawnKosmity[91]=al_load_bitmap("grafiki/spawn/frame0108.png");
    spawnKosmity[92]=al_load_bitmap("grafiki/spawn/frame0109.png");
    spawnKosmity[93]=al_load_bitmap("grafiki/spawn/frame0110.png");
    spawnKosmity[94]=al_load_bitmap("grafiki/spawn/frame0111.png");
    spawnKosmity[95]=al_load_bitmap("grafiki/spawn/frame0112.png");
    spawnKosmity[96]=al_load_bitmap("grafiki/spawn/frame0113.png");
    spawnKosmity[97]=al_load_bitmap("grafiki/spawn/frame0114.png");
    spawnKosmity[98]=al_load_bitmap("grafiki/spawn/frame0115.png");
    spawnKosmity[99]=al_load_bitmap("grafiki/spawn/frame0116.png");

}

void spawnKosmitow(struct pointersAlien kosmici, ALLEGRO_BITMAP **spawnKosmity){ // Funkcja zwieksza wartosc klatki spawnowania kosmitow o 1 przy kazdym zdarzeniu timera
    while(kosmici.head){
            if(kosmici.head->spawn>=99){
               kosmici.head->kosmitaBitmap = kosmici.head->kosmitaBitmapDef;
               kosmici.head->spawn++;
            }
            else{
                kosmici.head->kosmitaBitmap = spawnKosmity[kosmici.head->spawn];
                kosmici.head->spawn++;
            }
    kosmici.head=kosmici.head->next;
    }
}

