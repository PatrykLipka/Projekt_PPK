#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include "header.h"



void wczytanie(std::string nazwa_pliku, std::string plik, std::string wynik)
{
	std::ifstream wejscie(nazwa_pliku);
	std::string skad, dokad;
	double dystans;
	wierzcholek* pGlowa = nullptr;
	if (wejscie)
		while (wejscie >> skad >> dokad >> dystans)
		{
			dodajWierzcholek(pGlowa, skad, dokad, dystans);
		}
	wczytanieWynikow(plik, pGlowa, wynik);
	usuwanieWierzcholka(pGlowa);
}

void wczytanieWynikow(std::string plik, wierzcholek *& pHead, std::string wynik)
{
	double dist=0;
	std::ifstream wejscieW(plik);
	std::ofstream wyniki;
	wyniki.open("wyniki.txt", std::ofstream::out | std::ofstream::trunc);
	wyniki.close();
	wyniki.open("wyniki.txt", std::ofstream::app);
	std::string miasto1, miasto2;
	if (wejscieW)
	{
		while (wejscieW >> miasto1 >> miasto2)
		{
			wierzcholek *wyp = pHead;
			wierzcholek *tmp = wyp;
			bool znaleziono = false, znaleziono2 = false;
			while (tmp)
			{
				if (tmp->nazwa == miasto1)
					znaleziono = true;
				if (tmp->nazwa == miasto2) {
					znaleziono2 = true;
					dist = tmp->odleglosc;
				}
				tmp = tmp->kolejny_wierzch;
			}
			 if(znaleziono == false || znaleziono2 == false)
			{
				 wyniki << std::endl << "Trasa: " << miasto1 << " -> " << miasto2 << " nie istnieje! (brak miasta w pliku z drogami)" << std::endl;
			}
			else
			{
				dijkstra(pHead, miasto1, miasto2);
				wierzcholek* wskazniczek = pHead;
				while (wskazniczek && wskazniczek->nazwa != miasto2)
					wskazniczek = wskazniczek->kolejny_wierzch;
				if (wskazniczek->odleglosc == std::numeric_limits<double>::infinity())
					wyniki << std::endl << "Trasa: " << miasto1 << " -> " << miasto2 << " nie istnieje! (brak polaczenia miedzy miastami)" << std::endl;
				else
				{
					wierzcholek* wskaznik = pHead;
					while (wskaznik && wskaznik->nazwa != miasto2)
						wskaznik = wskaznik->kolejny_wierzch;
						wyniki << std::endl<<"Trasa: "<< miasto1 << " --> " << miasto2 <<" ("<<wskaznik->odleglosc<<" km): "<< std::endl;
						std::string dystans = std::to_string(wskaznik->odleglosc);
						int dlugosc = 12 + miasto1.length() + miasto2.length() + dystans.length();
						while (wyp)
						{
							if (wyp->nazwa == miasto2)
							{
								wypisywanie(wyp, miasto1, miasto2, pHead, wyniki, dlugosc);
							}
							wyp = wyp->kolejny_wierzch;
						}
				}
			}
		}
	}
	wyniki.close();
}

void dodajWierzcholek(wierzcholek*& pHead, std::string nazwa_miasta, std::string nazwa_celu, double dystans)
{
	wierzcholek* w1 = nullptr;
	wierzcholek* w2 = nullptr;
	auto sprawdzenie = szukaj(pHead, nazwa_miasta);
	if (pHead == nullptr || sprawdzenie == nullptr)
	{
		pHead = new wierzcholek{ nazwa_miasta, pHead, nullptr };
		w1 = pHead;
	}
	else
	{
		w1 = sprawdzenie;
	}
	sprawdzenie = szukaj(pHead, nazwa_celu);
	if (pHead == nullptr || sprawdzenie == nullptr)
	{
		pHead = new wierzcholek{ nazwa_celu, pHead, nullptr };
		w2 = pHead;
	}
	else
	{
		w2 = sprawdzenie;
	}
	dodajCel(w1, w2, dystans);
}

void dodajCel(wierzcholek *& w1, wierzcholek *& w2, double odleglosc)
{
	w1->lista = new cele{ w2, odleglosc, w1->lista };
}

void usuwanieCelu(cele* pHead)
{
	if (pHead != nullptr)
	{
		usuwanieCelu(pHead->nastepne);
		delete pHead;
		pHead = nullptr;
	}

}

void usuwanieWierzcholka(wierzcholek *& pHead)
{
	while (pHead != nullptr)
	{
		wierzcholek* nastepny = pHead->kolejny_wierzch;
		usuwanieCelu(pHead->lista);
		delete pHead;
		pHead = nastepny;
	}
}

