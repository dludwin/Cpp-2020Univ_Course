/* Dominik Ludwin, lab.1, 131609, 9.11.2020
 Program posiada dwie klasy: adres oraz osoba. Klasa osoba posiada konstruktor bezparametrowy oraz parametrowy, stala metode view
 ktora zwraca referencje ostream i sluzy do wypisania danych na ekran, zaprzyjazniony operator<< wypisania na ekran ktory pobiera
 referencje do ostream oraz referencje do stalego obiektu klasy adres. Jest tez zaprzyjaznienie calej klasy osoba w celu wywolania 
 funkcji miasto(). Klasa osoba posiada w swoich zmiennych prywatnych wskaznik do
 adresu, dodatkowo posiada operator przypisania kopiujacego i jezeli adresy porownywanych obiektow sa rozne to aktualna pamiec zostaje
 zwolniona i przypisana nowa, dalej nastepuje kopiowanie wartosci. Jesli porównywane obiekty są takie same, zwraca referencje do samego siebie
 Metoda miasto() zmienia wartosc stringa mia w prywatnej zmiennej klasy a mianowicie wskazniku do klasy adres
 Klasa posiada rowniez destruktor ktory zwalnia pamiec przechowujacy adres
*/
#include <iostream>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too
#include <string>

using namespace std;

class adres{
  string mia, ul;
  int nr;
public:

  adres(): mia(""),ul(""),nr(0){}    // konstruktor bezparametrowy, przypisuje zmiennym prywatnym dane zerowe            

  adres(const string& a1, const string& a2, int a3): mia(a1), ul(a2), nr(a3){}     // konstruktor z parametrami oraz lista inicjacyjna zmiennych prywatnych

  ostream& view(ostream& out) const{                               // view jest stala metoda ktora zwraca referencje do ostream, sluzy do wypisania danych na ekran
    return out << mia << ", " << ul << ", " << nr << '\n';
  }

  friend 
  ostream& operator<< (ostream& out, const adres& r);              

  friend class osoba;                                             // zaprzyjaznienie calej klasy osoba w celu wywolania funkcji miasto()

};
ostream& operator<< (ostream& out, const adres& r){                       
  return r.view(out);                                             // wywolanie metody view referencji stalego obiektu klasy adres 
}

class osoba{
  string im;
  int wi;
  adres* adr;
public:
 
  osoba():im(""),wi(0),adr(new adres){}
  
  osoba(const string& a1, int a2, const adres& a3):im(a1), wi(a2), adr(new adres(a3)){}


  osoba(const osoba& a1): im(a1.im), wi(a1.wi),  // konstruktor kopiujacy
        adr(new adres(*a1.adr)) {}


  osoba& operator=(const osoba& a1){     // operator przypisania kopiujacego
    if(this != &a1){                     // jeżeli adresy obiektów są różne
        delete adr;
        im = a1.im;
        wi = a1.wi;
        adr = new adres(*a1.adr);       // alokacja nowego miejsca w pamieci
    }
    return *this;                       // Porównywane obiekty są takie same, zwraca referencje do samego siebie
  }
 
  ~osoba(){ delete adr; }

  string& miasto() { return adr->mia ;}             

friend ostream& operator<< (ostream& out, const osoba& r);
 
};
ostream& operator<< (ostream& out, const osoba& r){
 
  return out << r.im << ", " << r.wi << ", " << *r.adr ;
}

int main(){
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); 
  #endif

adres* wsk = new adres("Częstochowa", "Dąbrowskiego", 73);

cout <<  wsk << '\n';
cout << *wsk << '\n';

adres a1(*wsk);
delete wsk;
wsk=nullptr;

const adres* wsk1 = new adres("Łódź", "Piotrkowska", 33);

cout << a1 << '\n';
cout << *wsk1 << '\n';

adres a2;
cout << a2 << '\n';
a2 = a1;
cout << a2 << '\n';

osoba os1("Ala", 25, *wsk1);
delete wsk1;

cout << os1 << '\n';
osoba os2(os1);

os1.miasto()="Zmieniono miasto osoby 1.";
cout << os2 << '\n';

osoba os3;
cout << os3 << '\n';
os3 = os2;

os1.miasto()="Drugi raz zmieniono miasto osoby 1.";
cout << os3 << '\n';
}






