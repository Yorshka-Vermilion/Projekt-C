#ifndef BIBLIOTEKI_H_INCLUDED
#define BIBLIOTEKI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define wysokoscEkranu 640
#define szerokoscEkranu 640
#define FPS 60

#define szerokoscStrzalu 3
#define wysokoscStrzalu 7

//! Struktura przechowuje infomacje dotyczace rozpoczecia nowej gry.
struct game{
    //! Wartość logiczna używana do zapisania statusu rozpoczetej gry.
    bool set;
}gra;

//! Struktura przechowuje infomacje dotyczace menu głównego.
struct menu{
    //! Wartość logiczna używana do zapisania statusu menu (true dla aktywnego, false dla nieaktywnego).
    bool set;
    //! Tablica przechowuje wskaźniki na strukture opcji.
    struct options *opcje[3];
    //! Zmienna przechowuje aktualny wybór opcji przez użytkownika.
    int wybor;
    //! Wskaźnik na bitmape grafiki menu.
    ALLEGRO_BITMAP *bitmap;
    //! Wskaźnik na czcionke menu.
    ALLEGRO_FONT *czcionka;
}menu;

//! Struktura przechowuje informacje dotyczące opcji wyświetlanych w menu głownym.
struct options{
    //! Zmienna przechowuje napis jaki ma się wyświetlać przy konkretnej opcji.
    char *tresc;
    //! Przechowuje infomacje o położeniu rogu napisu na osi x
    int x;
    //! Przechowuje informacje o położeniu rogu napisu na osi y
    int y;
};

//! Struktura przechowuje informacje dotyczące sklepu
struct shop{
    //! Wartość logiczna określa czy sklep ma zostać wyświetlony
    bool set;
    //! Tablica przechowuje wskaźniki na przedmioty w sklepie
    struct item *przedmiot[6];
    //! Wskaźnik na bitmape domyślnego pola sklepu
    ALLEGRO_BITMAP *pole;
    //! Zmienna określa szerokość domyślnego pola sklepu
    int szerokoscPola;
    //! Zmienna określa wysokość domyślnego pola sklepu
    int wysokoscPola;
    //! Wartość logiczna określa czy graczu brakuje kredytów na zakup przedmiotu
    bool zaMalo;
    //! Wskaźnik na bitmape tła sklepu
    ALLEGRO_BITMAP *tlo;
}sklep;
//! Struktura przechowuje informacje o poszczegolnych przedmiotach dostepnych w sklepie
struct item{
    //! Zmienna określa położenie na osi x bitmapy danego przedmiotu
    int x;
    //! Zmienna określa położenie na osi y bitmapy dnaego przedmiotu
    int y;
    //! Zmienna przechowuje nazwę przedmiotu
    char *nazwa;
    //! Zmienna przechowuje początkowy koszt przedmiotu
    int kosztPocz;
    //! Zmienna przechowuje aktualny koszt przedmiotu
    int koszt;
    //! Zmienna przechowuje aktualne obrażenia przedmiotu
    int dmg;
    //! Zmienna przechowuje aktualny poziom przedmiotu
    int poziom;
    //! Wartość logiczna określa czy gracz posiada już przedmiot
    bool posiadany;
    //! Wartość logiczna określa czy przedmiot jest aktualnie dostępny w sklepie
    bool dostepny;
    //! Wartość logiczna określa czy kursor myszy znajduję się aktualnie nad grafiką przedmiotu
    bool kursor;
    //! Wartość logiczna określa czy przedmiot jest przedmiotem specjalnym
    bool spec;
    //! Zmienna przechowuje wskaźnik na bitmape przedmiotu
    ALLEGRO_BITMAP *bitmapa;
};

//! Struktura przechowuje informacje o domyślnych specjalnych ustawieniach statku gracza
struct settings{
    //! Zmienna przechowuje informację o prędkości tracenia statusu niewrażliwości przez statek gracza
    double spadekNiewrazliwosci;
}ustawienia;

