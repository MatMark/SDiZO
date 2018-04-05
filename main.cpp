#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <conio.h>

#include "inter.h"
#include "tab.h"
#include "list.h"
#include "heap.h"

using namespace std;

int main()
{
	int pointer;
	inter * object = NULL, * sym = NULL;
	bool exit = false;
	string tmp = "BRAK";
	string error = "Struktura jest pusta, wczytaj najpierw dane z pliku\n(nacisnij dowolny przycisk)";
	
	//obsluga menu
	
	while (!exit)
	{
		system("cls");
		if(object != NULL) {
			tmp = typeid(*object).name() +1;
			if (tmp == "tab")cout << "Aktualna struktura: Tablica\n\n";
			else if (tmp == "list")cout << "Aktualna struktura: Lista\n\n";
			else if (tmp == "heap")cout << "Aktualna struktura: Kopiec binarny\n\n";
			else cout << "Aktualna struktura: " << tmp << "\n\n";
		}
		
		cout << "1. Zbuduj z pliku\n2. Usun\n3. Dodaj\n4. Znajdz\n5. Wyswietl\n6. Symulacje\n7. Wyjdz\n";
		cin >> pointer;
		system("cls");
		switch (pointer)
		{
				case 1:
				cout << "1. Tablica\n2. Lista\n3. Kopiec binarny\n4. Cofnij\n";
				cin >> pointer;
				system("cls");
				switch (pointer)
				{
					case 1:
						object = new tab;
						break;
				
					case 2:
						object = new list;
						break;
				
					case 3:
						object = new heap;
						break;
				
					default:
						break;
				
				}
				if(pointer == 1 || pointer == 2 || pointer == 3)object->Build();
				break;
				
			case 2:
				if (object != NULL) object->Delete();
				else{
					cout << error;
					getch();
				}
				break;
				
			case 3:
				if (object != NULL) object->Add();
				else{
					cout << error;
					getch();
				}
				break;
				
			case 4:
				if (object != NULL) object->Search();
				else{
					cout << error;
					getch();
				}
				break;
				
			case 5:
				if (object != NULL) object->Print();
				else{
					cout << error;
					getch();
				}
				break;
			
			case 6:
				cout << "1. Tablica\n2. Lista\n3. Kopiec binarny\n4. Cofnij\n";
				cin >> pointer;
				system("cls");
				if (pointer != 1 && pointer != 2 && pointer != 3) break;
				switch (pointer)
				{
					case 1:
						sym = new tab;
						break;
					
					case 2:
						sym = new list;
						break;
				
					case 3:
						sym = new heap;
						break;
				
					default:
						break;
						
				}
				if (pointer != 1 && pointer != 2 && pointer != 3) break;
				cout << "1. Dodawanie\n2. Usuwanie\n3. Przeszukiwanie\n4. Cofnij\n";
				cin >> pointer;
				system("cls");
				if(pointer != 1 && pointer != 2 && pointer != 3)break;
				int size, rep;
				cout << "Wielkosc struktury: ";
				cin >> size;
				cout << "Liczba powtorzen: ";
				cin >> rep;
				system("cls");
				switch (pointer)
				{

					case 1:
						sym->SymAdd(size, rep);
						break;
					
					case 2:
					   	sym->SymDelete(size, rep);
					   	break;
			
					case 3:
					   	sym->SymSearch(size, rep);
					   	break;
			
					default:
						break;
					
				}
				sym = NULL;
				delete sym;
				break;
			
			case 7:
				object = NULL;
				delete object;
				exit = true;
				break;
			
			default:
				break;
				
		}
	}
    return 0;       
}