wierzcholek* szukaj(wierzcholek*& pHead, std::string szukane_miasto)
{
	if (pHead != nullptr)
	{
		if (pHead->nazwa == szukane_miasto)
			return pHead;
		else
		{
			auto p = pHead;
			while (p != nullptr)
			{
				if (p->nazwa == szukane_miasto)
					return p;
				p = p->kolejny_wierzch;
			}
		}
	}
	return nullptr;
}

void dijkstra(wierzcholek* pHead, std::string m1, std::string m2)
{
	kolejka* wagon = nullptr;
	stworz_kolejke(m1, pHead, wagon);
	while (wagon)
	{
		double distance;
		distance = wagon->pWiersz->odleglosc;
		cele* cel = wagon->pWiersz->lista;
		while (cel)
		{
			wierzcholek* wiersz = static_cast<wierzcholek*>(cel->wierzcholek);
			if (wiersz->odleglosc > distance + cel->dystans)
			{
				wiersz->odleglosc = distance + cel->dystans;
				wiersz->poprzedni_wierzch = wagon->pWiersz;
			}
			cel = cel->nastepne;
		}
		kolejka* pom = wagon->pNext;

		delete wagon;
		wagon = pom;
		if (wagon && wagon->pNext)
			sortuj(wagon);
	}
}


void stworz_kolejke(std::string W, wierzcholek * pHead, kolejka *& pWiersz)
{
	while (pHead)
	{
		if (pHead->nazwa == W)
		{
			pHead->odleglosc = 0;
			pWiersz= new kolejka{ pHead, pWiersz };
		}
		else
		{
			pHead->odleglosc = std::numeric_limits<double>::infinity();
			pWiersz = new kolejka{ pHead, pWiersz };
		}
		pHead = pHead->kolejny_wierzch;
	}
	if (pWiersz->pWiersz->odleglosc != 0)
	{
		kolejka *p = pWiersz;
		while (p->pNext && p->pNext->pWiersz->odleglosc != 0)
		{
			p = p->pNext;
		}
		kolejka *pp = p->pNext;
		p->pNext = pp->pNext;
		pp->pNext = pWiersz;
		pWiersz = pp;
	}
}

void sortuj(kolejka * & pHead)
{
	int rozm = 0;
	kolejka *p = pHead;
	kolejka *q = p->pNext;
	kolejka *t = pHead;
	while (p)
	{
		rozm++;
		p = p->pNext;
	}
	for (int i = 0; i < rozm; i++)
	{
		p = pHead;
		q = p->pNext;
		t = pHead;
		if (p->pWiersz->odleglosc > q->pWiersz->odleglosc)
		{
			pHead = q;
			p->pNext = q->pNext;
			q->pNext = p;
			q = p->pNext;
			t = pHead;
		}
		else
		{
			p = p->pNext;
			q = q->pNext;
		}
		for (int j = 0; j < rozm - 3; j++)
		{

			if (p->pWiersz->odleglosc > q->pWiersz->odleglosc)
			{
				t->pNext = q;
				p->pNext = q->pNext;
				q->pNext = p;
				t = q;
				q = p->pNext;
			}
			else
			{
				p = p->pNext;
				q = q->pNext;
				t = t->pNext;
			}
		}
		if (i == 0 && rozm>2)
		{
			if (p->pWiersz->odleglosc > q->pWiersz->odleglosc)
			{
				t->pNext = q;
				p->pNext = nullptr;
				q->pNext = p;
			}
		}
	}
}

void wypisywanie(wierzcholek *wyp, std::string W, std::string W2, wierzcholek* pHead, std::ofstream & wypisz, int szerokosc)
{
	if (wyp && wyp->poprzedni_wierzch)
	{
		if (wyp->nazwa == W)
		{
			wierzcholek* tmp = pHead;
			double dist;
			while (tmp)
			{
				if (tmp->nazwa == W2)
					dist = tmp->odleglosc;
				tmp = tmp->kolejny_wierzch;
			}
		}
		else
		{
			wypisywanie(wyp->poprzedni_wierzch, W, W2, pHead, wypisz, szerokosc);
			std::string miasto1, miasto2;
			miasto1 = wyp->poprzedni_wierzch->nazwa;
			miasto2 = wyp->nazwa;
			double dystans = wyp->odleglosc - wyp->poprzedni_wierzch->odleglosc;
			wypisz << " " << miasto1 << " --> " << miasto2;
			wypisz.width(szerokosc - miasto1.length() - miasto2.length()-8);
			wypisz<< dystans << std::endl;
		}
	}
}