//! Struktura przechowuje informacje o ustawieniach każdego kosmity
struct settingsAlien{
    //! Zmienna przechowuje domyślne HP przeciwnika.
    int hp;
    //! Zmienna przechowuje domyślne obrażenia przeciwnika.
    int dmg;
    //! Zmienna przechowuje domyślną wartośc przeciwnika
    int wartosc;
    //! Zmienna przechowuje domyślną prędkość poruszania sie strzału kosmity
    int szybkoscStrzalu;
    //! Zmienna przechowuje domyślną częstotliwość oddawania strzałów przeciwnika
    int czestotliwoscStrzalow;
    //! Zmienna przechowuje domyślny numer klatki rozpoczynającej animację wybuchu przeciwnika
    int klatka;
    //! Zmienna przechowuje domyślną wartość doatkowej szansy na strzał kolejnego kosmity jeśli wcześniejszy został już zniszony
    /*!
    W końcowej fazie mapy przeciwnicy strzelali bardzo powoli, dzięki wprowadzeniu tej wartości, wiecej przeciwników oddaje strzał jeśli jest ich mało
    */
    int dodatkowaSzansa;
    //! Mnożnik ustawień kosmitów
    /*!
    Różne typy kosmitów mają rózne nagrody/HP/obrażenia/szybkość strzalu
    Aby uniknąć niepotrzebnych skomplkowań został wprowadzony mnożnik, który zwyczajnie przemnaża statystyki niektórych typów kosmitóœ
    */
    int mnoznik;
}ustawieniaKosmitow;

//! Struktura przechowuje informację o galaktyce
struct galaxy{
    //! Wartość logiczna określa czy galaktykę należy ustawić, czyli zeskalować niektóre statystyki przeciwników
    bool set;
}galaktyka;

//! Struktura przechowuje informację o poziomie
struct level{
    //! Wartość logiczna określa czy poziom już wystartował
    bool start;
    //! Wartość logiczna określa czy poziom zakończył się zwycięstwem gracza
    bool koniecPoziomu;
    //! Wartość logiczna określa czy gra została zakończona
    bool koniecGry;
    //! Wartość logiczna określa czy należy ustawić poziom, rozstawić i zeskalować przeciwników
    bool set;
    //! Wartość logiczna określa czy zostanie wyświetlony przerywnik między poziomami
    bool przerywnik;
    //! Wartość logiczna określa czy przeciwnicy zostali już zespawnowani
    bool spawned;
    //! Zmienna przechowuje numer aktualnej mapy czyli poziomu
    int mapa;
    //! Zmienna przechowuje numer aktualnej galaktyki
    int galaktyka;
    //! Zmienna określa ile rzędów przeciwników występuje na mapie
    int liczbaRzedow;
    //! Zmienna określa ile wierszy przeciwników występuje na mapie
    int liczbaWierszy;
    //! Zmienna przechowuje informację ilu kosmitów zostało na mapie
    int pozostaliKosmici;
    //! Zmienna przechowuje numer klatki animacji spawnowania przeciwników
    int klatka;
    ALLEGRO_BITMAP *bitmapa[10];
}poziom;

//! Struktura zawiera informację o statku oraz wskaźniki na jego uzbrojenie
struct ship{ // Struktura ship przechowuje informacje o statku
    //! Zmienna określa połozenie statku na osi x
    int x;
    //! Zmienna określa położenie statku na osi y
    int y;
    //! Zmienna określa aktualne HP staku
    int hp;
    //! Zmienna określa maksymalne HP statku
    int maxHP;
    //! Zmienna określa szerokość statku
    int szerokosc;
    //! Zmienna określa wysokość statku
    int wysokosc;
    //! Zmienna określa obrażenia początkowe statku
    int dmg;
    //! Zmienna określa prędkość ruchu statku w kierunku kursora
    int movement;
    //! Zmienna określa ilośc żyć gracza
    int zycia;
    //! Zmienna określa ilość rakiet gracza
    int rakiety;
    //! Zmienna określa pozostały czas efektu niewrażliwości
    double niewrazliwosc;
    //! Zmienna określa ilośc posiadanych kredytów
    int kredyty;
    //! Wskaźnik na srodkowe działo statku
    struct cannon *srodkoweDzialo;
    //! Wskaźnik na lewe działo statku
    struct cannon *leweDzialo;
    //! Wskaźnik na prawe działo statku
    struct cannon *praweDzialo;
    //! Wskaźnik na lewego drona
    struct drone *lewyDron;
    //! Wskaźnik na prawego drona
    struct drone *prawyDron;
    //! Wskaźnik na bitmape statku
    ALLEGRO_BITMAP *statekBitmap;
    //! Wskaźnik na dźwięk wystrzału statku
    ALLEGRO_SAMPLE *strzalDzwiek;
}statek;

