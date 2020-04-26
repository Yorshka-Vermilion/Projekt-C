#include "biblioteki.h"

void zapiszWynik(struct ship statek,struct level poziom){ // Zapisywanie wyniku do pliku
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); // Stworzenie struktury czasu
printf("CSADAS");
    FILE *plik = fopen("wyniki.txt","a+"); // Otworzenie pliku, ustawienie kursora na koncu, jesli plik nie istnieje to go tworzy
    if(plik){ // Jesli zostal otwarty
        fprintf(plik,"%d:%d:%d:%d:%d:%d:%d:%d\n",poziom.galaktyka,poziom.mapa,statek.kredyty,tm.tm_hour,tm.tm_min,tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900); // Zapisanie odpowiednich wartosci do pliku
    fclose(plik);
    return 0;
    }
}


void wczytajWyniki(struct score *wyniki){ // Wczytywanie wynikow z pliku do tablicy dwu wymiarowej
    for(int i=0;i<100;i++){ // Czyszczenie tablicy
        for(int j=0;j<8;j++){
            wyniki->wynik[i][j]=0;
        }
    }
    int i =0;
    FILE *plik = fopen("wyniki.txt","r");
    int galaktyka,mapa,wynik,godzina,minuta,dzien,miesiac,rok;
    while(EOF != fscanf(plik, "%d:%d:%d:%d:%d:%d:%d:%d\n",&galaktyka,&mapa,&wynik,&godzina,&minuta,&dzien,&miesiac,&rok)){ // Wczytywanie kolejnych linijek z pliku z wynikami do tablicy z wynikami
        wyniki->wynik[i][0]=galaktyka;
        wyniki->wynik[i][1]=mapa;
        wyniki->wynik[i][2]=wynik;
        wyniki->wynik[i][3]=godzina;
        wyniki->wynik[i][4]=minuta;
        wyniki->wynik[i][5]=dzien;
        wyniki->wynik[i][6]=miesiac;
        wyniki->wynik[i][7]=rok;
        i++;
    }
    posortujWyniki(wyniki); // Wywolanie funkcji sortujacej

    wyniki->wczytano = true; // Ustawienie wartosci wczytania wynikow na true, co zapobiega jej kolejnym wywolanią w programie
    fclose(plik);
}

void posortujWyniki(struct score *wyniki){ // Sortowanie 3 stopniowe, porownanie kolejno galaktyki,mapy i wyniku.
int i=0;
int j=0;
int tmp[1][8];
 while(wyniki->wynik[i][0]!=0){ // Dopóki w tablicy jest jakis wynik ktory nie jest zerem
        j=i+1;
        while(wyniki->wynik[j][0]!=0){ // Dopóki w tablicy jest jakis wynik który nie jest zerem
            if(wyniki->wynik[j][0]>=wyniki->wynik[i][0]){ // porownanie galaktyki
                if(wyniki->wynik[j][0]==wyniki->wynik[i][0] && wyniki->wynik[j][1]<=wyniki->wynik[i][1]){ // porownanie mapy
                    if(wyniki->wynik[j][1]==wyniki->wynik[i][1] && wyniki->wynik[j][2]>wyniki->wynik[i][2]){ // porownanie wyniku
                        for(int x=0;x<8;x++){ // Zamiana wartosci tablicy o podanych indeksach
                            tmp[0][x]=wyniki->wynik[i][x];
                            wyniki->wynik[i][x]=wyniki->wynik[j][x];
                            wyniki->wynik[j][x]=tmp[0][x];
                        }
                    }
                }
                else {
                for(int x=0;x<8;x++){ // Zamiana wartosci tablicy o podanych indeksach
                    tmp[0][x]=wyniki->wynik[i][x];
                    wyniki->wynik[i][x]=wyniki->wynik[j][x];
                    wyniki->wynik[j][x]=tmp[0][x];
                }
                }
            }
        j++;
        }
    i++;
    }
}

void wyswietlWyniki(struct score wyniki){ // Wyswietlanie wynikow, funkcja przyjmuje jako argument strukture wyniki
    int i=wyniki.scroll; // Do zmiennej i jest przypisana wartosc ze struktury wyniki.scroll
    int x=szerokoscEkranu/2; // Wysrodkowanie takstu
    int y=75; // Zaczecie pod napiszem NAJLEPSZE WYNIKI
    while(wyniki.wynik[i][0]!=0 && wyniki.wynik[i][0]!=NULL && y<wysokoscEkranu){ // Dopóki wyniki są rozne od zera, i istnieją i nie przekroczyly wysokosci ekranu to rysuj je na podanej pozycji w podanym formacie
        al_draw_textf(wyniki.czcionka , al_map_rgb(255 , 255 , 255) , x , y , ALLEGRO_ALIGN_CENTRE   , "%d. %d-%d  :  %d  :  %d:%d  :  %d-%d-%d",i+1,wyniki.wynik[i][0],wyniki.wynik[i][1],wyniki.wynik[i][2],wyniki.wynik[i][3],wyniki.wynik[i][4],wyniki.wynik[i][5],wyniki.wynik[i][6],wyniki.wynik[i][7]);
        i++;
        y+=wyniki.rozmiarCzcionki*2; // Dodajemy podwojoną wartosc rozmiaru czcionki w celu zrobienia odstepu miedzy kolejnymi wynikami
    }
}
