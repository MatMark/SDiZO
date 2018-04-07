#include <iostream>
#include <conio.h>
#include <fstream>
#include <ctime>

#include "list.h"


//metody klasy obslugujacej liste


using namespace std;

list::list()
{
	srand( time( NULL ) );
	size = 0;
	first = NULL;
	last = NULL;
}

list::~list()
{
	
}

//metoda dodajaca element do listy na pozycje o zadanej wartosci, badz jesli taka nie istnieje na poczatek listy

void list::Add()
{
	int position, value;
	bool exist = false;
	cout << "Wartosc elementu po ktorym bedzie wstawiony nowy element: ";
	cin >> position;
	cout << "Wartosc dodawanego elementu: ";
	cin >> value;
	element * temp = first, * added;
	
	for(int i = 0; i < size; i++)
	{
		if (temp->value==position){
			exist = true;
			added = new element;
			added->next = temp->next;
			temp->next = added;
			added->prev = temp;
			added->next->prev = added;
			added->value = value;
			size++;
		}
		temp = temp->next;
	}
	if (!exist)
	{
		temp = new element;
		temp->value=value;
		temp->prev=NULL;
		temp->next=first;
		first=temp;
		size++;
	}
	
	if(exist) cout << "Dodano element po elemencie o wartosci " << position << endl;
	else if (!exist) cout << "Dodano element na pierwszej pozycji\n";
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//metoda usuwajaca zadana wartosc z listy

void list::Delete()
{
	int value;
	bool exist = false;
	cout << "Wartosc do usuniecia: ";
	cin >> value;
	
	element * temp = first;
	for(int i = 0; i < size; i++)
	{
		if (temp->value==value) {
			exist = true;
			if(temp->prev && temp->next) 
			{
				temp->prev->next = temp->next;	
				temp->next->prev = temp->prev;
			}
			else if (!temp->prev)
			{
				first = temp->next;
				temp->next->prev = NULL;
			}
			else if (!temp->next)
			{
				last = temp->prev;
				temp->prev->next = NULL;
			}
			size--;
		}
		temp = temp->next;
	}
	if (exist) cout << "Usunieto elementy o wartosci " << value << endl;
	if (!exist) cout << "Element nie zostal usuniety poniewaz lista nie zawiera elementu o wartosci " << value << endl;
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//metoda tworzaca liste z danych zawartych w pliku

void list::Build()
{
	char name[64];
	cout << "Nazwa pliku z danymi: ";
	cin >> name;
	
	element * temp;
	ifstream file;
	file.open(name, ios::in);
	if(file.good()){
		file >> size;

		for(int i = 0; i < size; i++)
		{
			temp = new element;
			file >> temp->value;
			temp->next = NULL;
			temp->prev = last;
			last = temp;
			if(temp->prev) temp->prev->next = temp;
			else first = temp;
		}
		file.close();
		cout << "Wczytano dane z pliku " << name << endl;
		cout << "(nacisnij dowolny przycisk)";
		getch();	
	}
	else{
		cout << "Nie udalo sie wczytac danych z pliku " << name << endl;
		cout << "(nacisnij dowolny przycisk)";
		getch();
	}	
}

//metoda wyszykujaca podanej wartosci na liscie

void list::Search()
{
	int value;
	bool exist = false;
	cout << "Szukana wartosc: ";
	cin >> value;
	
	element * temp = first;
		for(int i = 0; i < size; i++)
		{
			if (temp->value==value) exist = true;
			temp = temp->next;
		}
	if (exist) cout << "Wyszukiwana wartosc znajduje sie na liscie\n";
	else cout << "Wyszukiwana wartosc nie znajduje sie na liscie\n";
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//metoda wyswietlajaca liste

void list::Print()
{
	char arrow = 18;
	element * temp = first;
		for(int i = 0; i < size; i++)
		{
			cout << "\t" << temp->value << endl;
			if(i<size-1)cout << endl << "\t" << arrow << endl << endl;
			temp = temp->next;
		}
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//mtoda tworzaca nowa liste z losowymi elementami

float list::SymBuild(int s)
{
	timer * clock = new timer;
	clock->StartCounter();
	element * temp;
	for(int j = 0; j < s; j++)
	{
		temp = new element;
		temp->value = rand()%N;
		temp->next = NULL;
		temp->prev = last;
		last = temp;
		if(temp->prev) temp->prev->next = temp;
		else first = temp;
	}
	float build_time = clock->GetCounter();
	clock = NULL;
	delete clock;
	return build_time;
}

//metoda symulujaca dodawanie elementu na "r" listach o losowych elementach rozmiaru "s"

void list::SymAdd(int s, int r)
{
	int start, size = s, rep = r;
	float build_time =0;
	element * temp, * added;
	cout << "Pozycja usuwania:\n1. Poczatek listy\n2. Koniec listy\n3. Losowe miejsce\n";
	cin >> start;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		if  (start == 1){
			temp = new element;
			temp->value=rand()%N;
			temp->prev=NULL;
			temp->next=first;
			first=temp;
		}
		else if (start == 2){
			temp = new element;
			temp->value=rand()%N;
			temp->next=NULL;
			temp->prev=last;
			last=temp;
		}
		else if (start == 3){
			temp = first;
			for(int i=0; i<rand()%size; i++)
			{
				temp = temp->next;
			}
			if(temp->prev && temp->next) 
			{
				added = new element;
				added->next = temp->next;
				temp->next = added;
				added->prev = temp;
				added->next->prev = added;
				added->value = rand()%N;
			}
			else if (!temp->prev)
			{
				temp = new element;
				temp->value=rand()%N;
		   	   	temp->prev=NULL;
				temp->next=first;
				first=temp;
			}
			else if (!temp->next)
			{
				temp = new element;
			   	temp->value=rand()%N;
				temp->next=NULL;
			   	temp->prev=last;
				last=temp;
			}
		}
	size++;
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}

//metoda symulujaca usuwanie elementu na "r" listach o losowych elementach rozmiaru "s"

void list::SymDelete(int s, int r)
{
	int start, size = s, rep = r;
	float build_time =0;
	element * temp;
	cout << "Pozycja usuwania:\n1. Poczatek listy\n2. Koniec listy\n3. Losowe miejsce\n";
	cin >> start;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		if  (start == 1){
			temp = first;
			first = temp->next;
			temp->next->prev = NULL;
		}
		else if (start == 2){
			temp = last;
			last = temp->prev;
			temp->prev->next = NULL;
		}
		else if (start == 3) 
		{
			temp = first;
			for(int i=0; i<rand()%size; i++)
			{
				temp = temp->next;
			}
			if(temp->prev && temp->next) 
			{
				temp->prev->next = temp->next;	
				temp->next->prev = temp->prev;
			}
			else if (!temp->prev)
			{
				first = temp->next;
				temp->next->prev = NULL;
			}
			else if (!temp->next)
			{
				last = temp->prev;
				temp->prev->next = NULL;
			}
		}
		size--;
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
	
}

//metoda symulujaca wyszukiwanie elementu na "r" listach o losowych elementach rozmiaru "s"

void list::SymSearch(int s, int r)
{
	int value, size = s, rep = r;
	float build_time =0;
	bool exist;
	element * temp;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		exist = false;
		value = rand()%N;
		temp = first;
		for(int i = 0; i < size && !exist; i++)
		{
			if (temp->value==value) exist = true;
			temp = temp->next;
		}
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}
