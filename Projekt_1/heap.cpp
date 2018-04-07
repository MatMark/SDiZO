#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <cmath>

#include "heap.h"
#include "timer.h"

//metody klasy obslugujacej kopiec binarny


using namespace std;

heap::heap()
{
	srand( time( NULL ) );
	size = 0;
}

heap::~heap()
{

}

//metoda dodajaca nowy element "PUSH"

void heap::Add()
{
	int temp;
	cout << "Podaj wstawiana wartosc: ";
	cin >> temp;
	int * q = new int[size];
	//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy
	for(int i = 0; i < size; i++)
	{
		q[i]=h[i];
	}
	size++;
	delete [] h;
	h = new int[size];
	//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
	for(int i = 0; i < size-1; i++)
	{
		h[i]=q[i];
	}
	delete [] q;
	//dodawanie nowego elementu
	int j = size-1, k = (j-1)/2;	//obliczanie pozycji rodzica wstawianego elementu
	while(j>0 && h[k] < temp)	//sprawdzamy warunek kopca
	{
		h[j] = h[k];	//rodzic na miejsce syna
		j = k;	//zmiana pozycji na pozycje rodzica
		k = (j-1)/2;	//obliczamy pozycje aktualnego rodzica
	}
	h[j] = temp;
}


//metoda usuwajaca dany element

void heap::Delete()
{
	if (size > 0)
	{
		int value;
		bool exist = false;
		cout << "Wartosc do usuniecia: ";
		cin >> value;
		//wyszukiwanie wartosci do usuniecia
		for(int l = 0; l < size; l++)
		{
			if (h[l]==value) 
			{
				exist = true;
				swap(h[l],h[0]);	//bo dostep tylko do korzenia
				swap(h[0],h[size-1]);
				break;
			}
		}
		if (!exist)
		{
			   cout << "Podana wartosc nie znajduje sie	w kopcu";
		}
		else
		{

			size--;
			for(int n = ceil(log2(size+1)); n >= 0; n--)
			{
				int j;
				for(int k = (size-1)/2; k >= 0; k--)//przechodzimy po wszystkich rodzicach
				{
					j = 2 * k + 1;	//wyliczenie pozycji lewego syna
					if(j + 1 < size && h[j + 1] > h[j]) j++;	//ustalanie, ktory syn jest wiekszy
					if(j + 1 < size && h[k]<h[j]) swap(h[j],h[k]);	//rodzic na miejsce syna
				}
			}
		    
			int * q = new int[size];
			//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy
			for(int i = 0; i < size; i++)
			{
				q[i]=h[i];
			}
			delete [] h;
			h = new int[size];
			//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
			for(int i = 0; i < size; i++)
			{
				h[i]=q[i];
			}
			delete [] q;
			
			
			cout << "Usunieto podana wartosc";	
		}
	}
	else 
	{
		cout << "Kopiec jest pusty";
	}
	cout << "\n(nacisnij dowolny przycisk)";
	getch();
}

//metoda tworzaca kopiec binarny z danych zawartych w pliku

void heap::Build()
{
	char name[64];
	int temp;
	cout << "Nazwa pliku z danymi: ";
	cin >> name;
	ifstream file;
	file.open(name, ios::in);
	if(file.good())
	{
		file >> size;
		h = new int[size];
		file >> h[0];
		for(int i = 1; i < size; i++)
		{
			//uzyty algorytm wstawiania nowego elementu
			file >> temp;
			int j, k;
			j=i;
			k=(j-1)/2;
			while(j>0 && h[k] < temp)
			{
				h[j] = h[k];
				j = k;
				k = (j-1)/2;
			}
			h[j] = temp;
		}
		file.close();
		cout << "Wczytano dane z pliku " << name << "\n(nacisnij dowolny przycisk)";
		getch();	
	}
	else
	{
		cout << "Nie udalo sie wczytac danych z pliku " << name << "\n(nacisnij dowolny przycisk)";
		getch();
	}

}

//funkcja wywolywana do wyszukiwania elementu
bool heap::Find(int value, int node)
{
	bool ret = false;
	int left = 2*node+1, right = 2*node+2;
	if(node < size && (h[node] == value || h[left] == value || h[right] == value)) ret = true;
	if (ret == false && left < size && h[left] > value) ret = Find(value, left);
	if (ret == false && right < size && h[right] > value) ret = Find(value, right);
	return ret;
}

//metoda wyszukujaca wybrany element
void heap::Search()
{
	int value;
	bool exist;
	cout << "Szukana wartosc: ";
	cin >> value;
	exist = Find(value, 0);
	if (exist) cout << "Wyszukiwana wartosc znajduje sie w kopcu\n";
	else cout << "Wyszukiwana wartosc nie znajduje sie w kopcu\n";
	cout << "(nacisnij dowolny przycisk)";
	getch();
}

