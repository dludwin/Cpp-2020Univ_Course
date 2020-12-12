// Dominik Ludwin, lab1, 131609, zadanie 7, 12.12.2020r.

#include <iostream>
#include <typeinfo>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too

using namespace std;

class pomiar{
 protected:
  string opis;
  size_t roz;
  double* tab;    // Pamiętaj, że zmienna tab jest wskaźnikiem mogącym przechowywać adres obiektu typu double.
                  // W tym przypadku będzie to adres pierwszego elementu dynamicznej tablicy typu double.

 public:
  pomiar(): roz(0),tab(nullptr) {}                                  // Czy rozumiesz co to znaczy, że wskaźnik tab ma zostać zainicjowany wartością zero? 
  pomiar(const string& a):opis(a), roz(0),tab(nullptr){}            // Odp: Tak. Wskaznik nie zawiera adresu zadnej zmiennej. Jezeli rozmiar jest 0 to wskaznik tab nie moze zawierac adresu zmiennej
  pomiar(const string& a, const double* p, const double* k):        // Zmienna p wskazuje na początek, a zmienna k na koniec (adres za ostatnim elementem) tablicy,
     opis(a), roz(k-p>0 ? k-p:0), tab(roz? new double[roz]:0)  {    // z której dane mają być przepisane do tablicy tworzonego obiektu.
      for (size_t i=0; i<roz;i++){
        tab[i] = *(p+i);
      } 
     }               
                                                            
  pomiar(const pomiar& a): opis(a.opis), roz(a.roz), tab(new double[a.roz] ){
     for(size_t i = 0; i < roz; i++)
      tab[i] = *(a.tab + i);
  }                
                                
 pomiar& operator=(const pomiar& a){
  if(this != &a){
      delete []tab;
      roz = a.roz;
      opis = a.opis;
      tab = roz? new double[roz]:0;
      for(size_t i = 0; i < roz; i++){
         tab[i] = a.tab[i];
      }
  }
  return *this;
 }              

  pomiar& operator+=(const string& r){     // += to operator, który modyfikuje lewy argument. W przypadku, gdy prawym argumentem jest obiekt klasy string ten operator modyfikuje tylko pole opis.
      opis = opis + " " + r;
      return *this;
    }  
  pomiar& operator+=(const double& r){     // Jeśli jednak prawym argumentem jest liczba to każdy z elementów tablicy jest modyfikowany o tę liczbę.
    for(size_t i = 0; i < roz; i++){
      tab[i] += r; 
    }
    return *this;
  }   

  pomiar& operator*=(const double& r){      // Ten operator działa analogicznie jak pomiar& operator+=(const double& r).
    for(size_t i = 0; i < roz; i++){
      tab[i] *= r; 
    }
    return *this;
  }   
 
   virtual ostream& pokaz(ostream& a) const = 0;

  virtual double oblicz_wynik() const = 0;    // To jest metoda czysto wirtualna tzn taka, dla której nie jest dostarczana implementacja (nie ma ciała funkcji).
                                             // Jeśli w klasie zadeklarowano choćby jedną funkcję czysto wirtualną to klasa taka jest klasą abstrakcyjną. Nie można definiować samodzielnie istniejących obiektów tej klasy.
                                             // Obiekty takiej klasy mogą istnieć jedynie jako podobiekty klas pochodnych. W klasie pochodnej należy jednak dostarczyć implementacje tych funkcji.
                                             // Klasa, która nie dostarcza implementacji metody wirtualnej dziedziczy metodę czysto wirtualną i staje się tym sposobem również klasą abstrakcyjną.
                                             // Częstym błędem popełnianym przez niewprawnych programistów jest dostarczanie implementacji funkcji podobnych do tej, którą zadeklarowano jako czysto wirtualną.
                                             // Wystarczy np. zamiast double oblicz() const {...} w klasie pochodnej zdefiniować funkcję double oblicz(){...} i wszystko przestaje się kompilować.

  virtual ostream& pokaz_opis(ostream&) const = 0;

  virtual ~pomiar(){ delete[]tab; }          // Jest zasada, że jeśli w klasie bazowej zadeklarowano choćby jedną funkcję wirtualną
                                             // to klasa powinna dostarczać także DEFINICJĘ wirtualnego destruktora
                                             // Przeanalizuj przykład klas B1, P1 i B2, P2 omawiany w drugiej części wykładu .

  friend
  ostream& operator<< (ostream& a, const pomiar& r);

  friend
  pomiar& operator+(const string& la, pomiar& pa);
};
 ostream& operator<< (ostream& a, const pomiar& r){ return r.pokaz(a) ;} // Polimorficznymi mogą być jedynie funkcje w hierarchii klas.
                                                                        // Funkcja realizująca przeciążenie operatora<< nigdy nie może być jednak metodą klasy.
                                                                        // Można jednak "zmusić" ten operator do dzałania polimorficznego - poprzez wywołanie (w ciele funkcji) polimorficznej metody.
