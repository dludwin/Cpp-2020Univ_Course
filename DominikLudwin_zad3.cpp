// 14.11.2020r Dominik Ludwin lab1 131609
/*  Program posiada dwie klasy: punkt oraz wielobok. Klasa punkt posiada dwie zmienne prywatne, konstruktor domyslny oraz z parametrami.
    Posiada metody dostepowe do zmiennych prywatnych. Ma metode dlugosc ktora pobiera referencje do stalego obiektu klasy punkt, 
    oraz zaprzyjazniony operator wypisania. Klasa wielobok w konstruktorze z parametrami sprawdza rozmiar zajmowany przez punkty poprzez odjecie 
    jednostek pamieci punktu dalszego od punktu blizszego, a nastepnie przypisuje 
    nowa pamiec lub wartosc zero, nastepnie petla przypisania i uzyskanie wartosci przez wyluskanie *(..) oraz iteracja po nastepnych adresach.
    Operator rownowaznosciowy dziala bardzo podobnie, lecz dodatkowo sprawdza czy obiekty sa sobie rowne i na tej podstawie podejmuje decyzje
    Operator[] sprawdza czy podany indeks jest poza zakresem tablicy, wyrzuca string lub zwraca wartosc indeksu poprzez referencje do danego obiektu klasy
    Wystepuja takze metody obwod, ilosc a takze destruktor - usuwanie miejsca z pamieci w tym przypadku calej tablicy
*/

#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too
#include <iostream>
#include <math.h>
using namespace std;

class punkt {
    double x_, y_;

    public: 
      punkt(): x_(0),y_(0) {}
      
      punkt(double a1, double a2): x_(a1), y_(a2) {} 

      double& x() { return x_; }
      double& y() { return y_; }

      double odleglosc(const punkt& p);

      friend 
      ostream& operator<< (ostream& out, const punkt& r);     
};

ostream& operator<<(ostream& out, const punkt& r){
  return out << r.x_ << ", " << r.y_;
}

double punkt::odleglosc(const punkt& p) {
  return sqrt(pow(x_ - p.x_, 2) + pow(y_ - p.y_, 2));
}

class wielobok{  
  size_t roz;  
  punkt* wsk;  
                     
public:
  wielobok():roz(0), wsk(0){}
  
  wielobok(const punkt* b, const punkt* e):roz(e-b>0 ? e-b:0), wsk( roz?new punkt[roz]:0 ){  
     for(size_t i = 0; i < roz; i++)
      wsk[i] = *(b+i);
  }   

  wielobok(const wielobok& r):roz(r.roz), wsk(new punkt[r.roz] ){
     for(size_t i = 0; i < roz; i++)
      wsk[i] = *(r.wsk + i);
  }   
  wielobok& operator=(const wielobok&r){
    if(this != &r){
        delete wsk;
        roz = r.roz;
        wsk = roz? new punkt[roz]:0;
        for(size_t i = 0; i < roz; i++)
          wsk[i] = r.wsk[i];
    }
    return *this;
    }
    
    punkt& operator[](size_t i){
      if(i<0 || i >= roz) throw string("Indeks poza zakresem\n");
      return wsk[i];
    }

    const punkt& operator[](size_t i) const{
      if(i<0 || i >= roz) throw string("Indeks poza zakresem\n");
      return wsk[i];
    }

  double obwod() const;

  const unsigned int ilosc() const{ return roz;}

  friend 
  ostream& operator<< (ostream& out, const wielobok& r); 

  ~wielobok(){ delete[] wsk;}

};
 ostream& operator<<(ostream& out, const wielobok& r){
   out << r.roz << " ";
   for (size_t i = 0; i < r.roz; i++)
      out << "[" << r.wsk[i].x() << "," << r.wsk[i].y() << "]"; 
   return out;
}

double wielobok::obwod() const{
    double tmp = 0;
    for (size_t i = 0; i < roz ; i++) {
        tmp += wsk[i].odleglosc(wsk[i+1]); 
    }
    return tmp;
  }

int main(){
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif
  punkt p(2, 3);
  cout << p.x() << ' ' << p.y() << '\n';
  p.x() = 1;
  p.y() = 1;
  cout << p.x() << ' ' << p.y() << '\n';
  cout << p.odleglosc(punkt()) << "\n\n";
  const punkt t[] = { punkt(0, 0), punkt(0, 1), punkt(1, 1), punkt(1, 0) };
  for(size_t i=0; i < sizeof(t)/sizeof(punkt); ++i)
    cout << i+1 << ")  " << t[i] << endl;

  cout << "\n*****\n";
  wielobok w1(t, t+4);
  cout << w1.obwod() << '\n';

  w1[1] = punkt(0.5, 0.5);
  cout << w1.obwod() << '\n';
  cout << "***\n\n";  
 

  wielobok w2;
  w2 = wielobok(t, t+3);
  cout << w2.obwod() << '\n';

  for (size_t i = 0; i < w2.ilosc(); ++i)
    cout << w2[i].x() << ' ' << w2[i].y() << '\n';

  cout << "\n*****\n";
  wielobok w3(w2);
  w3[1] = punkt(0, -1);
  w3[2] = punkt(-1, -1);
  for (size_t i = 0; i < w3.ilosc(); ++i)
    cout << w3[i] << endl;
  cout << "***\n\n";

  cout << "\n*****\n";
  cout << w2 << "***\n" << w3;
  cout << "*****\n\n";

  cout << w2.obwod() - w3.obwod() << "\n\n";
  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}