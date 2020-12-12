/* Dominik Ludwin, lab1, 131609, 19.11.2020r. Program zawiera trzy klasy - unit1, point, polygon, oraz jedna struktura blad. 
Struktura blad posiada tekst oraz numer wiersza bledu, wazny jest tutaj konstruktor z parametrami ktory inicjalizuje blad, posiada operator wypisania na ekran.
Klasa uint1 ma staly operator () zwracajacy zmienna prywatna, zaprzyjaznione operatory wypisania oraz wpisania. 
klasa point sklada sie z 2 zmiennych prywatnych, konstruktora domyslnego oraz z parametrami, operator wypisania i wpisania, zaprzyjazniona klase polygon, oraz metode
distance ktora oblicza dystans pomiedzy punktami ze wzoru. 
Klasa polygon ma operator przypisania domyslnego oraz kopiujacego, operator rownosci ktory przypisuje wartosci obiektu z prawej strony rownosci do wart.lewego obiektu
Mamy destruktor ktory niszczy pamiec zaalokowana w dwoch tabelach. Oraz dwie stale metody do liczenia obwodu oraz pola polygonu. 

*/

#include <iostream>
#include <fstream>
#include <cmath> 
#include <string.h>
#ifdef _WIN32
  #include <windows.h>
#endif // _WIN32 and _WIN64 too
using namespace std;

class uint1{
  unsigned v;
public:
  uint1():v(0){}
  uint1(const unsigned& a):v(a){}
  operator unsigned()const { return v; }
  friend 
  ostream& operator<<(ostream& out, const uint1& r){ return out << r.v; }
  friend 
  istream& operator>>(istream& in,  uint1& r){ return in >> r.v; }
};

struct blad {
  string txt;
  unsigned lp;
  blad():lp(0){}
  blad(const string& a, unsigned b):txt(a), lp(b){}
};
ostream& operator<<(ostream& out, const blad& p){return out << p.txt << ' ' << p.lp << endl; }

using naturalne = uint1;    

class polygon;

class point {
  double x,y;
  public:
  point():x(0),y(0){}
  point(const double& a, const double& b):x(a),y(b){}
  double distance(const point& a)const; 
  friend class polygon;
  friend istream& operator>>(istream&, point&);
  friend ostream& operator<<(ostream&, const point&);
  
};
double point::distance(const point& a)const {
  double c2 = (a.x-x)*(a.x-x)+(a.y-y)*(a.y-y);
  if(c2<1e-20)
    return 0; 
  return sqrt(c2); 
}
istream& operator>>(istream& in, point& p){return in>>p.x>>p.y; }
ostream& operator<<(ostream& out, const point& p){return out << p.x <<' '<<p.y; }

class polygon{
  unsigned n;
  point* points;
  naturalne* order;
  
 public:
  polygon():n(0), points(nullptr), order(nullptr){}
  polygon(const polygon& a);
  polygon& operator=(const polygon& a);  
  ~polygon(){ delete[] points; delete[] order; cout << "\n\n!!!~polygon()!!!\n\n"; } 
 
  void read(ifstream & );
  double obwod()const;
  double pole()const;
};

polygon::polygon(const polygon& a): n(a.n), points(new point[a.n]), order(new naturalne[a.n]) {
  for(size_t i = 0; i < n; i++){
    points[i] = a.points[i];
    order[i] = a.order[i];
  }
}
polygon& polygon::operator=(const polygon& a){
  if(this != &a){
      delete points;
      n = a.n;
      points = n? new point[n]:0;
      order = n? new naturalne[n]:0;
      for(size_t i = 0; i < n; i++){
         points[i] = a.points[i];
         order[i] = a.order[i];
      }
  }
  return *this;
}  

void polygon::read(ifstream & f){

  string buf;
  getline(f,buf);

  if(buf!="[POLYGON]") throw string("Brak nagłówka \"[POLYGON]\""); 

  getline(f,buf);
  if(buf!="[NUMBER OF NODES]") throw string("Brak nagłówka \"[NUMBER OF NODES]\""); 

  f >> n ; 
  getline(f,buf);

  if(!f || buf[0]!='\0' ) throw string("Nieprawidłowy format parametru \"n\""); 
  
 
  if(n<3) throw string("Liczba punktów mniejsza od 3");

  getline(f,buf);
  if(buf!="[NODES]") throw string("Brak nagłówka \"[NODES]\""); 

  unsigned int id;
  points = new point[n];
  order = new naturalne[n];
  
  for (size_t i = 0; i < n; i++)
  {
    f >> id;
    if(id < 1 || id > n) throw blad("Niepoprawny numer wezla w pliku tekstowym w linii: ", 5+i);
    f >> points[id-1].x;
    f >> points[id-1].y;
  }
  
  getline(f,buf);

  getline(f,buf);

  if(buf!="[POLYGON]") throw string("Brak nagłówka \"[POLYGON]\"");  

  for (size_t i = 0; i < n; i++)
  {
    f >> order[i];
    if(order[i] < 1 || order[i] > n) throw blad("Niepoprawne dane kolejności przetwarzania danych. Linia: ", 5+n+1);
  }
}

 double polygon::obwod()const{
  double obw=0;
  if(!order) throw string ("Brak tablicy order.");
  if(!points) throw string ("Brak tablicy points.");
  for(int i=0, j=0; (unsigned)i<n ;++i){
    j = order[i]-1;
    if(j<0) throw string ("Niedozwolona wartość 0 w tablicy order.");
    if(j> int(n)) throw string ("Wartosc w tablicy order jest wieksza od liczby wezlow.");
    obw+=points[j].distance(points[order[(i+1)%n]-1]);
  }
  return obw;
}

 double polygon::pole()const{

  double area = 0.0;
  double* tabx = new double[n];
  double* taby = new double[n];

  for(unsigned int i = 0; i < n; i++){
    double tempx = points[order[i]-1].x;
    double tempy = points[order[i]-1].y;
    tabx[i] = tempx;
    taby[i] = tempy;
  }
  int j = n - 1;
  for (unsigned int i = 0; i < n; i++){
    area += (tabx[j] + tabx[i]) * (taby[j] - taby[i]);
    j = i;
   }
   return abs(area / 2.0);
}  


int main (int argc, char* argv[])try {
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif

  if (argc !=2) throw int(0);
  if (strlen(argv[1]) < 5 ) throw int(1);
  if (string(argv[1]+(strlen(argv[1])-3))!="txt") throw 2 ;  

  ifstream file(argv[1]);
  if(!file) throw int (3);
  {
    polygon poly;
    try{
      poly.read(file);
      cout<< "obwód : " << poly.obwod()<< endl;
      cout<< "pole  : " << poly.pole()<< endl;  
    }
    catch ( const string& e ){ cout << e << endl;}
    catch ( const blad&   e ){ cout << e ;}
    file.close();
  }

  #ifdef _WIN32
    system("PAUSE");
  #endif
  return 0;
}
catch (int err){
  switch (err) {
    case 0: cout << err <<": Zła liczba parametrów programu.\n";
    break;
    case 1: cout << err <<": Zła nazwa pliku z danymi.\n";
    break;
    case 2: cout << err <<": Złe rozszerzenie pliku z danymi - musi być *.txt .\n";
    break;
    case 3: cout << err <<": Brak pliku o nazwie "<< argv[1] << " .\n";
  }
}
catch ( ... ) { cout << "Nieznana sytuacja wyjątkowa.\n"; }