#include <iostream>
#include "header.h"

int main(int argc, char *argv[])
{
	std::string wczyt1, wczyt2, wypis;
	
	if (argc == 7 && argv[1][0] == '-' &&  argv[3][0] == '-' &&  argv[5][0] == '-')
	{
		std::string sprawdzenie1 = argv[1];
		std::string sprawdzenie2 = argv[3];
		std::string sprawdzenie3 = argv[5];
		if (sprawdzenie1.length() != 2 || sprawdzenie2.length() != 2 || sprawdzenie3.length() != 2) 
		{
			std::cout << "bledne uzycie przelacznikow! (nazwa dluzsza niz byc powinna)" << std::endl;
			return 0;
		}
		if (argv[1][1] == 'd' &&  argv[3][1] == 't' &&  argv[5][1] == 'o')
		{
			wczyt1 = argv[2];
			wczyt2 = argv[4];
			wypis = argv[6];
		}
		else	if (argv[1][1] == 'd' &&  argv[3][1] == 'o' &&  argv[5][1] == 't') {
			wczyt1 = argv[2];
			wczyt2 = argv[6];
			wypis = argv[4];
		}
		else	if (argv[1][1] == 't' &&  argv[3][1] == 'd' &&  argv[5][1] == 'o') {
			wczyt1 = argv[4];
			wczyt2 = argv[2];
			wypis = argv[6];
		}
		else	if (argv[1][1] == 't' &&  argv[3][1] == 'o' &&  argv[5][1] == 'd') {
			wczyt1 = argv[4];
			wczyt2 = argv[6];
			wypis = argv[2];
		}
		else	if (argv[1][1] == 'o' &&  argv[3][1] == 't' &&  argv[5][1] == 'd') {
			wczyt1 = argv[6];
			wczyt2 = argv[4];
			wypis = argv[2];
		}
		else	if (argv[1][1] == 'o' &&  argv[3][1] == 'd' &&  argv[5][1] == 't') {
			wczyt1 = argv[6];
			wczyt2 = argv[2];
			wypis = argv[4];
		}
		else {
			std::cout << "bledne uzycie przelacznikow! (zle nazwy przelacznikow)" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "bledne uzycie przelacznikow! (zla liczba przelacznikow lub ktorys nie zaczyna sie od -" << std::endl;
		return 0;
	}
	if(!wczyt1 || !wczyt2 || !wypis)
	{
		std::cout<<"ktorys plik nie zostal podany";
		return 1;
	}
	else
	{
	wczytanie(wczyt1, wczyt2, wypis);
	std::cout << "program wlaczyl sie poprawnie"<<std::endl;
	return 0;
	}
}
