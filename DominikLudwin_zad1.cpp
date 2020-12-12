// Dominik Ludwin, lab.1, 3.11.2020r. Program posiada trzy klasy punkt, prostokat, graniastoslup i kazda z nich zawiara konstruktor domyslny oraz konstruktor z argumentami
// Nastepnie utworzone zostaly metody dostepowe poprzez referencje do stalej instancji klasy (stala metoda i liczba) oraz normalnych (nie const). 
// Dodatkowo klasa prostokat oblicza pole, natomiast klasa graniastoslup dodatkowo oblicza objetosc. 
// klasa prostokat posiada konstuktor ktory pobiera punkt a nastepnie wspolrzedne punktow na przekatnej a i b. 
// Instacja klasy graniastoslup moze byc stworzona na 3 sposoby: podanie danych, punkt i dane, oraz prostokat i dane. 

#include <iostream>

using namespace std;

class punkt{
  double x_, y_, z_;
    
public:
  
  punkt(): x_(0), y_(0), z_(0){}
  
  punkt(const double& a1, const double& a2, const double& a3 ): x_(a1), y_(a2), z_(a3){}
  
  double& x() { return x_; } 
  double& y() { return y_; } 
  double& z() { return z_; } 
  const double& x() const { return x_; }   
  const double& y() const { return y_; }   
  const double& z() const { return z_; }   
};
 
class prostokat{
  double x_, y_, z_, a_, b_;

  public:

    prostokat(): x_(0), y_(0), z_(0), a_(0), b_(0){}

    prostokat(const double& a1, const double& a2, const double& a3, const double& a4, const double& a5 ): x_(a1), y_(a2), z_(a3), a_(a4), b_(a5) {}

    prostokat(const punkt& pkt, const double& a4, const double& a5 ): x_(pkt.x()), y_(pkt.y()), z_(pkt.z()), a_(a4), b_(a5) {}

    double pole() { return a_ * b_; }
    double pole() const { return a_ * b_; }

    double& x() { return x_; } 
    double& y() { return y_; } 
    double& z() { return z_; } 
    double& a() { return a_; } 
    double& b() { return b_; } 
    const double& x() const { return x_; }   
    const double& y() const { return y_; }   
    const double& z() const { return z_; }  
    const double& a() const { return a_; }   
    const double& b() const { return b_; }  
};
  
class graniastoslup{
  double x_, y_, z_, a_, b_, h_;

  public:

    graniastoslup(): x_(0), y_(0), z_(0), a_(0), b_(0), h_(0){}

    graniastoslup(const double& a1, const double& a2, const double& a3, const double& a4, const double& a5, const double& a6 ): 
        x_(a1), y_(a2), z_(a3), a_(a4), b_(a5),h_(a6) {}

    graniastoslup(const punkt& pkt, const double& a4, const double& a5, const double& a6  ): x_(pkt.x()), y_(pkt.y()), z_(pkt.z()), a_(a4), b_(a5), h_(a6) {}
    
    graniastoslup(const prostokat& pro, const double& a6 ): x_(pro.x()), y_(pro.y()), z_(pro.z()), a_(pro.a()), b_(pro.b()), h_(a6) {}

    double objetosc() { return a_ * b_ * h_; }
    double objetosc() const { return a_ * b_ * h_; }

    double& x() { return x_; } 
    double& y() { return y_; } 
    double& z() { return z_; } 
    double& a() { return a_; } 
    double& b() { return b_; } 
    double& h() { return h_; }
    const double& x() const { return x_; }   
    const double& y() const { return y_; }   
    const double& z() const { return z_; }  
    const double& a() const { return a_; }   
    const double& b() const { return b_; }  
    const double& h() const { return h_; }  
};


int main(){
  punkt p1, p2(1,2,3);         
  const punkt p3(1.1,2.2,3.3);
 
  cout << p1.x() << endl;
  cout << p2.x() << endl;
 
  cout << p3.x() << endl;     

  cout << p3.x() << '\t' << p3.y() << '\t' << p3.z() << endl;
 
  p1.x()=1; p1.y()=10; p1.z()=100;  
                                    
  cout << p1.x() << '\t' << p1.y() << '\t' << p1.z() << endl;
 
  prostokat pr1, pr2(1,2,3,10.5, 20.5);
                                        
  const prostokat pr3(p2,5,5);

  pr1.x()=2; pr1.y()=20; pr1.x()=200; pr1.a()= 10; pr1.b()=10;
  cout << pr1.x() << '\t' << pr1.y() << '\t' << pr1.z() << '\t'
       << pr1.a() << '\t' << pr1.b() << '\t' << endl;
  cout << pr1.pole() << endl;


  cout << pr3.x() << '\t' << pr3.y() << '\t' << pr3.z() << '\t'
       << pr3.a() << '\t' << pr3.b() << '\t' << endl;

  cout << pr3.pole() << endl;          

  graniastoslup g1, g2(1,2,3,10.5,20.5,30.5), g3(p2,100,200,300);
  const graniastoslup g4(pr3,5);

  cout << g4.x() << '\t' << g4.y() << '\t' << g4.z() << '\n'
       << g4.a() << '\t' << g4.b() << '\t' << g4.h() << '\n'
       << g4.objetosc() << endl;

  g1.a()=10; g1.b()=10; g1.h()=10;
 
  cout << g1.x() << '\t' << g1.y() << '\t' << g1.z() << '\n'
       << g1.a() << '\t' << g1.b() << '\t' << g1.h() << '\n'
       << g1.objetosc() << endl; 

return 0;
}