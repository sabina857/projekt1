#include <iostream>
#include<cstdlib>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include<fstream>
#include<string>
#include <chrono>
#include <windows.h>
using namespace std;
int rozmiar_pliku;
int a[9] = { 1,2,3,3,3,3,3,3,2 }; //tablica 9 elementowa
int ile(int rozmiar, int* tabl, int szuk)// rozmiar tablicy, tablica, szukany element
{
    int x, wynik = 0;
    for (x = 0; x <= rozmiar - 1; x++)
    {
        if (tabl[x] == szuk)
        {
            wynik++;
        }
    }
    return wynik;
}

int* sortowanie(int tab[], int rozmiar)//sortowanie
{
    int* wynik;
    wynik = new int[rozmiar];
    int licznik_wynik = 0;
    for (int i = 0; i < rozmiar; i++)
    {
        int tmp = tab[i];
        if (tmp != -1)
        {
            int ile_tmp = ile(rozmiar, tab, tmp);
            for (int j = 0; j < ile_tmp; j++)
            {
                wynik[licznik_wynik] = tmp;
                licznik_wynik++;
            }
            for (int j = 0; j < rozmiar; j++)
            {
                if (tab[j] == tmp)
                {
                    tab[j] = -1;
                }
            }
        }
    }
    return wynik;
}
int* odczyt_z_pliku(string nazwa_pliku)//odczyt z pliku
{
    fstream plik;
    plik.open(nazwa_pliku);
    int rozmiar = 0;
    int tmp;
    while (plik >> tmp)
    {
        rozmiar++;
    }
    rozmiar_pliku = rozmiar;
    plik.close();
    plik.open(nazwa_pliku);
    int* wynik;
    wynik = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++)
    {
        plik >> wynik[i];
    }
    return sortowanie(wynik, rozmiar);
}
int losowy_test_pomiar_czasu(int rozmiar, int mod)
{
    int* tab;
    tab = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++)
    {
        tab[i] = rand() % mod;
    }
    clock_t start = clock();
    int* wynik = sortowanie(tab, rozmiar);
    clock_t stop = clock();
    return (stop - start);
}

int* losowy_test(int rozmiar, int mod)
{
    int* tab;
    tab = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++)
    {
        tab[i] = rand() % mod;
    }

    int* wynik = sortowanie(tab, rozmiar);
    return wynik;
}
/*
void generowanie_wykresu()
{
    int liczby[10] = { (int)1e3,(int)1e4,(int)1e5,(int)1e6,(int)(5 * 1e6),(int)1e7,(int)(2 * 1e7),(int)(5 * 1e7),(int)1e8 };
    for (int i = 0; i < 9; i++)
    {
        cout << liczby[i] << ":" << losowy_test(liczby[i], 20) << "\n";
    }
    return;
}*/
void zapisz_do_pliku(string nazwa_pliku, int* tab)
{
    ofstream plik;
    plik.open(nazwa_pliku);
    int i = 0;
    while (i < rozmiar_pliku)
    {
        plik << tab[i]<<"\n";
        i++;
    }
    plik.close();
    rozmiar_pliku = 0;
    return;
}

int main()
{
    srand(time(NULL));
    while (true)
    {
        int wybor;
        int* wynik_sortowania=NULL;
        int liczba_liczb;
        cout << "Wybierz jedna z opcji: \n"; //opcje do wyboru
        cout << "Jesli chcesz wczytac dane z pliku wcisnij 1.\n";
        cout << "Jesli chcesz podac dane do konsoli wcisnij 2.\n";
        cout << "Jesli chcesz zobaczyc przykladowy zestaw wcisnij 3.\n";
        cout << "Jesli chcesz zakonczyc program wcisnij 4\n";
        string nazwa_pliku;

        cin >> wybor;
        switch (wybor)//tworzymy opcje do wyboru
        {
        case 1: {
            cout << "podaj nazwe pliku: \n";

            cin >> nazwa_pliku;
            wynik_sortowania = odczyt_z_pliku(nazwa_pliku);
            liczba_liczb=rozmiar_pliku;
            break;
        }
        case 2: {
            cout << "podaj ilosc liczb ktore chcesz podac, a nastepnie w nowych liniach podaj kolejne liczby\n";
            int n;
            cin >> n;
            int* tablica;
            tablica = new int[n];
            for (int i = 0; i < n; i++)
            {
                cin >> tablica[i];
            }
            wynik_sortowania = sortowanie(tablica, n);
            liczba_liczb=n;
            break;
        }
        case 3: {
            cout << "podaj ilosc liczb oraz ich zakres:\n";
            int rozmiar;
            int zakres;
            cin >> rozmiar >> zakres;
            wynik_sortowania = losowy_test(rozmiar, zakres);
            liczba_liczb=rozmiar;
            break;
        }
        case 4: {
            return 0;
            break;
        }
        }
        cout << "Wybierz jedna z opcji: \n"; //drugie opcje do wyboru
        cout << "Jesli chcesz zapisac dane do pliku wcisnij 1.\n";
        cout << "Jesli chcesz wypisac  dane na konsoli wcisnij 2.\n";
        cout << "Jesli nic nie chcesz wcisnij 3\n";
        cout << "Jesli chcesz zakonczyc program wcisnij 4\n";
        cin >> wybor;
        switch (wybor) {
        case 1: {//tworzymy drugie opcje do wyboru
            cout << "podaj nazwe pliku: \n";
            cin >> nazwa_pliku;
            zapisz_do_pliku(nazwa_pliku, wynik_sortowania);
            break;
        }
        case 2: {
            int i = 0;
            while (i<liczba_liczb)
            {
                cout << wynik_sortowania[i] << " ";
                i++;
            }
            cout << "\n";
            break;
        }
        case 3:
        {

            break;
        }
        case 4:
            return 0;
            break;
        }
    }
return 0;
}