//! Struktura zawiera informację o pociskach gracza
struct shipShot{
    //! Zmienna określa położenie pocisku na osi x
    double x;
    //! Zmienna określa położenie pocisku na osi y
    double y;
    //! Zmienna określa obrażenia pocisku
    int dmg;
    //! Wskaźnik wskasuje na następny element listy strzałów
    struct shipShot *next;
    //! Wskaźnik na bitmape strzału
    ALLEGRO_BITMAP *strzalBitmap;
};

//! Struktura zawiera informację o dziale
struct cannon{
    //! Zmienna określa w jakim położeniu na osi x od środka statku znajduje się działo
    int x;
    //! Zmienna określa w jakim położeniu na osi y od środka statku znajduje się działo
    int y;
    //! Zmienna określa obrażenia działa
    int dmg;
    //! Zmienna określa szybkość poruszania się wystrzelonego pocisku
    int szybkoscPosisku;
    //! Zmienna określa poziom działa
    int poziom;
    //! Wskaźnik na bitmapę pocisku
    ALLEGRO_BITMAP *strzalBitmap;
};

//! Struktura zawiera informację o dronie
struct drone{
    //! Zmienna przechowuje informavję o położeniu drona na osi x względem lewego rogu statku
    int x;
    //! Zmienna przechowuje informację o położeniu drona na osi y względem lewego rogu statku
    int y;
    //! Zmienna określa szerokość drona
    int szerokosc;
    //! Zmienna określa wysokość drona
    int wysokosc;
    //! Zmienna określa HP drona
    int hp;
    //! Zmienna określa obrażniea drona
    int dmg;
    //! Zmienna określa poziom drona
    int poziom;
    //! Wskaźnik na bitmape drona
    ALLEGRO_BITMAP *dronBitmap;
    //! Wskaźnik na bitmapę pocisku
    ALLEGRO_BITMAP *strzalBitmap;
};

//! Struktur przechowuje wskaźniki listy strzałów statku
struct pointersShipShot{
    //! Wskaźniki na początek i koniec listy a także pomocniczy wskaźnik
    struct shipShot *head, *tail, *q;
} strzaly;

//! Struktura przechowuje informację o kosmicie
struct alien{
    //! Zmienna przechowuje informację o położeniu kosmity na osi x
    int x;
    //! Zmienna przechowuje informację o położeniu kosmity na osi y
    int y;
    //! Zmienna przechowuje informację o HP kosmity
    int hp;
    //! Zmienna określa obrażenia pocisku kosmity
    int dmg;
    //! Zmienna określa ilośc kredytów jaką gracz otrzymuje za pokonanie kosmity
    int wartosc;
    //! Zmienna przechowuje szybkość poruszania się pocisku kosmity
    int szybkoscStrzalu;
    //! Zmienna przechowuje aktualną klatke wybuchu kosmity
    int klatka;
    //! Zmienna przechowuje klatke spawnu kosmity
    int spawn;
    //! Zmienna przechowuje wartość częstotliwośći oddawania strzałów przez przeciwnika
    int czestotliwoscStrzalow;
    //! Wskaźnik na bitmape strzału
    ALLEGRO_BITMAP *strzalBitmap;
    //! Wskaźnik na domyślną bitmape kosmity
    ALLEGRO_BITMAP *kosmitaBitmapDef;
    //! Wskaznik na aktualna bitmape kosmity
    ALLEGRO_BITMAP *kosmitaBitmap;
    //! Tablica wskaźników na bitmapy eksplozji kosmity
    ALLEGRO_BITMAP *eksplozja[11];
    //! Wskaźnik na dzwiek eksplozji
    ALLEGRO_SAMPLE *dzwiekEksplozji;
    //! Zmienna przechowuje szerokość kosmity
    int szerokoscKosmity;
    //! Zmienne przechowuje wysokość kosmity
    int wysokoscKosmity;
    //! Wskaźnik na następnego kosmite z listy
    struct alien *next;
};