//metoda wyswietlajaca utworzony kopiec binarny

void heap::Print()
{
	int digits = 2; //ilu cyfrowe liczby
	int level = ceil(log2(size+1));	//wyskosc kopca
	int space = pow(2,level-1)*digits;	//wielkosc odstepow
	int counter = 1, i = 0; //liczba wstawianych elementow na danym poziomie
	while (i < size)
	{
		for(int j = 0; j < counter; j++)
		{
			cout.width( space );
			cout << internal << h[i];
			for(int k = 0; k < space; k++)	cout << " ";
			i++;
			if(i >= size) break;
		}
		if(i >= size) break;
		cout << endl << endl;
	   	space /= 2;
		counter *= 2;
	}
	cout << "\n\n(nacisnij dowolny przycisk)";
	getch();
}

//metoda tworzaca nowy kopiec binarny z losowymi elementami

float heap::SymBuild(int s)
{
	timer * clock = new timer;
	clock->StartCounter();
	int temp;
	h = new int[s];
	h[0] = rand()%N;
	for(int i = 1; i < s; i++)
	{
		//uzyty algorytm wstawiania nowego elementu
		temp = rand()%N;
		int j, k;
		j=i;
		k=(j-1)/2;
		while(j>0 && h[k] < temp)
		{
			h[j] = h[k];
			j = k;
			k = (j-1)/2;
		}
		h[j] = temp;
	}
	float build_time = clock->GetCounter();
	clock = NULL;
	delete clock;
	return build_time;
}

//metoda symulujaca dodawanie elementu na "r" kopcach binarnych o losowych elementach rozmiaru "s"

void heap::SymAdd(int s, int r)
{
	int temp, size = s, rep = r;
	float build_time =0;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		temp = rand()%N;
		int * q = new int[size];
		//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy
		for(int i = 0; i < size; i++)
		{
			q[i]=h[i];
		}
		size++;
		delete [] h;
		h = new int[size];
		//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
		for(int i = 0; i < size-1; i++)
		{
			h[i]=q[i];
		}
		delete [] q;
		//dodawanie nowego elementu
		int j, k;
		j=size-1;
		k=(j-1)/2;	//obliczanie pozycji rodzica wstawianego elementu
		while(j>0 && h[k] < temp)	//sprawdzamy warunek kopca
		{
			h[j] = h[k];	//rodzic na miejsce syna
			j = k;	//zmiana pozycji na pozycje rodzica
			k = (j-1)/2;	//obliczamy pozycje aktualnego rodzica
		}
		h[j] = temp;
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}

//metoda symulujaca usuwanie elementu na "r" kopcach binarnych o losowych elementach rozmiaru "s"

void heap::SymDelete(int s, int r)
{
	int size = s, rep = r;
	float build_time =0;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		if (size > 0)
		{
		    int value = rand()%N;
		   	bool exist = false;
			//wyszukiwanie wartosci do usuniecia
			for(int l = 0; l < size; l++)
			{
				if (h[l]==value) 
				{
					exist = true;
					swap(h[l],h[0]);	//bo dostep tylko do korzenia
					swap(h[0],h[size-1]);
					break;
				}
			}
			if(exist)
			{
				size--;
				for(int n = ceil(log2(size+1)); n >= 0; n--)
				{
					int j;
					for(int k = (size-1)/2; k >= 0; k--)//przechodzimy po wszystkich rodzicach
					{
						j = 2 * k + 1;	//wyliczenie pozycji lewego syna
						if(j + 1 < size && h[j + 1] > h[j]) j++;	//ustalanie, ktory syn jest wiekszy
						if(j + 1 < size && h[k]<h[j]) swap(h[j],h[k]);	//rodzic na miejsce syna
					}
				}
			}
		    
			int * q = new int[size];
			//petla kopiujaca wszystkie elementy do nowej tymczasowej tablicy
			for(int i = 0; i < size; i++)
			{
				q[i]=h[i];
			}
			
			delete [] h;
			h = new int[size];
			//petla przenoszaca dane z nowo utworzonej tymczasowej tablicy do wlasciwej
			for(int i = 0; i < size; i++)
			{
				h[i]=q[i];
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

//metoda symulujaca wyszukiwanie elementu na "r" kopcach binarnych o losowych elementach rozmiaru "s"

void heap::SymSearch(int s, int r)
{
	int value, size = s, rep = r;
	float build_time =0;
	bool exist;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		value = rand()%N;
		exist = Find(value, 0);
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}
