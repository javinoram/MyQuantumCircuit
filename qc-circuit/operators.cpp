#include "operators.h"
#include <complex>
#include <cmath>
#include <string>
#include <tuple>


Operator::Operator(){};

Operator::~Operator(){};

//Constructores y destructores de las clases padres
OneQubit::OneQubit( const int indice ){
  (this->indice) = indice;
};

int OneQubit::get_index(){return this->indice;};

OneQubit::~OneQubit(){ };

std::map<std::string, std::complex<double>> OneQubit::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion = OneQubit::indice;

  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    std::string estado_2 = it->first;
    estado_2[index_accion] = ( (it->first)[index_accion]=='0' ) ? '1' : '0';
    std::complex<double> p1 = it->second;
    std::complex<double> p2 = dict_probs[ estado_2 ];

    auto tuple_probs = accion( (it->first)[index_accion], p1);
    p1 = std::get<0>(tuple_probs);
    p2 = std::get<1>(tuple_probs);
      
    auto it_estado1 = new_probs.find( it->first );
    if( it_estado1 != new_probs.end() ){
      new_probs[ it->first ] = (new_probs[ it->first ]) + p1;
    }else{
      new_probs[ it->first ] = p1;
    };

    auto it_estado2 = new_probs.find( estado_2 );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado_2 ] = (new_probs[ estado_2 ]) + p2;
    }else{
      new_probs[estado_2] = p2;
    }
  };
  return new_probs;
};


TwoQubit::TwoQubit( const int indice1, const int indice2 ){
  (this->indice) = indice1;
  (this->indice_2) = indice2;
};

int TwoQubit::get_index(){return this->indice;};

TwoQubit::~TwoQubit(){ };

std::map<std::string, std::complex<double>> TwoQubit::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice;
  int index_accion_2 = TwoQubit::indice_2;
  
  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    //4 estados basales
    auto tuple_probs = accion( (it->first)[index_accion_1], (it->first)[index_accion_2], it->second);

    //check
    std::string estado = it->first;
    estado[index_accion_1] = '0';
    estado[index_accion_2] = '0';
    std::complex<double> p = std::get<0>(tuple_probs);
    auto it_estado2 = new_probs.find( estado );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado ] = (new_probs[ estado ]) + p;
    }else{
      new_probs[ estado ] = p;
    };

    estado[index_accion_1] = '0';
    estado[index_accion_2] = '1';
    p = std::get<1>(tuple_probs);
    it_estado2 = new_probs.find( estado );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado ] = (new_probs[ estado ]) + p;
    }else{
      new_probs[ estado ] = p;
    };

    estado[index_accion_1] = '1';
    estado[index_accion_2] = '0';
    p = std::get<2>(tuple_probs);
    it_estado2 = new_probs.find( estado );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado ] = (new_probs[ estado ]) + p;
    }else{
      new_probs[ estado ] = p;
    };

    estado[index_accion_1] = '1';
    estado[index_accion_2] = '1';
    p = std::get<3>(tuple_probs);
    it_estado2 = new_probs.find( estado );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado ] = (new_probs[ estado]) + p;
    }else{
      new_probs[ estado ] = p;
    };


  };
  return new_probs;
};


//
//
//RY GATE
//
//
RyGate::RyGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
  Operator::tag = "RY(" + std::to_string(angle) + ")";
};

RyGate::~RyGate(){ };

std::tuple<std::complex<double>, std::complex<double>> RyGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*cos( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), i*prob1*sin( (this->angle)*0.5 ) };
};

//
//
//RZ GATE
//
//
RzGate::RzGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
  Operator::tag = "RZ(" + std::to_string(angle) + ")";

};

RzGate::~RzGate(){ };
std::tuple<std::complex<double>, std::complex<double>> RzGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*exp( -i*(this->angle)*0.5 ), 0.0 };
  };
  return { 0.0, prob1*exp( i*(this->angle)*0.5 )};
};

//
//
//HADAMARD GATE
//
//
HGate::HGate( const int indice ): OneQubit(indice){
  Operator::tag = "H";
};

HGate::~HGate(){ };

std::tuple<std::complex<double>, std::complex<double>> HGate::accion(const char flag, std::complex<double> prob1){
  //std::complex<double> i(0,1);
  if( flag=='0' ){
    return { (1.0/sqrt(2.0))*prob1, ( 1.0/sqrt(2.0) )*prob1 };
  };
  return { (1.0/sqrt(2.0))*prob1, (-1.0/sqrt(2.0))*prob1 };
};

//
//
//X GATE
//
//
XGate::XGate( const int indice ): OneQubit(indice){
  Operator::tag = "X";
};

XGate::~XGate(){ };

std::tuple<std::complex<double>, std::complex<double>> XGate::accion( const char flag, std::complex<double> prob1 ){
  return {0.0, prob1};
};

//
//
//Z GATE
//
//
ZGate::ZGate( const int indice ): OneQubit(indice){
  Operator::tag = "Z";
};

ZGate::~ZGate(){ };

