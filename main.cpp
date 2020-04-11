
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Adresat
{
    int id =0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};
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
string konwerjsaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}
void dodajOsobe(vector<Adresat>&adresaci)
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

    if (adresaci.empty() == true)
    {
        znajomi.id = 1;}
    else
    {
        znajomi.id = adresaci.back().id + 1; }

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
                adresat.imie = oddzielonaCzescDanychAdresata;
                break;
            case 3:
                adresat.nazwisko = oddzielonaCzescDanychAdresata;
                break;
            case 4:
                adresat.numerTelefonu = oddzielonaCzescDanychAdresata ;
                break;
            case 5:
                adresat.email = oddzielonaCzescDanychAdresata;
                break;
            case 6:
                adresat.adres = oddzielonaCzescDanychAdresata;
                break;
            }
            oddzielonaCzescDanychAdresata = "";
            numerPojedynczejDanejAdresata++;}}

   return adresat;
}
int wczytajAdresatowZPliku(vector<Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    //int osobaId = idAdresata + 1;
    fstream plikTekstowy;
    plikTekstowy.open("ksiazka_adresowa.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);

            adresaci.push_back(adresat);}

        plikTekstowy.close();}

     else
        cout<<"Nie mozna otwozyc pliku";

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

    int idAdresata = 0;
    vector<Adresat>adresaci;
    sprawdzIstnieniePlikuZewnetrznego();
    wczytajAdresatowZPliku(adresaci);
    char wybor;

    while (true)
    {
        system("cls");

        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyswietl wszystkie kontakty" << endl;
        cout << "3. Znajdz kontakt po imieniu" << endl;
        cout << "4. Znajdz kontakt po nazwisku" << endl;
        cout << "5. Edytuj Kontakty" << endl;
        cout << "6. Usun kontakt" << endl;
        cout << "9. Wyjdz" << endl;
        cin >> wybor;


        if (wybor == '1')
        {
             dodajOsobe(adresaci);
        }
        if (wybor == '2')
        {
           wyswietlWszystkichZnajomych(adresaci);
        }
        if (wybor == '3')
        {
           szukajImie(adresaci);
        }
        if (wybor == '4')
        {
           szukajNazwisko( adresaci);
        }
        if (wybor == '5')
        {
           edytujKontakt( adresaci);
        }
        if (wybor == '6')
        {
            usunKontakt(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
