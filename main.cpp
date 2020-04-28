#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};
struct Adresat
{
    int id =0 ,numerIdUzytkownika;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

string zaszyfrujSzyfremCezara(string tekst)
{
    const int przesuniecie = 3;
    const int iloscLiterWAlfabecie = ('z' - '0') + 1;

    for (int pozycja = 0; pozycja < tekst.length(); pozycja++)
    {
        if ( (tekst[pozycja] >= '0') && (tekst[pozycja] <= 'w') )
            tekst[pozycja]  = tekst[pozycja] + przesuniecie;

        else if ( (tekst[pozycja] >= 'x') && (tekst[pozycja] <= 'z') )
            tekst[pozycja] = tekst[pozycja] - iloscLiterWAlfabecie + przesuniecie;
    }

    return tekst;
}
string odszyfrujSzyfremCezara(string tekst)
{
    const int przesuniecie = 3;
    const int iloscLiterWAlfabecie = ('z' - '0') + 1;

    for (int pozycja = 0; pozycja < tekst.length(); pozycja++)
    {
        if ( (tekst[pozycja] >= '0') && (tekst[pozycja] <= '2') )
             tekst[pozycja] = tekst[pozycja] + iloscLiterWAlfabecie - przesuniecie;
        else if ( (tekst[pozycja] >= '3') && (tekst[pozycja] <= 'z') )
            tekst[pozycja]  = tekst[pozycja] - przesuniecie;
    }

    return tekst;
}
void sprawdzIstnieniePlikuZewnetrznego () {
    char nazwaPlikuKontaktow[ ] = "ksiazka_adresowa.txt";

    string linia="";
    fstream plik;
    plik.open(nazwaPlikuKontaktow, fstream::in | fstream::out);
    if (!plik) {
        cout << "Tworze plik kontaktow.";
        Sleep(1000);
        plik.open(nazwaPlikuKontaktow,  fstream::in | fstream::out | fstream::trunc);
        plik.close();
    } else {
        plik.close();
    }
}
int konwersjaStringNaInt(string liczba) {
    int liczbaInt;
    istringstream iss(liczba);
    iss >> liczbaInt;

    return liczbaInt;
}
string konwerjsaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}
void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    int idUzytkownika;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik uzytkownik;

    cout << "Podaj login uzytkownika: ";
    cin >> loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> login == loginUzytkownika)
        {
            cout << "Taki uztkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> loginUzytkownika;
        }
    }

    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    if (uzytkownicy.empty() == true)
    {
       uzytkownik.idUzytkownika = 1;
    }
    else
    {
       uzytkownik.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

   uzytkownik.login = loginUzytkownika;
   uzytkownik.haslo = hasloUzytkownika;

    uzytkownicy.push_back(uzytkownik);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += zaszyfrujSzyfremCezara(itr -> haslo) + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}