//! Struktura przechowuje wskaźniki listy kosmitów
struct pointersAlien{
    //! Wskaźniki na początek i konieć listy kosmitów a także wskaźnik pomocniczy
    struct alien *head, *tail, *q;
}kosmici;

//! Struktura przechowuje informację o pocisku kosmity
struct alienShot{
    //! Zmienna przechowuje położenie na osi x pocisku
    double x;
    //! Zmienna przechowuje położenie na osi y pocisku
    double y;
    //! Zmienna przechowuje wartość obrażeń pocisku
    int dmg;
    //! Zmienna przechowuje prędkość poruszania się pocisku
    int szybkosc;
    //! Wskaźnik na bitmape strzału
    ALLEGRO_BITMAP *strzalBitmap;
    //! Wskaźnik na następny element listy strzałów
    struct alienShot *next;
};

//! Struktura przechowuje wskaźniki listy strzałów
struct pointersAlienShot{
    //! Wskaźniki na początek i koniec listy strzałów, oraz wskaźnik pomocniczy
    struct alienShot *head, *tail, *q;
} strzalyKosmitow;

//! Struktura przechowuje informacje o wynikach
struct score{
    //! Wartość logiczna określa czy okno wyników powinno być aktualnie wyświetlane
    bool set;
    //! Zmienna określa początkową pozycje wyświetlaną w tablicy wyników
    /*! Manipulacja za pomocą kółka myszy */
    int scroll;
    //! Tablica przechowuje wyniki wczytane z pliku
    int wynik[100][8];
    //! Wartość logiczna określa czy wyniki zostały już wczytane i posorotowane
    bool wczytano;
    //! Zmienna określa rozmiar czcionki którą pisane są wyniki na ekranie
    int rozmiarCzcionki;
    //! Wskaźnik na czcionke.
    ALLEGRO_FONT *czcionka;
}wyniki;

//! Funkcja odpowiada za poruszanie sie statku w kierunku kursora
/*!
    \param statek struktura statku
    \param myszX pozyscja kursora na osi x
    \param myszY pozycja kursora na osi y
*/
extern void ruchStatku(struct ship *statek,int myszX, int myszY);

//! Funkcja odpowiada za rysowanie statku
/*!
    \param statek struktura statku
*/
extern void rysujStatek (struct ship statek);

//! Funkcja sprawdza dokładną kolizje pocisku kosmity ze statkiem
/*!
    \param statek Struktura statku
    \param xOBJ pozycja x objektu
    \param yOBJ pozycja y objektu
    \param szerOBJ szerokosc objektu
    \param wysOBJ wysokosc obiektu
    \return Jeśli znaleziono kolizje zwraca false, jeśli nie true
*/
extern bool dokladnaKolizjaStatku(struct ship *statek,int xOBJ, int yOBJ, int szerOBJ, int wysOBJ);

//! Funkcja sprawdza kolizje statku i kosmity
/*!
    \param kosmici Struktura wskaźników listy kosmitów
    \param statek Struktura statku
*/
extern void sprawdzKolizjeStatkuZKosmita(struct pointersAlien *kosmici,struct ship *statek);

//! Funkcja zmniejsza pozostały czas niewrażliwości statku, a także powoduje efekt "migania" statku przy utracie życia
/*!
    \param statek Struktura statku
    \param ustawienia Struktura z ustawieniami specjalnymi statku
*/
extern void dostosujNiewrazliwosc(struct ship *statek,struct settings ustawienia);

//! Funkcja sprawdza ogólną kolizje statku ze strzalem
/*!
    \param strzaly Struktura wskaźników na liste strzałów kosmitóœ
    \param statek Struktura statku
    \sa SpdokladnaKolizjaStatku()
*/
extern void sprawdzKolizjeStatkuZeStrzalem(struct pointersAlienShot *strzaly, struct ship *statek);

//! Funkcja odpowiada za wystrzelenie ze wszystkich zamontowanych dział statku
/*!
    \param strzaly Struktura wskaźników na liste strzałow statku
    \param statek Struktura statku
    \sa zakolejkujStrzaly()
    \sa zakolejkujStrzalyDrona()
*/
extern void wystrzelZDzial(struct pointersShipShot *strzaly,struct ship *statek);