pomiar& operator+(const string& la, pomiar& pa){   // ("[kg] " + *tab[0]) 
  pa.opis = la + pa.opis;
  return pa;
}
// Klasy ciezar i temp nie mają żadnych pól.
// Dostarczają jedynie odpowiedni zbiór funkcji.
class ciezar : public pomiar {
  public:

  ciezar(): pomiar() {}
  ciezar(const string& a): pomiar(a){}
  ciezar(const string& a, const double* p, const double* k):  pomiar(a,p,k){} 
 
  ostream& pokaz_opis(ostream& out) const{
       return out << "Ciężar - \"" + opis + "\"";
  };

  double oblicz_wynik() const{
    double sum = 0;
    
    if(roz == 0) throw string ("brak danych");
    for(size_t i = 0; i < roz; i++){
      sum += tab[i];
    }
    return sum;
  }
  ostream& pokaz(ostream& a) const
  {
    return pokaz_opis(a);
  }
};

class temp : public pomiar {
  public:

  temp(): pomiar() {}
  temp(const string& a): pomiar(a){}
  temp(const string& a, const double* p, const double* k):  pomiar(a,p,k){} 

    ostream& pokaz_opis(ostream& out) const{
    return out << "Temperatura - \"" + opis + "\"";
  };

  double oblicz_wynik() const{
    double sum = 0;
    if(roz == 0) throw string("brak danych");

    for(size_t i = 0; i < roz; i++){
      sum += tab[i];
    }
    return sum/roz;

  }
  
  ostream& pokaz(ostream& a) const
  {
    return pokaz_opis(a) ;
  }
};

void pokaz_wszystko(ostream& cout, const pomiar& t){   // zdefiniuj tę funkcję. Pamiętaj o sytuacjach wyjątkowych

  if(string(typeid(t).name()) == "6ciezar"){
   t.pokaz(cout);
   cout << ", WYNIK : ";
   try{ 
     cout << t.oblicz_wynik(); 
   }
   catch(const string& er){
     cerr << er;
   }
    cout << "\n";
  }
  else if(string(typeid(t).name()) == "4temp" ){
   t.pokaz(cout);
   cout << ", WYNIK : ";
   try{ 
     cout << t.oblicz_wynik(); 
   }
   catch(const string& er){
     cerr << er;
   }
    cout << "\n";
  }
  else {
    cout << "Zly typ zmiennej";  
  }
  
}


int main()try{
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif

  double dane[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8 };

  pomiar* tab[5] {};   // pomyśl jakiego typu ma być zmienna tab - Typ - wskaznik do obiektu klasy pomiar. Tablica zainicjowana zerami o rozmiarze 5.
 
  tab[0] = new ciezar("cytryny") ;
  tab[1] = new temp("poranki", dane+3, dane+6);
  tab[2] = new ciezar("jabłka", dane+1, dane+3) ;
  tab[3] = new temp("wieczory", dane+1, dane+9);
  tab[4] = new ciezar;
 
  cout << "********** 1 **********" << endl;
  for (int i=0; i<5; ++i)
    cout << *tab[i] << endl ;


  cout << "\n********** 2 **********" << endl;

  for (int i=0; i<5; ++i)
    try{    
      cout << *tab[i] << ", WYNIK : " << tab[i]->oblicz_wynik() << endl ;
    }
    catch (const string& a){
     cout << a << endl;
    }


  cout << "\n********** 2a *********" << endl;
  *tab[0] = ciezar("cytryny", dane, dane+1);
  *tab[0] = ("[kg] " + *tab[0]) += "po wyprzedaży";
  *tab[1]  = "Wiosenne " + *tab[1];
  *tab[2] += "ANTONÓWKI suszone";
  *tab[2] *= 0.1;
  *tab[3] += "po korekcie odczytu";
  *tab[3] += 0.1;

  for (int i=0; i<5; ++i)
    try{    
      cout << *tab[i] << ", WYNIK : " << tab[i]->oblicz_wynik() << endl ;
    }
    catch (const string& a){
     cout << a << endl;
    }

  for (int i=0; i<5; ++i)
    delete tab[i];


  cout << "\n********** 3 **********" << endl;  
  const ciezar test1("gruszki", dane, dane+9);
  const temp test2;

  //w odpowiednim miejscu zdefiniuj funkcję pokaz_wszystko(...)

  pokaz_wszystko(cout, test1);
  pokaz_wszystko(cout, test2);
  pokaz_wszystko(cout, ciezar());
  pokaz_wszystko(cout, temp("Jakaś tam", dane+8, dane+9));

  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}

catch(...){
  cout << "Ooooops!\nCoś poszło nie tak.\n";
}