Uzytkownik pobierzDaneuzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami)
{
    Uzytkownik uzytkownik;
    int idUzytkownika;

    string oddzielonaCzescDanychUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int i = 0; i< daneUzytkownikaOddzielonePionowymiKreskami.length();i ++)
    {
        if (daneUzytkownikaOddzielonePionowymiKreskami[i] != '|')
        {
            oddzielonaCzescDanychUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[i];}
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.idUzytkownika  = atoi(oddzielonaCzescDanychUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.login = oddzielonaCzescDanychUzytkownika;
                break;
            case 3:
                uzytkownik.haslo =odszyfrujSzyfremCezara( oddzielonaCzescDanychUzytkownika);
                break;

            }
            oddzielonaCzescDanychUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;}}

   return uzytkownik;
}
int wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";
    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami))
        {
            uzytkownik = pobierzDaneuzytkownika(daneJednegoUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);}

        plikTekstowy.close();}

     else
        cout<<"Nie mozna otwozyc pliku"<<endl;


}
int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = false;
    int proby = 0;
    cout << "Podaj login uzytkownika: ";
    cin >>  loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> login == loginUzytkownika)
        {
            znalezionyUzytkownik = true;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ":";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Zalogowales sie."<<endl;
                    return itr -> idUzytkownika;
                }
            }
            if( proby == 3)
            {
                cout << "Podales 3 razy bledne haslo.Poczekaj przez 3 sekundy przed kolejna proba." << endl;
            }
        }
    }

    if(znalezionyUzytkownik==false)
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1500);
    return 0;
}
void zapiszDaneUzytkownikaDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out| ios::trunc);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += zaszyfrujSzyfremCezara(itr -> haslo) + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}
void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string hasloUzytkownika;
    int pozycjaZnalezionejOsoby = 0;
    cout << "Podaj nowe haslo: ";
    cin >> hasloUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[pozycjaZnalezionejOsoby].haslo = hasloUzytkownika;
            cout << "Haslo zostalo zmienione"<< endl;
            Sleep(1500);
            zapiszDaneUzytkownikaDoPliku(uzytkownicy);
        }
        pozycjaZnalezionejOsoby++;
    }
}
string pobierzLiczbe(string tekst, int pozycjaZnaku) {
    string liczba = "";
    while(isdigit(tekst[pozycjaZnaku]) == true)
    {
        liczba += tekst[pozycjaZnaku];
        pozycjaZnaku ++;
    }
    return liczba;
}
int pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = konwersjaStringNaInt(pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}
int indexOstatniegoAdresata()
{
    string daneJednegoAdresataOddzielonePionowymiKreskami;
    fstream plikTekstowy;
    int ostatniIndex=0 ;
    plikTekstowy.open("ksiazka_adresowa.txt", ios::in);


    if (plikTekstowy.good() == true)
    {

        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            ostatniIndex = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami);
        }

        plikTekstowy.close();
    }
    else
    {
        cout<<"Nie mozna otwozyc pliku";

    }
    return ostatniIndex +1;
}