//! Funkcja odpowiada za rysowanie strzałów statku
/*!
    \param strzaly Struktra wskaźników na liste strzałów statku
*/
extern void rysujStrzaly(struct pointersShipShot strzaly);

//! Funkcja odpowiada za ruch strzałów statku
/*!
    \param strzaly Struktra wskaźników na liste strzałów statku
    \sa usunStrzaly()
*/
extern void ruchStrzalow(struct pointersShipShot *strzaly);

//! Funkcja odpowiada za usnunięcie strzałów które wypadły za mape z listy strzałów statku
/*!
    \param strzaly Struktra wskaźników na liste strzałów statku
    \param strzal Struktura strzału który wypadł poza mape
*/
extern void usunStrzaly(struct pointersShipShot *strzaly, struct shipShot *strzal);

//! Funkcja odpowiada za dopisanie do listy strzałow nowego strzału
/*!
    \param strzaly Struktura wskaźników listy strzałów
    \param dzialo Struktura działa z którego padł strzał
    \param x pozycja nowego strzalu na osi x
    \param y pozycja nowego strzalu na osi y
*/
extern void zakolejkujStrzaly(struct pointersShipShot *strzaly, struct cannon *dzialo, int x, int y);

//! Funkcja odpowiada za dopisanie do listy strzałow nowego strzału drona
/*!
    \param strzaly Struktura wskaźników listy strzałów
    \param dron Struktura drona z którego padł strzał
*/
extern void zakolejkujStrzalyDrona(struct pointersShipShot *strzaly, struct drone *dron);

//! Funkcja tworzy nowe dzialo
/*!
    Używana głownie w sklepie.
    \param x Pozycja nowego działa w odległości x od srodka statku na osi x
    \param y Pozycja nowego działa w odległości y od srodka statku na osi y
    \param strzalBitmap Wskaznik na bitmape pocisku
    \return Zwraca wskaznik na nową strukture dziala
*/
extern struct cannon *stworzNoweDzialo(int x, int y,ALLEGRO_BITMAP **strzalBitmap);

//! Funkcja tworzy nowego drona
/*!
    Używana głownie w sklepie.
    \param x Pozycja nowego działa w odległości x od lewego rogu statku na osi x
    \param y Pozycja nowego działa w odległości y od lewego rogu statku na osi y
    \param strzalBitmap Wskaznik na bitmape pocisku
    \return Zwraca wskaznik na nową strukture drona
*/
extern struct drone *stworzNowegoDrona(int x, int y,ALLEGRO_BITMAP **dronBitmap,ALLEGRO_BITMAP **strzalBitmap);

//! Funkcja tworzy nowego kosmite, dopisuje go do listy kosmitow i ustawia mu przekazane wartości
/*!
    \param kosmici Struktura wskaźników listy kosmitow
    \param pozX Docelowa pozycja nowego kosmity na osi x
    \param pozY Docelowa pozycja nowego kosmity na osi Y
    \param ustawieniaKosmitow Struktura ustawien kosmitow
    \param grafikiKosmitow Bitmapy kosmitow
    \param grafikiStrzalow Bitmapy strzalow kosmitow
    \param animacjaEksplozji Bitmapy eksplozji
    \param rodzaj Wylosowany rodzaj kosmity, lub w przypadku 10 ustawiony
*/
extern void rozstawKosmite(struct pointersAlien *kosmici,int pozX, int pozY,struct settingsAlien ustawieniaKosmitow, ALLEGRO_BITMAP **grafikiKosmitow, ALLEGRO_BITMAP **grafikiStrzalow, ALLEGRO_BITMAP **animacjaEksplozji,int rodzaj);

//! Funkcja wywołuje funkcje tworzenia kosmity z odpowiednimi wartosciami pozycji i rodzaju
/*!
    \param kosmici Struktura wskaźników listy kosmitow
    \param poziom Struktura z informacjami o aktualnym poziomie
    \param pozX Docelowa pozycja nowego kosmity na osi x
    \param pozY Docelowa pozycja nowego kosmity na osi Y
    \param ustawieniaKosmitow Struktura ustawien kosmitow
    \param grafikiKosmitow Bitmapy kosmitow
    \param grafikiStrzalow Bitmapy strzalow kosmitow
    \param animacjaEksplozji Bitmapy eksplozji
    \sa rozstawKosmite()
*/
extern void rozstawKosmitow(struct pointersAlien *kosmici,struct settingsAlien ustawieniaKosmitow,struct level poziom, ALLEGRO_BITMAP **grafikiKosmitow, ALLEGRO_BITMAP **grafikiStrzalow, ALLEGRO_BITMAP **animacjaEksplozji);

