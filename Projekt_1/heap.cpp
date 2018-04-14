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
	delete [] h;
}

//metoda dodajaca nowy element

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

//metoda wyszukujaca element do usuniecia
int heap::Find(int value, int node)
{
	
	int position = NULL;
	int left = 2*node+1, right = 2*node+2;	//lewy i prawy syn
	
	if(node<size)	//sprawdza czy dany wezel jest rowny szukanej wartosci
	{
		if(h[node]==value) position = node;
	}

	if(!position)	//jezeli lewy syn jest wiekszy badz rowny niz szukana wartosc to powtarza wyszukiwanie od niego
	{
		if(left<size)
		{
			if(h[left]>=value) position = Find(value, left);
		}	
	}

	if(!position)	//jezeli prawy syn jest wiekszy badz rowny niz szukana wartosc to powtarza wyszukiwanie od niego
	{
		if(right<size)
		{
			if(h[right]>=value) position = Find(value, right);
		}	
	}

	return position;
}

//metoda usuwajaca dany element

void heap::Delete()
{
	if (size > 0)
	{
		int value;
		cout << "Wartosc do usuniecia: ";
		cin >> value;
		int position = Find(value, 0);	//wyszukiwanie pozycji elementu do usuniecia
		if(h[position] == value)
		{
				swap(h[position],h[size-1]);	//zamiana usuwanego elementu z ostatnim elementem
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
				//relokacja pamieci
				int * q = new int[size];
				memcpy(q, h, (size) * sizeof(int));
				delete[] h;
				h = q;
				q = NULL;
				delete [] q;
 			
				
				cout << "Usunieto podana wartosc";
		}
		else
		{
			   cout << "Podana wartosc nie znajduje sie	w kopcu";
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


//metoda wyszukujaca wybrany element
void heap::Search()
{
	int value;
	cout << "Szukana wartosc: ";
	cin >> value;
	if (h[Find(value, 0)]==value) cout << "Wyszukiwana wartosc znajduje sie w kopcu\n"; //zaczyna wyszukiwanie od korzenia
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
	size = s;
	int temp;
	h = NULL;
	delete [] h;
	h = new int[s];
	h[0] = rand()%s;
	for(int i = 1; i < s; i++)
	{
		//uzyty algorytm wstawiania nowego elementu
		temp = rand()%s;
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
	float build_time = 0;
	timer * clock = new timer;
	clock->StartCounter();
	for(int i = 0; i < rep; i++)
	{
		build_time += SymBuild(size);
		temp = rand()%s;
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
		    int value = rand()%size;
		   	int position = Find(value, 0);	//wyszukiwanie pozycji elementu do usuniecia
			if(h[position] == value)
			{
				swap(h[position],h[size-1]);	//zamiana usuwanego elementu z ostatnim elementem
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
			    //relokacja pamieci
				int * q = new int[size];
				memcpy(q, h, (size) * sizeof(int));
				delete[] h;
				h = q;
				q = NULL;
				delete [] q;
			}

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
		value = rand()%size;
		exist = Find(value, 0);
	}
	system("cls");
	cout << "Sredni czas wykonania: " << (clock->GetCounter()-build_time)/rep << "\n(nacisnij dowolny przycisk)";;
	clock = NULL;
	delete clock;
	getch();
}
