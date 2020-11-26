#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool istniejeTakaTablica=false; //zmienna sluzaca do przechowywania informacji o tym czy dla dannej tablicy istnieja podtablice
bool wyswietlono=false; // zmienna pomocnicza pozwalajaca na jednorazowe wyœwietlenie informacji
int rozmiar=0;

const string NazwaPliku="wyniki.txt";

int* pobierzTablice()// Funkcja sluzaca do stworzenia i wypelnienia tablicy
{
    cout << "Ile elementow ma posiadac tablica? ";
     cin >> rozmiar;
    while(cin.fail() || rozmiar<=0) { // sprawdzamy czy dane sa wczytane niepoprawnie, jesli sa niepoprawne, wykonujemy zawartosc petli
         cout << "Blad! podaj poprawna liczbe!" << endl;
         cin.clear(); // czyscimy flage bledu na cin
         cin.ignore(256,'\n'); // ignorujemy wszystkie bledne dane (w tym przypadku maksymalnie 256 znaków) az do napotkania znaku nowej lini, czyli klawisza enter
         cin >> rozmiar; // wprowadzamy wartosc ponownie
     }

    int *tablica = new int[rozmiar];

    for(int i=0;i<rozmiar;i++)// wypelnianie stworzonej tablicy
    {
        cout << "\nPodaj element nr." << i+1 <<": ";
        cin >> tablica[i];
        while(cin.fail()) {// takie samo sprawdzanie jak wyzej, ale bez warunku ze liczba musi byc wieksza od zera
            cout << "Blad! podaj liczbe!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> tablica[i];
        }
    }
    return  tablica;
}
void znajdzPodtablice(int tab[], int n)//funkcja znajdujaca podtablice i wypisujaca je do pliku
{
    ofstream plik;
    plik.open (NazwaPliku);

    plik << "\n\nGlowna tablica: [ ";
    for(int i=0; i<n;i++)// wypisujemy po kolei glowna tablice
    {
        if(i+1==n) // jezli kolejny indeks nie istnieje w tej tablicy, przy aktualnej wartosci nie dodajemy przecinka ale ']' i lamiemy wiersz
        {
            plik << tab[i] <<" ]\n\n";
        }
        else
        {
            plik << tab[i] << ", ";
        }
    }

    for (int i = 0; i < n; i++)// petla przechodzi przez wszystkie elementy tablicy zaczynajac od pierwszego o indeksie 0
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += tab[j];//dodajemy wartosc elementu 'j' tablicy do zmiennej trzymajacej sume

            if (sum == 0)
            {
                istniejeTakaTablica=true;
                if(!wyswietlono) // jednorazowo wyœwietlamy wiadomosc ze ta tablica ma przynajmniej jedna podtablice której suma elementów jest równa 0
                {
                    plik << "Istnieja podtablice, ktorych suma wynosi 0\n";
                    wyswietlono=true;// ustawiamy wartosc zmiennej na true, co zapobiegnie wyœwietleniu tej wiadomoœci przy znalezieniu kolejnej podtablicy
                }

                plik << "Podtablica: [" << i << ".." << j << "] czyli: ";// wyœwietla przedzial indeksów glównej tablicy w którym zawarta jest podtablica

                plik << "[ ";
                for(int l=i; l<=j;l++)// przechodzimy przez podany wyzej przedzial i wyswietlamy kazdy element
                {
                    if(l+1>j)
                    {
                        plik << tab[l] <<" ]\n"; // jezli kolejny indeks nie istnieje w tej tablicy, przy aktualnej wartosci nie dodajemy przecinka ale ] i lamiemy wiersz
                    }
                    else
                    {
                        plik << tab[l] << ", ";
                    }
                }

            }
        }
    }
    if(!istniejeTakaTablica) //Jezeli nigdy nie ustawiono flagi na true oznacza to ze nie istnieja podtablica o sumie elementow rownej 0
    {
        plik << "Nie istnieja podtablice, ktorych suma wynosi 0\n";
    }
    plik.close();
}

int main()
{
    int *tablica =  pobierzTablice();
    znajdzPodtablice(tablica, rozmiar);// przekazujemy tablice do funkcji która znajdzie i wpisze do pliku jej podtablice
    delete [] tablica; // usuwamy tablice dynamiczna

    //wypisanie na ekran
    ifstream wyniki(NazwaPliku); // otwieramy plik do odczytu

    if (wyniki.is_open())
    {
        cout << wyniki.rdbuf();
        wyniki.close();
    }
    else//Jezli nie udalo sie otworzyc pliku wyswietlamy blad
    {
        cout << "Nastapil blad przy probie otwarcia pliku " << NazwaPliku << " przechowujacego wyniki dzialania programu!";
    }

    return 0;
}