//! Funkcja odpowiada za rysowaine kosmitow
/*!
    \param kosmici Struktra wskaźników na liste kosmitow
    \param poziom Struktura z infrmacjami o aktualnym poziomie
*/
extern void rysujKosmitow(struct pointersAlien kosmici,struct level *poziom);

//! Funkcja odpowiada za ruch kosmitow
/*!
    \param kosmici Struktra wskaźników na liste kosmitow
*/
extern void ruchKosmitow(struct pointersAlien *kosmici);

//! Funkcja sprawdza kolizje strzałów statku z kosmitami
/*!
    \param strzaly Struktura wskaźników na liste strzałów statku
    \param kosmici Struktura wskaźników na listę kosmitóœ
    \param statek Struktura statku
*/
extern void sprawdzKolizjeZKosmita(struct pointersShipShot *strzaly, struct pointersAlien *kosmici, struct ship *statek);

//! Funkcja odpowiada za dopisanie do listy strzałow kosmity nowego strzału kosmity
/*!
    \param strzaly Struktura wskaźników listy strzałów kosmitow
    \param kosmici Struktura kosmitow
    \param ustawieniaKosmitow Struktura z ustawieniami kosmitow
*/
extern void zakolejkujStrzalyKosmitow(struct pointersAlienShot *strzaly, struct pointersAlien kosmici, struct settingsAlien ustawieniaKosmitow);

//! Funkcja odpowiada za ruch strzałów kosmitow
/*!
    \param strzaly Struktra wskaźników na liste strzałów kosmitow
    \sa usunStrzalyKosmitow()
*/
extern void ruchStrzalowKosmitow(struct pointersAlienShot *strzaly);

//! Funkcja odpowiada za usnunięcie strzałów które wypadły za mape z listy strzałów kosmitow
/*!
    \param strzaly Struktra wskaźników na liste strzałów kosmitow
    \param strzal Struktura strzału który wypadł poza mape
*/
extern void usunStrzalyKosmitow(struct pointersAlienShot *strzaly, struct alienShot *strzal);

//! Funkcja odpowiada za rysowanie strzałów kosmitow
/*!
    \param strzaly Struktra wskaźników na liste strzałów kosmitow
*/
extern void rysujStrzalyKosmitow(struct pointersAlienShot strzaly,int *strzalyBitmap);

//! Funkcja usówa kosmitów z listy kosmitów
/*!
    \param kosmici Struktura kosmitow
*/
extern void usunKosmitow(struct pointersAlien *kosmici);

//! Funkcja zmienia aktualną klatke animacji spawnowania kosmity
/*!
    \param kosmici Struktura kosmitow
    \param spawnKosmity Wskaźnik na tablice z klatkami animacji spawnu
*/
extern void spawnKosmitow(struct pointersAlien kosmici,ALLEGRO_BITMAP **spawnKosmity);

//! Funkcja ładuje do tablicy klatki animacji spawnu kosmity
/*!
    \param spawnKosmity Wskaźnik na tablice z klatkami animacji spawnu
*/
extern void zaladujAnimacjeSpawnuKosmity(ALLEGRO_BITMAP **spawnKosmity);

//! Funkcja tworzy nowy przedmiot i zwraca wskaźnik na niego
/*!
    \param nazwa Ciąg znaków z nazwą przedmiotu
    \param x Pozycja x nowego przedmiotu w sklepie
    \param y Pozycja y nowego przedmiotu w sklepie
    \param koszt Koszt nowego przedmiotu
    \param dostepny Dostepnośc nowego przedmiotu, określa czy ma być dostępny w sklepie od razu
    \param spec Określa czy przedmiot jest przedmiotem specjalnym
    \param bitmapa Bitmapa przedmiotu która bedzie wyświetlana w sklepie
    \return Zwraca wskaźnik na nowy przedmiot
*/
extern struct item *stworzPrzedmiot(char *nazwa, int x, int y, int koszt, bool dostepny, bool spec, ALLEGRO_BITMAP *bitmapa);