void dodajOsobe(vector<Adresat>&adresaci, int idZalogowanegoUzutkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    string liniaAdresowa ="";

    Adresat znajomi;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    znajomi.id = indexOstatniegoAdresata();
    znajomi.numerIdUzytkownika = idZalogowanegoUzutkownika;
    znajomi.imie = imie;
    znajomi.nazwisko = nazwisko;
    znajomi.numerTelefonu = numerTelefonu;
    znajomi.email = email;
    znajomi.adres = adres;

    adresaci.push_back(znajomi);

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        liniaAdresowa+=konwerjsaIntNaString(znajomi.id) + '|';
        liniaAdresowa+=konwerjsaIntNaString(znajomi.numerIdUzytkownika) + '|';
        liniaAdresowa+=znajomi.imie + '|';
        liniaAdresowa+=znajomi.nazwisko + '|';
        liniaAdresowa+=znajomi.numerTelefonu + '|';
        liniaAdresowa+=znajomi.email + '|';
        liniaAdresowa+=znajomi.adres + '|';

        plik << liniaAdresowa << endl;
        liniaAdresowa ="";


        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);}
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;}
}
Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    int idAdresata;

    string oddzielonaCzescDanychAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int i = 0; i< daneAdresataOddzielonePionowymiKreskami.length();i ++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[i] != '|')
        {
            oddzielonaCzescDanychAdresata += daneAdresataOddzielonePionowymiKreskami[i];}
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.id  = atoi(oddzielonaCzescDanychAdresata.c_str());
                break;
            case 2:
                adresat.numerIdUzytkownika  = atoi(oddzielonaCzescDanychAdresata.c_str());
                break;
            case 3:
                adresat.imie = oddzielonaCzescDanychAdresata;
                break;
            case 4:
                adresat.nazwisko = oddzielonaCzescDanychAdresata;
                break;
            case 5:
                adresat.numerTelefonu = oddzielonaCzescDanychAdresata ;
                break;
            case 6:
                adresat.email = oddzielonaCzescDanychAdresata;
                break;
            case 7:
                adresat.adres = oddzielonaCzescDanychAdresata;
                break;
            }
            oddzielonaCzescDanychAdresata = "";
            numerPojedynczejDanejAdresata++;}}

   return adresat;
}
int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami) {
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika =konwersjaStringNaInt(pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}
int wczytajAdresatowZPliku(vector<Adresat> &adresaci,int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open("ksiazka_adresowa.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami)){
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);

            adresaci.push_back(adresat);}}

            plikTekstowy.close();}


        else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

}
void wyswietlWszystkichZnajomych(vector <Adresat> &adresaci)
{
    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        cout << endl;
        cout << "Numer ID : " << itr -> id << endl;
        cout << "Imie :" <<itr -> imie <<endl;
        cout << "Nazwisko: "<<itr -> nazwisko << endl;
        cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
        cout << "Email: " << itr -> email << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
    }
    system("pause");
}
void szukajNazwisko(vector <Adresat> &adresaci)
{
    string poszukiwaneNazwisko;
    bool wynik = false;
    cout << endl << "Podaj nazwisko adresata, ktorego mamy wyszukac: ";
    cin >> poszukiwaneNazwisko;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> nazwisko == poszukiwaneNazwisko)
        {
            wynik = true;
            cout << endl;
        cout << "Numer ID : " << itr -> id << endl;
        cout << "Imie :" <<itr -> imie <<endl;
        cout << "Nazwisko: "<<itr -> nazwisko << endl;
        cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
        cout << "Email: " << itr -> email << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
        }
    }

    if(wynik ==false)
    {
        cout << endl << "Nie znaleziono osoby o tym nazwisku." << endl << endl;
    }
    system("pause");
}
void szukajImie(vector <Adresat> &adresaci)
{
    string poszukiwaneImie;
    bool wynik = false;
    cout << endl << "Podaj Imie adresata, ktorego mamy wyszukac: ";
    cin >> poszukiwaneImie;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> imie == poszukiwaneImie)
        {
            wynik = true;
            cout << endl;
        cout << "Numer ID : " << itr -> id << endl;
        cout << "Imie :" <<itr -> imie <<endl;
        cout << "Nazwisko: "<<itr -> nazwisko << endl;
        cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
        cout << "Email: " << itr -> email << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
        }
    }

    if(wynik ==false)
    {
        cout << endl << "Nie znaleziono osoby o tym nazwisku." << endl << endl;}

    system("pause");
}
void zapiszDoPliku(vector <Adresat> &adresaci)
{
    fstream plik;

    string liniaAdresowa = "";
    plik.open("ksiazka_adresowa.txt", ios::out | ios::trunc);
    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaAdresowa += konwerjsaIntNaString(itr -> id) + '|';
            liniaAdresowa += konwerjsaIntNaString(itr -> numerIdUzytkownika) + '|';
            liniaAdresowa += itr -> imie + '|';
            liniaAdresowa += itr -> nazwisko + '|';
            liniaAdresowa += itr -> numerTelefonu + '|';
            liniaAdresowa += itr -> email + '|';
            liniaAdresowa += itr -> adres + '|';

            plik << liniaAdresowa << endl;
            liniaAdresowa = "";}

    plik.close();

        cout << "Dane zostaly zapisne." << endl;

    system("pause");}

    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");}

}
void edytujKontakt (vector <Adresat> &adresaci)
{

    string  imie,nazwisko,numerTelefonu, email, adres,linia;
    char wybranaPozycjaMenu;
    int poszukiwanyNumerID;
    bool wynik = false;
    int pozycjaZnalezionejOsoby = 0;


    cout << "Wyszukanie adresata. Podaj ID: ";
    cin >> poszukiwanyNumerID;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == poszukiwanyNumerID)
        {
            wynik = true;
            system("cls");
            cout << "Edycja kontaktu." << endl;
            cout << "Imie :"<<itr -> imie <<endl;
            cout << "Nazwisko :" <<itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: "  << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj imie." << endl;
            cout << "2.Edytuj nazwisko." << endl;
            cout << "3.Edytuj numer telefonu." << endl;
            cout << "4.Edytuj adres mailowy." << endl;
            cout << "5.Edytuj adres kontaktowy." << endl;
            cout << "6.Edytuj wszystkie informacje." << endl;
            cout << "9.Zakoncz edycje." << endl<<endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                cout << "Podaj nowe imie: ";
                cin.sync();
                getline(cin,imie);
                adresaci[pozycjaZnalezionejOsoby].imie = imie;
                break;
            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                getline(cin,nazwisko);
                adresaci[pozycjaZnalezionejOsoby].nazwisko = nazwisko;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                adresaci[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;

                break;
            case '4':
                cout << "Podaj nowy adres mailowy: ";
                cin >>  email;
                adresaci[pozycjaZnalezionejOsoby].email = email;

                break;
            case '5':
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);
                adresaci[pozycjaZnalezionejOsoby].adres = adres;

                break;
            case '6':
                cout << "Podaj nowe imie: ";
                cin.sync();
                getline(cin,imie);
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                getline(cin,nazwisko);
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                cout << "Podaj nowy adres mailowy: ";
                cin >>  email;
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);
                adresaci[pozycjaZnalezionejOsoby].imie = imie;
                adresaci[pozycjaZnalezionejOsoby].nazwisko = nazwisko;
                adresaci[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                adresaci[pozycjaZnalezionejOsoby].email = email;
                adresaci[pozycjaZnalezionejOsoby].adres = adres;
                break;

            case '9':
                system("pause");
                break;
            }
            cout << "Edycja kontaktu przebiegla pomyslnie." << endl << endl;
            zapiszDoPliku(adresaci);
        }

        pozycjaZnalezionejOsoby++;}

    if(wynik == false)
        {
            cout<<endl << "Nie ma takiego adresata" << endl << endl;}

     system("pause");
}
char wczytajZnak() {
        string wejscie = "";
        char znak  = {0};

        while (true)
        {
            cin.sync();
            getline(cin, wejscie);

            if (wejscie.length() == 1)
            {
            znak = wejscie[0];
            break;
            }
            cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
        }
        return znak;
}

