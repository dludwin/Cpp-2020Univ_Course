/*  Dominik Ludiwn, lab1, 131609, 17.11.2020r. Zadanie4 - Program posiada jedna klase punkt ktora ma jedna zmienna prywatna, trzyelementowa tablice typu double
    Posiada konstruktor domyslny, z parametrami a takze poprzez przekazanie stalego wskaznika typu double a nastepnie inicjalizacja poprzez curly braces
    Operator wypisania, operator wpisania nie moze byc const, poniewaz modyfikuje wartosci. Operator tablicowy, jest stala metoda ktora zwraca stala referencje do double
    Sprawdza czy int jest w zakresie tablicy, jesli nie to wyrzuca string lub zwraca element. Sa rowniez operatory +,-,/, mnozenie obiekt * liczba, i zarowno
    liczba * obiekt jako przeciazony operator (nie metoda klasy). Jest rowniez operator mniejsci ktory porownuje obiekty za pomoca tuple->tie oraz zwraca bool.
    Operator rownosci porownuje kazdy element w obu obiektach. T3 to stala metoda zwraca staly wskaznik do tablicy typu double
*/

#include <iostream>
#include <cmath>
#include <tuple>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too

using namespace std;

//*
class point{
  double tab[3];

public:

     point(): tab{0,0,0} {}

     point(const double a1, const double a2, const double a3): tab{a1,a2,a3} {}

     point(const double* t): tab{t[0], t[1], t[2]} {}
      
     friend 
     ostream& operator<< (ostream& out, const point& r);   

     friend
     istream& operator>>(istream& in, point& r);

     const double distance (const point& p) const;
    
     const double &operator[](int i) const { 
        if(i<0 || i >= 3) throw string("Indeks poza zakresem\n");
        return tab[i]; 
       }

     point operator+ (const point & t) const
     {
        return point(tab[0] + t.tab[0], tab[1] + t.tab[1], tab[2] + t.tab[2]);
     }

     point operator- (const point & t) const
     {
        return point(tab[0] - t.tab[0], tab[1] - t.tab[1], tab[2] - t.tab[2]);
     }

     point operator* (const double & t) const
     {
        return point(tab[0] * t, tab[1] * t, tab[2] * t);
     }

    friend 
     point operator* (double f, point V);   

    friend bool operator<(const point& l, const point&p);

    friend bool operator==(const point& l, const point&p);

    const double* T3()const{ return tab; }   // stala metoda zwraca staly wskaznik do tablicy typu double

};

    ostream& operator<<(ostream& out, const point& r){
      return out << r.tab[0] << ", " << r.tab[1] << ", " << r.tab[2];
    }

    istream& operator>>(istream& in, point& r)        // W przeciazeniu operatora wczytywania danych point nie moze byc const
    {
      cout << "Prosze podac 3 wspolrzedne punktu: ";
      in >> r.tab[0] >> r.tab[1] >> r.tab[2];
      return in;
    }

    const double point::distance (const point& p) const {
      return sqrt(pow(tab[0] - p.tab[0], 2) + pow(tab[1] - p.tab[1], 2) + pow(tab[2] - p.tab[2], 2));
    }

    point operator* (double f, point V) { return point(V.tab[0] * f, V.tab[1] * f, V.tab[2]* f); }

    bool operator<(const point& l, const point&p){      // tie nalezy do biblioteki tuple - krotka. Porownuje wartosci dwoch obietkow 
      return tie(l.tab[0], l.tab[1], l.tab[2])          // zwraca true lub false
             < tie(p.tab[0], p.tab[1], p.tab[2]);
    } 

    bool operator==(const point& l, const point&p){
      return (l.tab[0] == p.tab[0] && l.tab[1] == p.tab[1] && l.tab[2] == p.tab[2]);
    }

int main(){
double x[2][3] = { {1.0, 1.0, 1.0},
                     {1.0, 2.0, 3.0} }; 

  point p1(x[0]), p2(x[1]);           

  const point p3(0.4, 0.2, 0.1);        
 
  cout << p1 << ", " << p2 << '\n';     
  cout << p3[0] << ' ' << p3[1] << ' ' << p3[2] << '\n';
 
  cout << p1.distance(point()) << endl;  
  cout << p3.distance(p1) << endl;

  cout << p1 + p2 << endl;           
  cout << p1 - p3 << endl;             

  cout << 3.14 * p2 << endl;           
  cout << p2 * 3.14 << endl;     
 
  cout << (p1 < p3) << endl;                

  cout << (p1 == point(1.0, 1.0, 1.0)) << endl;

  cin >> p1;

  cout << p1 << '\n';

  cout << "\n***e0**\n";
  point e0;
  cout << &e0 << '\n' << e0.T3() << '\n' << e0 << endl;

  cout << "\n***e1**\n";
  point e1(x[0]);
  cout << x << "  " << x[0] << "  (" << x[0][0] << ")  " << &x[0][0] << '\n';
  cout << &e1 << '\n' << e1.T3() << '\n' << e1 << endl; 

  cout << "\n***e2**\n";
  point e2(e1);
  cout << &e2 << '\n' << e2.T3() << '\n' << e2 << endl;

  cout << "\n***e0**\n";
  e0 = e2;
  cout << &e0 << '\n' << e0.T3() << '\n' << e0 << endl;

  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}