//! Funkcja sprawdza czy kursor myszy znajduje się nad jakimś przedmiotem w sklepie
/*!
    Jesli kursor znajudje się nad bitmapą przedmiotu to ustawiana jest wartość logiczna kursor w strukturze przedmiotu
    \param x Pozycja myszy na osi x
    \param y Pozycja myszy na osi y
    \param sklep Struktura sklepu
*/
extern void sprawdzSklep(int x, int y, struct shop *sklep);

//! Funkcja pobiera informacje o przedmiotach zainstalowanych na statku i przekazuje je do sklepu
/*!
    \param sklep Struktura sklepu
    \param statek Struktura statku
*/
extern void ustawSklep(struct shop *sklep, struct ship *statek);

//! Funkcja rysuje informacje o przedmiocie po najechaniu na niego kursorem
/*!
    \param przedmiot Struktura przedmiotu nad którym jest aktualnie kursor
    \param font Czcionka którą pisane są informacje
*/
extern void rysujInfo(struct item *przedmiot,ALLEGRO_FONT *font);

//! Funkcja odpowiada za kupno przedmiotu i zainstalowanie go na statku
/*!
    \param x Pozycja kursora na osi x
    \param y Pozycja kursora na osi y
    \param sklep Struktura sklepu
    \param statek Struktura statku
    \param strzalBitmap Bitmapa strzału
    \param dronBitmap Bitmapa drona
    \return Zwraca wartosc 0 jeśl zakup sie powiódł, 1 jeśli gracz ma za mało kredytów na zakup danego przedmiotu
*/
extern int kupPrzedmiot(int x, int y,struct shop *sklep, struct ship *statek, ALLEGRO_BITMAP *strzalBitmap,ALLEGRO_BITMAP *dronBitmap);

//! Funkcja czyści pamięc statku
/*!
    \param statek Struktura statku
*/
extern void wyczyscStatek(struct ship *statek);

//! Funkcja czyści pamięc zajętą przez liste kosmitów, strzały kosmitów i strzały statku
/*!
    \param kosmici Struktura wskaźników na lise kosmitow
    \param strzalyKosmitow Struktura wskaźników na liste strzałów kosmitów
    \param strzaly Struktura wskaźników na liste strzałów statku
*/
extern void wyczyscPamiec(struct pointersAlien *kosmici, struct pointersAlienShot *strzalyKosmitow, struct pointersShipShot *strzaly);

//! Funkcja zapisuje wynik gracza do pliku
/*!
    \param statek Struktura statku
    \param poziom Struktura poziomu
*/
extern void zapiszWynik(struct ship statek,struct level poziom);

//! Funkcja wczytuje wyniki z pliku do tablicy i je sortuje
/*!
    \param wyniki Struktura wyników
*/
extern void wczytajWyniki(struct score *wyniki);

//! Funkcja wyświetla wyniki na ekranie
/*!
    \param wyniki Struktura wynikow
*/
extern void wyswietlWyniki(struct score wyniki);

//! Funkcja tworzy nową opcje w menu
/*!
    \param tresc Nazwa nowej opcji
    \param x Pozycja nowej opcji na oxi x
    \param y Pozycja nowej opcji na osi y
    \return Zwraca wskaźnik na nową opcje menu
*/
extern struct options *ustawOpcje(char *tresc, int x, int y);

//! Funkcja sprawdza jaka opcja została wybrana i wykonuje odpowiednie akcje w celu przejścia do kolejnych ekranów gry lub wyjścia z gry
/*!
    \param opcja Numer wybranej opcji
    \param exit Wskaźnik na zmienną exit odpowiedzialną za wykonywanie głównej pętli programu, ustawiona na 0 powoduje zakończenie programu
*/
extern void wyborOpcji(int opcja,int *exit);

//! Funkcja ładuje bitmapy map do tablicy w strukturze podanej w parametrze
/*!
    \param poziom Struktura poziomu
*/
extern void zaladujMapy(struct level *poziom);
#endif