void usunKontakt (vector <Adresat> &adresaci)
{
    int poszukiwanyNumerID ;
    int idAdresata;

    char znak;
    bool wynik =false;
    cout << "Wyszukiwanie kontaktu. Podaj numer ID adresata: ";
    cin >> poszukiwanyNumerID;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {

        if (itr -> id == poszukiwanyNumerID)
        {
            wynik = true;
            cout << endl;
            cout << "Numer ID : " << itr -> id << endl;
            cout << "Imie :" <<itr -> imie <<endl;
            cout << "Nazwisko: "<<itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Email: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;


            cout<< "Wcisnij klawisz 't' by powierdzic usuniecie kontaktu"<<endl;
            znak = wczytajZnak();
            if(znak == 't')
            {

            itr = adresaci.erase(itr);
            cout << "Kontakt zostal usuniety." << endl << endl;

            zapiszDoPliku(adresaci);
            break;}
       else if (znak !='t')
        {
            cout <<"kontakt nie zostal usuniety"<<endl;
            system("pause");
            break;}}}

      if(wynik == false)
    {
        cout<<endl<< "Nie ma takiego kontaktu "<<endl;

        system("pause");}

}
int main()
{
    int idZalogowanegoUzytkownika = 0;
    int idAdresata = 0;

    vector <Uzytkownik> uzytkownicy;
    vector<Adresat>adresaci;

    sprawdzIstnieniePlikuZewnetrznego();
    wczytajUzytkownikowZPliku(uzytkownicy);

    char wybor;

    while (1)
    {

        if(idZalogowanegoUzytkownika == 0)
        {
            cout <<endl<< "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "9.Zamknij program" << endl;
            cin >> wybor;

            switch(wybor)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                adresaci.clear();
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                wczytajAdresatowZPliku(adresaci,idZalogowanegoUzytkownika);

                break;
            case '9':
                exit(0);
                break;
            }
        }
     else if (idZalogowanegoUzytkownika>0)

    {
        system("cls");

        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyswietl wszystkie kontakty" << endl;
        cout << "3. Znajdz kontakt po imieniu" << endl;
        cout << "4. Znajdz kontakt po nazwisku" << endl;
        cout << "5. Edytuj Kontakty" << endl;
        cout << "6. Usun kontakt" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;
        cin >> wybor;



        switch(wybor)
        {
            case '1':
                dodajOsobe(adresaci,idZalogowanegoUzytkownika);
                break;
            case'2':
                 wyswietlWszystkichZnajomych(adresaci);
                break;
            case '3':
                 szukajImie(adresaci);
                break;
            case '4':
                szukajNazwisko( adresaci);
                break;
            case '5':
               edytujKontakt( adresaci);
                break;
            case '6':
                 usunKontakt(adresaci);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '9':
                idZalogowanegoUzytkownika = 0;
                break;
        }

    }
    }
    return 0;
}
