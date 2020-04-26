#include "biblioteki.h"

int main(){
    //Inicjacja dodatkow biblioteki allegro
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(100); // Rezerwowanie probek dzwieku

    ALLEGRO_EVENT_QUEUE * kolejka; // Tworzenie wskaznika na kolejke
    ALLEGRO_DISPLAY * display = al_create_display(szerokoscEkranu,wysokoscEkranu); //Tworzenie ekranu
    ALLEGRO_FONT * font =  al_load_font("czcionki/Terminus 8x8.ttf",12,0); // Tworzenie czcionki
    ALLEGRO_FONT * font2 =  al_load_font("czcionki/Terminus 8x8.ttf",8,0); // Tworzenie czcionki
    ALLEGRO_FONT * fontPlus =  al_load_font("czcionki/Terminus 8x8.ttf",24,0); // Tworzenie czcionki
    ALLEGRO_BITMAP * dronBitmap, * strzalBitmap, *strzal2Bitmap, *eksplozjaKosmity1[11], *spawnKosmity[100], *grafikiKosmitow[10], *grafikiStrzalow[10], *animacjaEksplozji[11];// Tworzenie bitmap
    ALLEGRO_TIMER * timer; // Tworzenie timera wywolujacego zdarzenia w kolejce

    timer = al_create_timer(1.0/FPS); // Ustawienie opoznienia timera
    srand(time(NULL)); // Ustawienie losowosci
    kolejka = al_create_event_queue(); // Tworzenie kolejki

    al_install_mouse(); // Instalacja obslugi myszy
    al_install_keyboard(); // Instalacja obslugi klawiatury

    // Dodanie do kolejki, funkcji umożliwających odbieranie zdarzen z ekranu, timera, klawiatury i myszy

    al_register_event_source(kolejka, al_get_display_event_source(display));
    al_register_event_source(kolejka, al_get_timer_event_source(timer));
    al_register_event_source(kolejka, al_get_keyboard_event_source());
    al_register_event_source(kolejka, al_get_mouse_event_source());

    //Ładowanie grafik startowych do pamięci wskazywanej przez wskaźnik
    grafikiKosmitow[0] = al_load_bitmap("grafiki/kosmita.png"); // Ladowanie grafik kosmitow
    grafikiKosmitow[1] = al_load_bitmap("grafiki/kosmita2.png");
    grafikiKosmitow[2] = al_load_bitmap("grafiki/kosmita3.png");
    grafikiKosmitow[9] = al_load_bitmap("grafiki/boss.png");
    grafikiStrzalow[0] = al_load_bitmap("grafiki/strzalK1.png"); // Ladowanie grafik strzalow kosmitow
    grafikiStrzalow[1] = al_load_bitmap("grafiki/strzalK2.png");
    grafikiStrzalow[2] = al_load_bitmap("grafiki/strzalK3.png");
    grafikiStrzalow[3] = al_load_bitmap("grafiki/strzalK4.png");
    grafikiStrzalow[4] = al_load_bitmap("grafiki/strzalK5.png");
    grafikiStrzalow[5] = al_load_bitmap("grafiki/strzalK6.png");
    grafikiStrzalow[6] = al_load_bitmap("grafiki/strzalK7.png");

    animacjaEksplozji[0]=al_load_bitmap("grafiki/eksplozje/kosmita1/1.png"); // Przypisanie 'animacji' eksplozji kosmity
    animacjaEksplozji[1]=al_load_bitmap("grafiki/eksplozje/kosmita1/2.png");
    animacjaEksplozji[2]=al_load_bitmap("grafiki/eksplozje/kosmita1/3.png");
    animacjaEksplozji[3]=al_load_bitmap("grafiki/eksplozje/kosmita1/4.png");
    animacjaEksplozji[4]=al_load_bitmap("grafiki/eksplozje/kosmita1/5.png");
    animacjaEksplozji[5]=al_load_bitmap("grafiki/eksplozje/kosmita1/6.png");
    animacjaEksplozji[6]=al_load_bitmap("grafiki/eksplozje/kosmita1/7.png");
    animacjaEksplozji[7]=al_load_bitmap("grafiki/eksplozje/kosmita1/8.png");
    animacjaEksplozji[8]=al_load_bitmap("grafiki/eksplozje/kosmita1/9.png");
    animacjaEksplozji[9]=al_load_bitmap("grafiki/eksplozje/kosmita1/10.png");
    animacjaEksplozji[10]=al_load_bitmap("grafiki/eksplozje/kosmita1/11.png");


    statek.statekBitmap = al_load_bitmap("grafiki/statek2.png");

    strzalBitmap = al_load_bitmap("grafiki/strzal.png");

    dronBitmap = al_load_bitmap("grafiki/dron.png");

    sklep.pole = al_load_bitmap("grafiki/sklep/srodkoweDzialo.png");
    menu.bitmap = al_load_bitmap("grafiki/menu.png");



    zaladujAnimacjeSpawnuKosmity(&spawnKosmity); // Funkcja ładująca animacje spawnowania kosmitów

    // Ustawienia
    int myszX=0; // Ustawienie wartosci zmiennej w ktorej znajduje sie wspołżędna x myszy na ekranie
    int myszY=0; // Ustawienie wartosci zmiennej w ktorej znajduje sie wspołżędna y myszy na ekranie

        // Ustawienia poczatkowe struktury poziom
    poziom.start=false; // Strat poziomu
    poziom.koniecPoziomu=false; // Koniec poziomu
    poziom.koniecGry=false; // Koniec gry
    poziom.set=false; // *.set okresla czy struktura zostala juz ustawiona
    poziom.spawned = false; // Wartosc odpowiadajaca statusowi zespawnowania kosmitow na mapie, true dla skonczonej operacji
    zaladujMapy(&poziom);

    gra.set=false; // Wartosc logiczna opdowiadajaca za rozpoczynanie gry
    sklep.set=false; // Wartosc logiczna odpowiadajaca za wchodzenie do sklepu

        // Ustawienia menu
    menu.set = true; // Wartosc logiczna odpowiadajaca za wchodzenie do menu poczatkowego
    menu.opcje[0]=ustawOpcje("Nowa gra",szerokoscEkranu/2 , wysokoscEkranu/2-100); // Ustawienia wyswietlania tekstu w menu
    menu.opcje[1]=ustawOpcje("Wyniki",szerokoscEkranu/2 , wysokoscEkranu/2);
    menu.opcje[2]=ustawOpcje("Wyjscie",szerokoscEkranu/2 , wysokoscEkranu/2+100);
    menu.czcionka = al_load_font("czcionki/Terminus 8x8.ttf",20,0); // Ładowanie czcionki wyswietlanej w menu
    menu.wybor = 0; // Okresla która opcja jest zaznaczona/wybrana

        // Ustawienia okna z wynikami
    wyniki.set=false; // Wartosc logiczna odpowiadajaca za wchodzenie do okna wynikow
    wyniki.wczytano = false; // Wartosc sprawdzajaca czy wyniki zostaly juz wczytane czy trzeba wczytac je od nowa
    wyniki.rozmiarCzcionki = 15; // Rozmiar czcionki w oknie wynikow
    wyniki.czcionka = al_load_font("czcionki/Terminus 8x8.ttf",wyniki.rozmiarCzcionki,0); // Ładowanie czcionki wyswietlanej w oknie wynikow
    wyniki.scroll = 0; // Wartosc odpowiadająca za poczatkowy wynik wyswietlany w oknie wynikow

    int exit=1; // Wartosc odpowiadajaca za wykonywanie glownej petli programu
    al_start_timer(timer); // Wystartowanie timera

    while(exit){ //Menu głowne
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Rysowanie calego ekranu do danym kolorem
    ALLEGRO_EVENT event; // Stworzenie struktury ALLEGRO_EVENT odpowiadajacej za odczytywanie zdarzeń
    al_wait_for_event(kolejka,&event); // Funkcja czeka na jakiekolwiek zdarzenie, nie wykonuje bezcelowo programu jeśli nic sie nie dzieje
        if(menu.set==true){ // Wejscie do menu
            al_draw_bitmap(menu.bitmap,0,0,0);
            for(int i=0;i<3;i++){ // Rysowanie opcji w menu
                if(i<2){ // Dwie opcje na bialo
                al_draw_text(menu.czcionka , al_map_rgb(255 , 255 , 255) , menu.opcje[i]->x , menu.opcje[i]->y , ALLEGRO_ALIGN_CENTRE   , menu.opcje[i]->tresc);
                } // Jedna na czarno
                else al_draw_text(menu.czcionka , al_map_rgb(0 , 0 , 0) , menu.opcje[i]->x , menu.opcje[i]->y , ALLEGRO_ALIGN_CENTRE   , menu.opcje[i]->tresc);

                if(menu.wybor==i){ // Jesli wybor to aktualnie rysowana opcja to dorysuj dotatkowe ikony po bokach opcji
                    int odstep = strlen(menu.opcje[i]->tresc)*20/2+10;
                    al_draw_bitmap(dronBitmap,menu.opcje[i]->x+odstep,menu.opcje[i]->y,0);
                    al_draw_bitmap(dronBitmap,menu.opcje[i]->x-odstep-al_get_bitmap_width(dronBitmap),menu.opcje[i]->y,0);
                }
            }
            al_flip_display(); // Funkcja odpowiada za wyswietlenie na ekranie narysowanych bitmap
        }


        if(event.type == ALLEGRO_EVENT_KEY_DOWN){ // Sprawdzanie typu wywołanego zdarzenia, w tym przypadku jest to nacisniecie klawisza
                    switch(event.keyboard.keycode){ // Sprawdzanie który dokładnie klawisz został wcisniety

                        case ALLEGRO_KEY_ESCAPE: // ESCAPE
                            if(poziom.koniecPoziomu==true)zapiszWynik(statek,poziom); // Jesli jakikolwiek poziom zostal juz rozpoczety nastepuje zapis wyniku
                            exit=0; // Wyjscie z programu
                        break;

                        case ALLEGRO_KEY_DOWN: // Strzalka w dol
                            if(menu.wybor==2)menu.wybor=0; // Sprawdzanie czy mozna jeszcze zejsc nizej, jesli nie wracamy na poczatek listy opcji
                            else menu.wybor++; // jesli tak, idziemy o jeden w dol
                        break;

                        case ALLEGRO_KEY_UP: // Strzalka w gore
                            if(menu.wybor==0)menu.wybor=2; // Sprawdzanie czy mozna jeszcze zejsc wyzej, jesli nie idziemy na koniec listy opcji
                            else menu.wybor--; // jesli tak, idziemy o jeden w gore
                        break;

                        case ALLEGRO_KEY_ENTER: // ENTER
                            al_flush_event_queue(kolejka); // Czysczenie kolejki ze zdarzen
                            wyborOpcji(menu.wybor,&exit); // Funkcja sprawdzajaca jaka opcja jest aktualnie zaznaczona
                        break;                            //w celu ustawienia odpowiednich wartosci w strukturach (przejscia do innego okna , lub wyjsciu z programu
                    }
                }
        al_flush_event_queue(kolejka); // Czysczenie kolejki ze zdarzen

        while(poziom.start==true && exit && poziom.koniecGry==false && sklep.set == false){ //Glowna petla poziomu
            if(gra.set==false){ //Wczytywanie domyślnych ustawień, ustawianie nowej gry
                poziom.liczbaRzedow = 15; // Ustawia pożądaną liczbe rzedow kosmitow
                poziom.liczbaWierszy = 5; // Ustawia pozadana liczbe wierszy kosmitow

                poziom.mapa=1; // Ustawia poczatkowa mape (poziom)
                poziom.galaktyka=1; // Ustawia poczatkowa galaktyke
                poziom.przerywnik = true; // Ustawia wyswietlanie przerywnika
                poziom.spawned = false; // Ustawia wartosc logiczna z ktorej wynika czy kosmici sa juz na mapie czy dopiero sie spawnują

                ustawienia.spadekNiewrazliwosci=0.1; // Szybkosc z jaka statek traci swoją niewrażliwosc po straceniu zycia

                // Ustawienia kosmitow
                ustawieniaKosmitow.czestotliwoscStrzalow=3; // Ustawia poczatkowa czestotliwosc strzalow kosmitow
                ustawieniaKosmitow.dmg=40; // Ustawia poczatkowe obrazenia kosmitow
                ustawieniaKosmitow.hp=90; // Ustawia poczatkowe HP kosmitow
                ustawieniaKosmitow.wartosc=25; // Ustawia początkową wartosc, czyli kredyty jakie otrzymuje gracz po zniszczeniu kosmity
                ustawieniaKosmitow.szybkoscStrzalu=120; // Ustawia poczatkową szybkosc strzalu z jaką porusza sie pocisk kosmity
                ustawieniaKosmitow.klatka=0; // Zeruje klatke wybuchu aby nie pojawila sie zadna losowa wartosc
                ustawieniaKosmitow.dodatkowaSzansa=10; // Dodatkowa szansa na strzal
                ustawieniaKosmitow.mnoznik=2; // Ustawienie wartosci mnoznika dla specjalnych kosmitow, mozna go traktowac jak poziom trudnosci

                // Ustawienia statku
                statek.movement = 8; // Ustawia poczatkowa wartosc poruszania sie
                statek.hp = 100; // HP
                statek.dmg = 100; // Obrazenia
                statek.zycia = 3; // Zycia
                statek.maxHP=statek.hp; // Ustawienie maksymalnego hp
                statek.niewrazliwosc = 10; // Niewrazliwosc po stracie zycia/rozpoczeciu gry
                statek.kredyty=0; // Kredyty poczatkowe
                statek.szerokosc = al_get_bitmap_width(statek.statekBitmap); // Funkcja sprawdza szerokosc bitmapy i zwraca jej wartosc
                statek.wysokosc = al_get_bitmap_height(statek.statekBitmap); // Funkcja sprawdza wysokosc bitmapy i zwraca jej wartosc
                statek.strzalDzwiek = al_load_sample("dzwieki/strzal.ogg"); // Wczytanie dzwieku strzalu statku do struktury
                statek.srodkoweDzialo = stworzNoweDzialo(2,statek.wysokosc/3,strzalBitmap); // Tworzenie nowego dziala, na pozycji x,y z podaną grafiką wystrzalu
                statek.lewyDron = NULL; // Ustawienie pustego wskaznika na lewego drona
                statek.prawyDron = NULL; // Ustawienie pustego wskaznika na prawego drona

                // Ustawienia sklepu
                sklep.szerokoscPola = al_get_bitmap_width(sklep.pole); // Funkcja sprawdza szerokosc bitmapy i zwraca jej wartosc
                sklep.wysokoscPola = al_get_bitmap_height(sklep.pole); // Funkcja sprawdza wysokosc bitmapy i zwraca jej wartosc
                sklep.tlo = al_load_bitmap("grafiki/sklep/sklep.png");

                    // Tworzenie przedmiotow
                sklep.przedmiot[0]=stworzPrzedmiot("Srodkowe dzialo",szerokoscEkranu/2-sklep.szerokoscPola/2,wysokoscEkranu/2-130,500,true,false,al_load_bitmap("grafiki/sklep/srodkoweDzialo.png"));
                sklep.przedmiot[1]=stworzPrzedmiot("Lewe Dzialo",szerokoscEkranu/2-sklep.szerokoscPola/2-102,wysokoscEkranu/2-80,500,true,false,al_load_bitmap("grafiki/sklep/leweDzialo.png"));
                sklep.przedmiot[2]=stworzPrzedmiot("Prawe Dzialo",szerokoscEkranu/2-sklep.szerokoscPola/2+102,wysokoscEkranu/2-80,500,true,false,al_load_bitmap("grafiki/sklep/praweDzialo.png"));
                sklep.przedmiot[3]=stworzPrzedmiot("Naped",szerokoscEkranu/2-sklep.szerokoscPola/2,wysokoscEkranu/2+100,5000,true,true,al_load_bitmap("grafiki/sklep/naped.png"));
                sklep.przedmiot[4]=stworzPrzedmiot("Lewy Dron",szerokoscEkranu/2-statek.szerokosc/1.59-sklep.szerokoscPola/2,wysokoscEkranu/2+75,500,true,false,al_load_bitmap("grafiki/sklep/lewyDron.png"));
                sklep.przedmiot[5]=stworzPrzedmiot("Prawy Dron",szerokoscEkranu/2+statek.szerokosc/1.59-sklep.szerokoscPola/2,wysokoscEkranu/2+75,500,true,false,al_load_bitmap("grafiki/sklep/prawyDron.png"));
                // Ustawienia pozycji statku na ekranie
                statek.x = szerokoscEkranu/2;
                statek.y = wysokoscEkranu*0.9;
                // Ustawienia poczatkowej wartosci zmiennych odpowiadających za pozycje myszki
                myszX=szerokoscEkranu/2;
                myszY=wysokoscEkranu*0.9;

                galaktyka.set=true; // Przy ustawieniu gry, automatycznie zostala ustawiona galaktyka
                gra.set=true; // Koniec ustawień gry
            }
            if(galaktyka.set==false){ // Ustawienia galaktyki
                poziom.przerywnik = true; // Aktywacja przerywnika
                poziom.spawned = false; // Kosmici niezespawnowani
                ustawieniaKosmitow.czestotliwoscStrzalow+=1; // Zwiekszenie czestotliwosci strzalow
                ustawieniaKosmitow.wartosc+=25; // Zwiekszenie wartosci kosmitow
                ustawieniaKosmitow.szybkoscStrzalu+=20; // Zwiekszenie predkosci poruszania sie pocisku
                statek.maxHP += 50;
                galaktyka.set=true; // Galaktyka ustawiona

                // Ustawienie statku na ekranie
                statek.x = szerokoscEkranu/2; // x
                statek.y = wysokoscEkranu*0.9; // y
            }

            if(poziom.set==false && poziom.przerywnik==false){ // Jesli poziom nie zostal ustawiony i przerywnik nie jest juz aktywny
                wyczyscPamiec(&kosmici,&strzalyKosmitow,&strzaly); // Czyszczenie pozostalosci z poptrzedniej mapy

                ustawieniaKosmitow.hp+=10; // Zwiekszenie HP kosmity
                ustawieniaKosmitow.dmg+=5; // Zwiekszenie obrazen kosmity

                rozstawKosmitow(&kosmici,ustawieniaKosmitow,poziom,grafikiKosmitow,grafikiStrzalow,animacjaEksplozji); // Tworzenie kosmitow, przekazanie struktury wskaznikowej, struktury z ustawieniami kosmitow i struktury z poziomem
                poziom.spawned=false; // Kosmici nie zostali jeszcze zespawnowani
                poziom.set=true; // Poziom zostal ustawiony
            }

                al_wait_for_event(kolejka,&event); // Czekanie na zdarzenie

                if (event.type == ALLEGRO_EVENT_MOUSE_AXES) { // Jesli zdarzenie to ruch myszki, to odpowiednie zmienne przyjmują wartosc pozycji kursora na ekranie
                    myszX=event.mouse.x;
                    myszY=event.mouse.y;
                    }

                else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ // Jesli zostal wcisniety jakis klawisz...
                    switch(event.keyboard.keycode){ // Sprawdz który
                        case ALLEGRO_KEY_ESCAPE: // Jesli ESCAPE
                        menu.set=true; // Wroc to menu
                        poziom.koniecGry=true; // Koniec gry
                        poziom.koniecPoziomu=true; // Koniec poziomu
                        break;
                    }
                }

                else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && statek.hp>0 && poziom.spawned == true) { // Jesli przycisk myszki zostal wcisniety,
                                                                                                                    //hp statku wieksze niz 0 i kosmici zostali juz zespawnowani..
                    wystrzelZDzial(&strzaly,&statek); // to wystrzel z dzial statku i dronow jesli istnieja
                }


                else if(event.type == ALLEGRO_EVENT_TIMER){ // Jesli zdarzenie zostalo wywolane przez "tykający" timer

                    al_draw_bitmap(poziom.bitmapa[poziom.mapa-1],0,0,0); // Narysowanie tla
                    ruchStatku(&statek,myszX,myszY); // Rusz statkiem w strone kursora o wartosc zapisana w strukturze statku
                    dostosujNiewrazliwosc(&statek,ustawienia); // Jesli statek jest aktualnie w stanie niewrazliwosci to zmniejsz ta wartosc o podana wartosc w ustawieniach

                    if(kosmici.head != NULL && poziom.przerywnik==false){ // Jesli sa jacys kosmici i przerywnik zostal juz skonczony

                        if(poziom.spawned==false){ // Jesli kosmici nie sa jeszcze zespawnowani
                            spawnKosmitow(kosmici,&spawnKosmity); // Ustaw klatke spawnowania kosmitow na jedna wiecej
                            if(kosmici.head->spawn>99)poziom.spawned=true; // Jesli klatka osiagnela wartosc 100 to kosmici zespawnowani
                        }
                        else{ // Jesli zostali juz zespawnowani
                            sprawdzKolizjeStatkuZKosmita(&kosmici,&statek); // Sprawdzanie kolizji statku z kosmita
                            ruchKosmitow(&kosmici); // Ruch kosmitow w poziomie
                            zakolejkujStrzalyKosmitow(&strzalyKosmitow,kosmici,ustawieniaKosmitow); // Strzal losowych kosmitow
                        }

                        rysujKosmitow(kosmici,&poziom); // Rysowanie kosmitow na ekranie

                        if(poziom.pozostaliKosmici==0 && kosmici.head->klatka>10){ // Jesli zostalo 0 kosmitow
                                poziom.mapa++; // Zwieksz numer mapy
                                poziom.klatka=0; // Ustaw klatke odpowiadajaco za wyswietlanie przerywnika na 0
                            if(poziom.mapa>10){ // Jesli mapa wieksza niz 10
                                ustawSklep(&sklep,&statek); // Ustaw sklep
                                poziom.koniecPoziomu=true; // Koniec poziomu
                                sklep.zaMalo = false; // Nie wyswietlaj juz powiadomienia o zbyt malej ilosci kredytow
                                sklep.set = true; // Wejdz do sklepu aktywowane
                                galaktyka.set=false; // Galaktyka nie ustawiona,
                                poziom.galaktyka++; // Zwiekszenie wartosci galaktyki
                                poziom.mapa=1; // Mapa ustawiona na 1
                            }
                            else poziom.przerywnik = true; // Jesli mapa nie wieksza niz 10 to przerywnik aktywowany
                        }
                    }

                    else if(poziom.przerywnik==true){ // Jesli przerywnik aktywny
                        if(poziom.klatka>2*FPS){ // Jesli klatka wieksza niz podwojona wartosc fpsow (czyli 2 sekundy)
                                poziom.przerywnik=false; // Przerywnik skonczony
                                poziom.koniecPoziomu=true; // Koniec poziomu aktywny
                                poziom.set=false; // Poziom nie ustawiony
                        }
                        else{ // Jesli klatka nie wieksza niz podwojona wartosc fpsow to rysuj tekst informujacy o aktualnej mapie i galaktyce
                        al_draw_textf(font , al_map_rgb(0 , 125 , 255) , szerokoscEkranu/2 , wysokoscEkranu/2-100 , ALLEGRO_ALIGN_CENTRE   , "Poziom: %d-%d ",poziom.galaktyka,poziom.mapa);
                        poziom.klatka++; // Klatka zwiekszona o 1
                        }
                    }

                    if(strzalyKosmitow.head != NULL){ // Jesli na mapie znajduja sie jakikolwiek strzal kosmitow
                        rysujStrzalyKosmitow(strzalyKosmitow,strzal2Bitmap); // Rysuj strzaly kosmitow
                        ruchStrzalowKosmitow(&strzalyKosmitow); // Rusz strzaly kosmitow
                        sprawdzKolizjeStatkuZeStrzalem(&strzalyKosmitow,&statek); // Sprawdz kolizje strzalow kosmitow ze statkiem
                    }

                    if(strzaly.head != NULL){ // Jesli strzely statku istnieją na mapie
                        rysujStrzaly(strzaly); // Rysuj strzaly statku
                        ruchStrzalow(&strzaly); // Rusz strzaly statku
                    }

                    if(strzaly.head != NULL && kosmici.head != NULL){ // Jesli istnieja strzely statku i kosmici
                        sprawdzKolizjeZKosmita(&strzaly,&kosmici,&statek); // Sprawdz czy strzel statku nie koliduje z kosmita
                    }
                    if(statek.zycia<0){ // Jesli pozostalo mniej zyc niz 0
                        poziom.koniecGry=true; // Koniec gry
                    }

                    rysujStatek(statek); // Rysuj statek

                    //HUD
                    al_draw_textf(font , al_map_rgb(255 , 250 , 255) , szerokoscEkranu, 10 , ALLEGRO_ALIGN_RIGHT  , "Kredyty: %d", statek.kredyty);
                    al_draw_textf(font , al_map_rgb(255 , 0 , 255) , 0, 10 , ALLEGRO_ALIGN_LEFT   , "Kosmici: %d", poziom.pozostaliKosmici);
                    al_draw_textf(font , al_map_rgb(255 , 0 , 0) , szerokoscEkranu/2+40, wysokoscEkranu-15 , ALLEGRO_ALIGN_LEFT   , "HP: %d", statek.hp);
                    al_draw_textf(font , al_map_rgb(255 , 0 , 0) , szerokoscEkranu/2-40, wysokoscEkranu-15 , ALLEGRO_ALIGN_RIGHT   , "Zycia: %d", statek.zycia);
                    if(poziom.mapa==10 && kosmici.head != NULL){
                        al_draw_textf(fontPlus , al_map_rgb(255 , 0 , 0) , szerokoscEkranu/2, 15 , ALLEGRO_ALIGN_CENTER   , "Boss: %d", kosmici.head->hp);
                    }
                    al_flip_display(); // Wyswietlanie narysowanych wczesniej bitmap/pikseli na ekranie

                    }
                }

        if(poziom.koniecPoziomu==true || poziom.koniecGry==true || exit==0){ // Jesli poziom lub gra sa zakonczone lub wybrano wyjscie z gry
                wyczyscPamiec(&kosmici,&strzalyKosmitow,&strzaly); // Wyczysc pamiec kosmitow, strzalow kosmitow i strzalow statku
                poziom.start=false; // Poziom nie zostal wystartowany
                if(exit==0 || poziom.koniecGry == true){ // Jesli wybrano wyjscie lub gra sie zakonczyla
                    wyczyscStatek(&statek); // Wyszysc pamiec statku
                }
        }

        while(sklep.set==true){ // Sklep
            al_wait_for_event(kolejka,&event); // Czekanie na zdarzenie

            if(event.type==ALLEGRO_EVENT_TIMER){ // Jesli zdarzenie to aktywowany timer
                al_draw_bitmap(sklep.tlo,0,0,0);  // Rysuj tlo sklepu
                al_draw_bitmap(statek.statekBitmap,szerokoscEkranu/2-statek.szerokosc/2,wysokoscEkranu/2-statek.wysokosc/2,0); // Rysuj bitmape statku na srodku ekranu

                //Jesli ktorys z dronw jest juz kupiony to go narysuj
                if(statek.lewyDron!=NULL)al_draw_bitmap(statek.lewyDron->dronBitmap,szerokoscEkranu/2-(statek.szerokosc/2)-statek.lewyDron->x,wysokoscEkranu/2-(statek.wysokosc/2)-statek.lewyDron->y,0);
                if(statek.prawyDron!=NULL)al_draw_bitmap(statek.prawyDron->dronBitmap,szerokoscEkranu/2-(statek.szerokosc/2)-statek.prawyDron->x,wysokoscEkranu/2-(statek.wysokosc/2)-statek.prawyDron->y,0);

                al_draw_text(fontPlus, al_map_rgb(255,255,255), szerokoscEkranu/2,wysokoscEkranu*0.1,ALLEGRO_ALIGN_CENTRE,"SKLEP"); // Rysuj napis SKLEP
                al_draw_textf(font, al_map_rgb(255,255,255), szerokoscEkranu/2,wysokoscEkranu*0.2,ALLEGRO_ALIGN_CENTRE,"Kredyty: %d",statek.kredyty); // Rysuj napis kredyty i wartosc kredytow zdobytych do tej pory

                al_draw_textf(font, al_map_rgb(255,255,255), 20,wysokoscEkranu*0.9,ALLEGRO_ALIGN_LEFT,"Zycia: %d",statek.zycia); // Rysuj napis Zycia i wartosc pozostalych zyc
                al_draw_textf(font, al_map_rgb(255,255,255), szerokoscEkranu/2,wysokoscEkranu*0.9,ALLEGRO_ALIGN_CENTRE,"Max HP: %d",statek.maxHP); // Rysuj napis Max Hp i aktualne maksymalne zycie statku
                al_draw_textf(font, al_map_rgb(255,255,255), szerokoscEkranu-20,wysokoscEkranu*0.9,ALLEGRO_ALIGN_RIGHT,"Rakiety: %d",statek.rakiety); // Rysuj napis Rakiety i ich aktualny stan
                al_draw_textf(font , al_map_rgb(255 , 0 , 255) , szerokoscEkranu/2,wysokoscEkranu*0.8 , ALLEGRO_ALIGN_CENTRE   , "Aby przejsc dalej wcisnij dowolny przycisk klawiatury");

                for(int i=0;i<75;i++){ // Rysowanie linii poprowadzonych ze statku do odpowiednich ikon przedmiotow w sklepie
                    al_draw_pixel(szerokoscEkranu/2-25-i,wysokoscEkranu/2-i/1.3,al_map_rgb(255 , 255 , 255));
                    al_draw_pixel(szerokoscEkranu/2+25+i,wysokoscEkranu/2-i/1.3,al_map_rgb(255 , 255 , 255));
                    al_draw_pixel(szerokoscEkranu/2,wysokoscEkranu/2-40-i,al_map_rgb(255 , 255 , 255));
                    al_draw_pixel(szerokoscEkranu/2+statek.szerokosc/1.59,wysokoscEkranu/2+i,al_map_rgb(255 , 255 , 255));
                    al_draw_pixel(szerokoscEkranu/2-statek.szerokosc/1.59,wysokoscEkranu/2+i,al_map_rgb(255 , 255 , 255));
                    al_draw_pixel(szerokoscEkranu/2,wysokoscEkranu/2+40+i,al_map_rgb(255 , 255 , 255));
                }

                for(int j=0;j<6;j++){ // Rysowanie ikon przedmiotow
                            al_draw_bitmap(sklep.przedmiot[j]->bitmapa,sklep.przedmiot[j]->x,sklep.przedmiot[j]->y,0);
                            if(sklep.przedmiot[j]->kursor==true){ // Jesli nad przedmiotem zostal ustawiony kursor
                                rysujInfo(sklep.przedmiot[j],font2); // To narysuj informacje o przedmiocie po lewej stronie ekranu
                            }
                }

                if(sklep.zaMalo){ // Jesli wartosc logiczna zaMalo w strukturze sklep posiada aktualnie wartosc true
                    al_draw_textf(font, al_map_rgb(255,0,0), szerokoscEkranu/2,wysokoscEkranu*0.23,ALLEGRO_ALIGN_CENTRE,"Za malo kretydow!"); // to wyswietl napis Za malo kredytow
                }
                al_flip_display(); // Wyswietl narysowane elementy na ekranie
            }

            else if  (event.type == ALLEGRO_EVENT_MOUSE_AXES) { // Jesli typ zdarzenia to ruch myszki
                    myszX=event.mouse.x; // Ustaw wartosci myszki odpowiadajace aktualnej pozycji kursora
                    myszY=event.mouse.y;
                    sprawdzSklep(myszX,myszY,&sklep); // Sprawdz gdzie jest kursor, jesli nad jakas ikona przedmiotu to ustaw wartosc logiczna 'kursor' tego przedmiotu na true
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){ // Jesli zostal wcisniety klawisz myszy
                    myszX=event.mouse.x; // Ustaw wartosci myszki odpowiadajace aktualnej pozycji kursora
                    myszY=event.mouse.y;
                    sklep.zaMalo=false; // Ustaw wartosc logiczna zaMalo na false
                    if(kupPrzedmiot(myszX,myszY,&sklep,&statek,strzalBitmap,dronBitmap)==1)sklep.zaMalo=true; // Jesli funkcja kupPrzedmiot zwroci wartosc 1 to zostanie ustawiona wartosc zaMalo na true co pozniej spowoduje wyswietlenie informacji o braku srodkow
                    else ustawSklep(&sklep,&statek); // Jesli zwroci co innego to uaktualnij wartosci przedmiotow w sklepie i zapisz nowe przedmioty do statku
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ // Jesli zostal wcisniety jakis klawisz na klawiaturze
                switch(event.keyboard.keycode){ // Sprawdz jaki to klawisz
                    case ALLEGRO_KEY_ESCAPE: // Jesli ESC
                        wyczyscStatek(&statek); // Wyszysc pamiec statku
                        menu.set=true; // Wroc do menu
                        sklep.set=false; // Sklep nie zostal ustawiony
                        poziom.koniecGry=true; // Koniec gry
                        poziom.koniecPoziomu=true; // Koniec poziomu
                        poziom.set=false; // Poziom nie zostal ustawiony
                        al_flush_event_queue(kolejka); // Wyszysc kolejke zdarzen
                     break;

                    default: // W przypadku innego klawisza
                        sklep.set=false; // Opusc sklep
                        menu.set=false; // Nie wchodz do menu
                        poziom.start=true; // Wystartuj poziom
                        poziom.set=false; // Poziom nie zostal ustawiony
                        poziom.przerywnik=true; // Przerywnik aktywowany
                        al_flush_event_queue(kolejka); // Wyczysc kolejke zdarzen
                    break;
                }
            }
        }

        while(poziom.koniecGry==true && gra.set==true){ // Okno konca gry
            al_clear_to_color(al_map_rgb(0, 0, 0)); // Rysuj danym kolorem
            al_draw_textf(font , al_map_rgb(255 , 0 , 255) , szerokoscEkranu/2 , wysokoscEkranu/2 , ALLEGRO_ALIGN_CENTRE   , "Koniec gry"); // Wyswietl napis
            al_draw_textf(font , al_map_rgb(255 , 0 , 255) , szerokoscEkranu/2 , wysokoscEkranu/2+50 , ALLEGRO_ALIGN_CENTRE   , "Udalo Ci sie osiagnac mape %d-%d i uzbierac %d kredytow",poziom.galaktyka,poziom.mapa,statek.kredyty);// Wyswietl napis
            al_draw_textf(font , al_map_rgb(255 , 0 , 255) , szerokoscEkranu/2 , wysokoscEkranu/2+150 , ALLEGRO_ALIGN_CENTRE   , "Aby przejsc dalej wcisnij dowolny przycisk");// Wyswietl napis

            al_flip_display(); // Wyswietl narysowane elementy
            al_wait_for_event(kolejka,&event); // Czekaj na zdarzenie
             if(event.type == ALLEGRO_EVENT_KEY_DOWN){ // Jesli zdarzenie to wcisniecie klawisza klawiatury
                    zapiszWynik(statek,poziom); // Zapisz wynik
                    wyniki.wczytano =false;
                    poziom.koniecPoziomu=false; // Ustaw wartosc koncaPoziomu na false
                    poziom.koniecGry=false; // Ustaw wartosc koncaGry na false
                    poziom.set=false; // Poziom nie zostal ustawiony
                    poziom.start=false; // Poziom nie wystartowal
                    galaktyka.set=false; // Galaktyka nie zostala ustawiona
                    gra.set=false; // Gra nie zostala ustawiona/mozna wlaczyc nowa gre
                }
            al_flush_event_queue(kolejka); // Wyczysc kolejke
        }

        while(wyniki.set==true){ // Wyniki

            if(wyniki.wczytano==false)wczytajWyniki(&wyniki); // Jesli nie wczytano jeszcze wynikow to wczytaj wyniki
            al_wait_for_event(kolejka,&event); // Poczekaj na zdarzenie
            if(event.type == ALLEGRO_EVENT_KEY_DOWN){ // Jesli zostal wcisniety klaiwsz
                wyniki.set=false; // Wyjdz z okna wynikow
                menu.set=true; // Wejdz do menu
            }
            else if(event.type == ALLEGRO_EVENT_TIMER && wyniki.wczytano == true){ // Jesli zdarzenie zostalo wywolane timerem i wyniki zostaly juz wczytane
                al_clear_to_color(al_map_rgb(0, 0, 0)); // Rysuj ekran w kolorze
                al_draw_textf(fontPlus , al_map_rgb(200 , 200 , 200) , szerokoscEkranu/2 , 15 , ALLEGRO_ALIGN_CENTRE   , "NAJLEPSZE WYNIKI");// Wyswietl napis
                wyswietlWyniki(wyniki); // Rysuj wyniki
                al_flip_display(); // Wyswietl narysowane elementy
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){ // Jesli event to ruch muszka (i kólkiem myszki)
                if(event.mouse.z<=0){ // Jesli to kołko myszki i ma wartosc mniejsza niz 0
                wyniki.scroll = event.mouse.z*(-1); // Ustaw wartosc scroll'a w strukturze wyniki na odpowiednia wartosc w zaleznosci od kierunku poruszenia kolkiem myszki
                }
            }
        }
    }
    // Usuniecie z pamieci bitmap
    al_destroy_bitmap(statek.statekBitmap);
    al_destroy_bitmap(strzalBitmap);
    al_destroy_bitmap(sklep.pole);
    // Usuniecie z pamieci okna ekranu
    al_destroy_display(display);
    // Usuniecie z pamieci czcionek
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_font(fontPlus);
    // Usuniecie z pamieci timera
    al_destroy_timer(timer);
    // Wylaczenie obslugi myszki i klawiatury
    al_uninstall_mouse();
    al_uninstall_keyboard();
    // Usuniecie kolejki
    al_destroy_event_queue(kolejka);
}