std::tuple<std::complex<double>, std::complex<double>> ZGate::accion( const char flag, std::complex<double> prob1 ){
  if( flag=='0' ){
    return {prob1, 0.0};
  };
  return {-prob1, 0.0};
};

//
//
//Y GATE
//
//
YGate::YGate( const int indice ): OneQubit(indice){
  Operator::tag = "Y";
};

YGate::~YGate(){ };

std::tuple<std::complex<double>, std::complex<double>> YGate::accion( const char flag, std::complex<double> prob1 ){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return {0.0, i*prob1};
  };
  return {0.0, -i*prob1};
};

//
//
//RX GATE
//
//
RxGate::RxGate( const int indice, const double angle ): OneQubit(indice) { 
  (this->angle) = angle;
  Operator::tag = "RX(" + std::to_string(angle) + ")";
};

RxGate::~RxGate(){ };

std::tuple<std::complex<double>, std::complex<double>> RxGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag == '0' ){
    return { prob1*cos( (this->angle)*0.5 ), -i*prob1*sin( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
};

//
//
//CNOT GATE
//
//
CnotGate::CnotGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){
  Operator::tag = "CX(" + std::to_string(indice2) + ")";
};

CnotGate::~CnotGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CnotGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    return {0.0, 0.0, 0.0, prob};
  }; 
  return {0.0, 0.0, prob, 0.0};
};

//
//
//CZ GATE
//
//
CZGate::CZGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){
  Operator::tag = "CZ(" + std::to_string(indice2) + ")";

};

CZGate::~CZGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CZGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    return {0.0, 0.0, prob, 0.0};
  }; 
  return {0.0, 0.0, 0.0, -prob};
};

//
//
//CY GATE
//
//
CYGate::CYGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){
  Operator::tag = "CY(" + std::to_string(indice2) + ")";
};

CYGate::~CYGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CYGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  std::complex<double> i(0,1);
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    return {0.0, 0.0, 0.0, i*prob};
  }; 
  return {0.0, 0.0, -i*prob, 0.0};
};
//
//
//CH GATE
//
//
CHGate::CHGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){
  Operator::tag = "CH(" + std::to_string(indice2) + ")";
};

CHGate::~CHGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CHGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    return {0.0, 0.0, (1.0/sqrt(2.0))*prob, (1.0/sqrt(2.0))*prob};
  }; 
  return {0.0, 0.0, (-1.0/sqrt(2.0))*prob, (1.0/sqrt(2.0))*prob};
};

//
//
//CRX GATE
//
//
CRXGate::CRXGate(const int indice1, const int indice2, const double angle): TwoQubit(indice1, indice2){
  (this->angle) = angle;
  Operator::tag = "CRX(" + std::to_string(angle) + ","+ std::to_string(indice2) + ")";
};

CRXGate::~CRXGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CRXGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  std::complex<double> i(0,1);
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    std::complex<double> val1 = prob*cos( (this->angle)*0.5 );
    std::complex<double> val2 = -i*prob*sin( (this->angle)*0.5 );
    return {0.0, 0.0, val1, val2};
  }; 
  std::complex<double> val1 = -prob*i*sin( (this->angle)*0.5 );
  std::complex<double> val2 = prob*cos( (this->angle)*5 );
  return {0.0, 0.0, val1, val2};
};

//
//
//CRY GATE
//
//
CRYGate::CRYGate(const int indice1, const int indice2, const double angle): TwoQubit(indice1, indice2){
  (this->angle) = angle;
  Operator::tag = "CRY(" + std::to_string(angle) + ","+ std::to_string(indice2) + ")";
};

CRYGate::~CRYGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CRYGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  std::complex<double> i(0,1);
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    std::complex<double> val1 = prob*cos( (this->angle)*0.5 );
    std::complex<double> val2 = prob*cos( (this->angle)*0.5 );
    return {0.0, 0.0, val1, val2};
  }; 
  std::complex<double> val1 = -i*prob*sin( (this->angle)*0.5 );
  std::complex<double> val2 = i*prob*sin( (this->angle)*5 );
  return {0.0, 0.0, val1, val2};
};

//
//
//CRZ GATE
//
//
CRZGate::CRZGate(const int indice1, const int indice2, const double angle): TwoQubit(indice1, indice2){
  (this->angle) = angle;
  Operator::tag = "CRZ(" + std::to_string(angle) + ","+ std::to_string(indice2) + ")";
};

CRZGate::~CRZGate(){ };

std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
  CRZGate::accion(const char flag1, const char flag2,  std::complex<double> prob){
  std::complex<double> i(0,1);
  if( flag1 == '0' && flag2 == '0' ){
    return {prob, 0.0, 0.0, 0.0};
  }else if( flag1 == '0' and flag2 == '1' ){
    return {0.0, prob, 0.0, 0.0};
  }else if( flag1 == '1' && flag2 == '0' ){
    std::complex<double> val1 = prob*exp( -i*(this->angle)*0.5 );
    std::complex<double> val2 = 0.0;
    return {0.0, 0.0, val1, val2};
  }; 
  std::complex<double> val1 = 0.0;
  std::complex<double> val2 = prob*exp( i*(this->angle)*0.5 );
  return {0.0, 0.0, val1, val2};
};
