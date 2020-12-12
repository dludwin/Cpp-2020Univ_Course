/*  Dominik Ludwin, lab1, 131609, 30.11.2020r. Zadanie6.
    Program ma dwie klasy, wykorzystuje dziedziczenie. Klasa osoba ma dwie zmienne chronione: nazwisko oraz liczbe lat.
    Poziom dostepu protected oznacza ze klasy pochodne maja dostep do tych zmiennych.
    Klasa pochodna to pracownik ktora na poziomie dostepu public dziedziczy po klasie osoba
    Gdyby klasa bazowa miala zmienne prywatne to nie mozna odziedzieczyc ich w zaden sposob, jedynie poprzez zaprzyjaznienie. 
    dziedziczenie w sposob public: public protected - / w sposob protected - protedted protected - / w sposob private: private private - . - to private bazy 
    Deklaracja uzywania using wprowadza kazda nazwana skladowa klasy bazowej do zasiegu klasy pochodnej
    Jezeli w jest wskaznikiem typu osoba a przypisany jest mu adres obiektu klasy pochodnej i jezeli nastepnie jesli chcemy uzyc metody 
    tego wskaznika klasy bazowej to nalezy dodac w klasie pochodnej wyrazenie using bazowa::nazwa_metody
    static_cast < nowy_typ > ( wyrazenie ) - zwraca wartosc nowego typu
*/ 
#include <iostream>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too

using namespace std;

class osoba{
public:
  osoba(string a1 = "", int a2 = 0): nazwisko_(a1), liczba_lat_(a2) {}
  void pokaz() const { cout << nazwisko_ << ", " << liczba_lat_ << "\n"; }
  string nazwisko() const { return nazwisko_;}
  int liczba_lat() const { return liczba_lat_;};
protected:
  string nazwisko_; 
  int liczba_lat_;
};

class pracownik : public osoba {
  public:
    pracownik(string a3 = "", int a4 = 0): stanowisko_(a3), placa_(a4) {}
    pracownik(string a1 = "", int a2 = 0, string a3 = "", int a4 = 0): osoba(a1,a2),stanowisko_(a3), placa_(a4) {}
    void pokaz() const { cout << nazwisko_ << ", " << liczba_lat_ << ", " << stanowisko_ << ", " << placa_ << "\n"; }
    using osoba::pokaz;
    string stanowisko() const { return stanowisko_;}
    int placa() const { return placa_;}
    pracownik(const pracownik& a1): osoba(a1.nazwisko_, a1.liczba_lat_), stanowisko_(a1.stanowisko_), placa_(a1.placa_) {}

    pracownik& operator=(const pracownik& a1){  
    if(this != &a1){                     
        nazwisko_ = a1.nazwisko_;
        liczba_lat_ = a1.liczba_lat_;
        stanowisko_ = a1.stanowisko_;
        placa_ = a1.placa_;
    }
    return *this;                     
  }
  protected:
    string stanowisko_; 
    int placa_;
};

int main(){
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif

  osoba os("Dolas", 26);
  os.pokaz();

  const pracownik pr1("Dyzma", 35, "mistrz", 1250.0);      
  cout << pr1.nazwisko() << "  " << pr1.liczba_lat()  << endl;
  cout << pr1.stanowisko() << "  " << pr1.placa() << endl;
 
  pracownik pr2(pr1);
  pr2.pokaz();
 
  pracownik pr3("Kos", 45, "kierownik", 2999.0);
  pr3.pokaz();
  pr3 = pr2;
  pr3.pokaz();

  osoba* w = &os;
  w->pokaz();
  w = &pr3;
  w->pokaz();

  static_cast<pracownik*>(w)->pokaz();

  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}