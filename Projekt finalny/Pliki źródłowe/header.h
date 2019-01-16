#ifndef HEADER_H
#define HEADER_H

#include <iostream>
/**
Struktura zawiera cele poszczegolnych drog
*/
struct cele
{
	void *wierzcholek;
	double dystans;
	cele* nastepne;
};
/**
Struktura zawiera wierzcholki wraz z wskaznikami na cele i odleglosciami do nich
*/
struct wierzcholek
{
	std::string nazwa;
	wierzcholek *kolejny_wierzch;
	cele *lista;
	double odleglosc;
	wierzcholek *poprzedni_wierzch;
};
/**
Struktura wykorzystana do stworzenia kolejki priorytetowej
*/
struct kolejka
{
	wierzcholek *pWiersz;
	kolejka *pNext;
};

/**
Funkcja wczytuje plik z drogrami
@param nazwa_pliku plik z drogami
@param plik plik z trasami do wyznaczenia
@param wynik plik z wynikami
*/
void wczytanie(std::string nazwa_pliku, std::string plik, std::string wynik);
/**
Funkcja dodaje wierzcholek do listy
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param nazwa_miasta nazwa miasta z ktorego wyjezdzamy
@param nazwa_celu nazwa miasta do ktorego mozna jechac
*/
void dodajWierzcholek(wierzcholek*& pHead, std::string nazwa_miasta, std::string nazwa_celu, double dystans);
/**
Funkcja dodaje cel dla wierzcholka
@param w1 wskaznik na wierzcholek do ktorego dodajemy cel
@param w2 wskaznik na cel ktory dodajemy do wierzcholka
@param odleglosc dystans z wierzcholka do celu
*/
void dodajCel(wierzcholek *& w1, wierzcholek *& w2, double odleglosc);
/**
Funkcja sprawdza czy dany wierzcholek jest juz w liscie
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param szukane_miasto miasto, ktorego szukamy w liscie
@return zwraca wskaznik na znalezione miasto, jezeli nie znajdzie tego miasta- zwraca nullptr
*/
wierzcholek* szukaj(wierzcholek*& pHead, std::string szukane_miasto);
/**
Implementacja algorytmu dijkstry
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param m1 nazwa miasta z ktorego wyjezdzamy
@param m2 nazwa miasta do ktorego szukamy drogi
*/
void dijkstra(wierzcholek* pHead, std::string m1, std::string m2);
/**
Funkcja usuwa cele
@param pHead wskaznik na pierwszy element listy celow
*/
void usuwanieCelu(cele* pHead);
/**
Funkcja usuwa wierzcholki
@param pHead wskaznik na pierwszy element listy wierzcholkow
*/
void usuwanieWierzcholka(wierzcholek *& pHead);
/**
Funkcja tworzy kolejke priorytetowa
@param W miasto z ktorego szukamy drogi
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param pWiersz wskaznik, za pomoca ktorego tworzymy kolejke priorytetowa
*/
void stworz_kolejke(std::string W, wierzcholek * pHead, kolejka *& pWiersz);
/**
Funkcja wczytuje plik szukanych tras oraz przekazuje wyniki do odpowiedniego pliku
@param W plik szukanych tras
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param wynik nazwa pliku do ktorego wypisujemy wyniki
*/
void wczytanieWynikow(std::string plik, wierzcholek *& pHead, std::string wynik);
/**
Funkcja wypisuje poszczegolne odcinki tras
@param wyp wskaznik pomocniczy sluzacy do wypisywania poszczegolnych odcinkow tras
@param W miasto poczatkowe danego odcinka
@param W2 miasto docelowe danego odcinka
@param pHead wskaznik na pierwszy element listy wierzcholkow
@param wypisz strumien sluzacy do wypisania wynikow
@param szerokosc argument wykorzystany do sformatowania szerokosci wypisania poszczegolnych odcinkow
*/
void wypisywanie(wierzcholek *wyp, std::string W, std::string W2, wierzcholek* pHead, std::ofstream & wypisz, int szerokosc);
/**
Funkcja sortuje kolejke priorytetowa po wykonaniu obiegu algorytmu dijkstry i usunieciu jednego elementu tej kolejki
@param pHead wskaznik na pierwszy element kolejki priorytetowej
*/
void sortuj(kolejka * & pHead);

#endif
