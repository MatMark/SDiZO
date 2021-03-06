#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>

#include "tab.h"
#include "timer.h"

//metody klasy obslugujacej tablice


using namespace std;

tab::tab()
{
	srand( time( NULL ) );
	size = 0;
}

tab::~tab()
{
	delete [] t;
}

//metoda dodajaca nowy element na wybranej pozycji o wybranej wartosci

void tab::Add()
{
		int position, value;
		cout << "Pozycja nowego elementu [0-" << size << "]: ";
		cin >> position;
		cout << "Wartosc nowego elementu: ";
		cin >> value;
		if(position == size)
		{
			size++;
			int * q = new int[size];
			q[size-1] = value;
			memcpy(q, t, (size - 1) * sizeof(int));
			delete [] t;
			t = q;
			q = NULL;
			delete [] q;
			cout << "Dodano element na pozycji " << position << " o wartosci " << value << "\n(nacisnij dowolny przycisk)";
			getch();
		}
		else if(position < size){
			//relokacja pamieci
			size++;
			int * q = new int[size];
			q[position] = value;
			memcpy(q,t,position*sizeof(int));
			memcpy(q+position+1,t+position,(size-position-1)*sizeof(int));
			delete [] t;
			t = q;
			q = NULL;
			delete [] q;
			cout << "Dodano element na pozycji " << position << " o wartosci " << value << "\n(nacisnij dowolny przycisk)";
			getch();
		}
		else {
		cout << "Niemozliwe jest dodanie tego elementu" << endl << "(nacisnij dowolny przycisk)";
		getch();
	}
}

//metoda usuwajaca wybrany element tablicy

void tab::Delete()
{
	int position;
	cout << "Element do usuniecia [0-" << size << "]: ";
	cin >> position;
	
	if(size>=1 && position <= size){
		size--;
		int * q = new int[size];
		//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy i usuwajaca element
		for(int i = 0; i < size; i++)
		{
			if (i<position) q[i] = t[i];
			else q[i] = t[i+1];
		}
		delete [] t;
		t = new int[size];
		//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
		for(int i = 0; i < size; i++)
		{
			t[i] = q[i];
		}
		delete [] q;
		cout << "Usunieto element numer " << position << "\n(nacisnij dowolny przycisk)";
		getch();
	}
	else {
		cout << "Niemozliwe jest usuniecie tego elementu\n(nacisnij dowolny przycisk)";
		getch();
	}
}

//metoda tworzaca tablice z danych zawartych w pliku

void tab::Build()
{
	char name[64];
	cout << "Nazwa pliku z danymi: ";
	cin >> name;
	
	ifstream file;
	file.open(name, ios::in);
	if(file.good()){
		file >> size;
		t = new int[size];
		for(int i = 0; i < size; i++)
		{
			file >> t[i];
		}
		file.close();
		cout << "Wczytano dane z pliku " << name << "\n(nacisnij dowolny przycisk)";
		getch();	
	}
	else{
		cout << "Nie udalo sie wczytac danych z pliku " << name << "\n(nacisnij dowolny przycisk)";
		getch();
	}
	
}

//metoda wyszukujaca wybrany element

void tab::Search()
{
	int value;
	bool exist = false;
	cout << "Szukana wartosc: ";
	cin >> value;
	
	for(int i = 0; i < size && !exist; i++)
	{
		if (t[i]==value) exist = true;
	}
	
	if (exist) cout << "Wyszukiwana wartosc znajduje sie w tablicy\n";
	else cout << "Wyszukiwana wartosc nie znajduje sie w tablicy\n";
	cout << "(nacisnij dowolny przycisk)";
	getch();
	
}

//metoda wyswietlajaca utworzona tablice

void tab::Print()
{
	for(int i = 0; i < size; i++)
	{
		cout << "("<<i<<")\t" << t[i] << endl;
	}
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//mtoda tworzaca nowa tablice z losowymi elementami

float tab::SymBuild(int s)
{
	timer * clock = new timer;
	clock->StartCounter();
	size = s;
	t = NULL;
	delete [] t;
	t = new int[s];
	for(int j = 0; j < s; j++)
	{
		t[j] = rand()%s;
	}
	float build_time = clock->GetCounter();
	clock = NULL;
	delete clock;
	return build_time;
}

//metoda symulujaca dodawanie elementu na "r" tablicach o losowych elementach rozmiaru "s"

void tab::SymAdd(int s, int r)
{
	int value, position, start, size = s, rep = r;
	float build_time =0;
	cout << "Pozycja dodawania:\n1. Poczatek tablicy\n2. Koniec tablicy\n3. Losowe miejsce\n";
	cin >> start;
	if  (start == 1) position = 0;
	else if (start == 2) position = size;
	else if (start == 3) position = rand()%size;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		size = s;
		build_time += SymBuild(size);
		value = rand()%size;
		if(position == size)
		{
			//relokacja pamieci
			size++;
			int * q = new int[size];
			q[size-1] = value;
			memcpy(q, t, (size - 1) * sizeof(int));
			delete[] t;
			t = q;
			q = NULL;
			delete [] q;
		}
		else if(position < size){
			size++;
			int * q = new int[size];
			
			q[position] = value;
			memcpy(q,t,position*sizeof(int));
			memcpy(q+position+1,t+position,(size-position-1)*sizeof(int));
			delete [] t;
			t = q;
			q = NULL;
			delete [] q;
		}
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";
	clock = NULL;
	delete clock;
	getch();
}

//metoda symulujaca usuwanie elementu na "r" tablicach o losowych elementach rozmiaru "s"

void tab::SymDelete(int s, int r)
{
	int position, start, size = s, rep = r;
	float build_time =0;
	cout << "Pozycja usuwania:\n1. Poczatek tablicy\n2. Koniec tablicy\n3. Losowe miejsce\n";
	cin >> start;
	if  (start == 1) position = 0;
	else if (start == 2) position = size;
	else if (start == 3) position = rand()%size;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		if(size>=1 && position <= size){
		size--;
		int * q = new int[size];
		//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy i usuwajaca element
		for(int i = 0; i < size; i++)
		{
			if (i<position) q[i] = t[i];
			else q[i] = t[i+1];
		}
		delete [] t;
		t = new int[size];
		//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
		for(int i = 0; i < size; i++)
		{
			t[i] = q[i];
		}
		delete [] q;
		}	
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}

//metoda symulujaca wyszukiwanie elementu na "r" tablicach o losowych elementach rozmiaru "s"

void tab::SymSearch(int s, int r)
{
	int value, size = s, rep = r;
	float build_time =0;
	bool exist;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		exist = false;
		value = rand()%size;
		for(int j = 0; j < size && !exist; j++)
		{
			if (t[j]==value) exist = true;
		}
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}
