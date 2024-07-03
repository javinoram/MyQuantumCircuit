#include "operators.h"
#include<iostream>
#include <complex>
#include <cmath>


//Constructores y destructores de las clases padres
OneQubit::OneQubit( const int indice ){
  (this->indice) = indice;
};
OneQubit::~OneQubit(){ std::cout<<"Destructor OneQubit"<<std::endl; };

TwoQubit::TwoQubit( const int indice1, const int indice2 ){
  (this->indice_1) = indice_1;
  (this->indice_2) = indice_2;
};
TwoQubit::~TwoQubit(){ std::cout<<"Destructor TwoQubit"<<std::endl; };


//Metodos de las clases hijas de la clase OneQubit
RxGate::RxGate( const int indice, const double angle ): OneQubit(indice) {
  (this->angle) = angle;
};
RxGate::~RxGate(){std::cout<<"Destructor RxGate"<<std::endl;};


std::complex<double> RxGate::accion_operador(std::string estado, std::complex<double> prob){
  std::complex<double> exponente(0.0, (this->angle)*0.5);
  std::complex<double> tmp_var ( std::exp( exponente ) );
  if( estado[OneQubit::indice]=='0' ){
    tmp_var = std::exp( -exponente );
  };
  return tmp_var*prob;
}


RyGate::RyGate( const int indice, const double angle ): OneQubit(indice){

}
RyGate::~RyGate(){std::cout<<"Destructor RyGate"<<std::endl;}

std::complex<double> RyGate::accion_operador(std::string estado, std::complex<double> prob){
  return prob;
};


RzGate::RzGate( const int indice, const double angle ): OneQubit(indice){

}
RzGate::~RzGate(){std::cout<<"Destructor RzGate"<<std::endl;}
std::complex<double> RzGate::accion_operador(std::string estado, std::complex<double> prob){
  return prob;
};

HGate::HGate( const int indice ): OneQubit(indice){

};
HGate::~HGate(){std::cout<<"Destructor Hadamard"<<std::endl;};
std::complex<double> HGate::accion_operador( std::string estado, std::complex<double> prob ){
  return prob;
};



//Metodos de las clases hijas de la clase TwoQubit
CnotGate::CnotGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};
CnotGate::~CnotGate(){std::cout<<"Destructor Cnot gate"<<std::endl;};
std::string CnotGate::accion_operador(std::string estado){
  return estado;
}
