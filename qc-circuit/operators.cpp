#include "operators.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <tuple>


Operator::Operator(){};

Operator::~Operator(){};

//Constructores y destructores de las clases padres
OneQubit::OneQubit( const int indice ){
  (this->indice) = indice;
};

OneQubit::~OneQubit(){ std::cout<<"Destructor OneQubit"<<std::endl; };

TwoQubit::TwoQubit( const int indice1, const int indice2 ){
  (this->indice_1) = indice1;
  (this->indice_2) = indice2;
};

TwoQubit::~TwoQubit(){ std::cout<<"Destructor TwoQubit"<<std::endl; };


//
//
//RX GATE
//
//
RxGate::RxGate( const int indice, const double angle ): OneQubit(indice) { 
  (this->angle) = angle;
};

RxGate::~RxGate(){std::cout<<"Destructor RxGate"<<std::endl;};

std::map<std::string, std::complex<double>> RxGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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

std::tuple<std::complex<double>, std::complex<double>> RxGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag == '0' ){
    return { prob1*cos( (this->angle)*0.5 ), -i*prob1*sin( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
};


//
//
//RY GATE
//
//
RyGate::RyGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
};

RyGate::~RyGate(){std::cout<<"Destructor RyGate"<<std::endl;};

std::tuple<std::complex<double>, std::complex<double>> RyGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*cos( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), i*prob1*sin( (this->angle)*0.5 ) };
};

std::map<std::string, std::complex<double>> RyGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };

  };
  return new_probs;
};

//
//
//RZ GATE
//
//
RzGate::RzGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
};
RzGate::~RzGate(){std::cout<<"Destructor RzGate"<<std::endl;};
std::tuple<std::complex<double>, std::complex<double>> RzGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*exp( -i*(this->angle)*0.5 ), 0.0 };
  };
  return { 0.0, prob1*exp( i*(this->angle)*0.5 )};
};
std::map<std::string, std::complex<double>> RzGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };
  };

  return new_probs;
};


//
//
//HADAMARD GATE
//
//
HGate::HGate( const int indice ): OneQubit(indice){};

HGate::~HGate(){std::cout<<"Destructor Hadamard"<<std::endl;};

std::tuple<std::complex<double>, std::complex<double>> HGate::accion(const char flag, std::complex<double> prob1){
  //std::complex<double> i(0,1);
  if( flag=='0' ){
    return { (1.0/sqrt(2.0))*prob1, ( 1.0/sqrt(2.0) )*prob1 };
  };
  return { (1.0/sqrt(2.0))*prob1, (-1.0/sqrt(2.0))*prob1 };
};

std::map<std::string, std::complex<double>> HGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };
  };
  return new_probs;
};


//
//
//X GATE
//
//
XGate::XGate( const int indice ): OneQubit(indice){};

XGate::~XGate(){std::cout<<"Destructor Not gate"<<std::endl;};

std::tuple<std::complex<double>, std::complex<double>> XGate::accion( const char flag, std::complex<double> prob1 ){
  return {0.0, prob1};
};

std::map<std::string, std::complex<double>> XGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };
  };
  return new_probs;
};


//
//
//Z GATE
//
//
ZGate::ZGate( const int indice ): OneQubit(indice){};

ZGate::~ZGate(){std::cout<<"Destructor Z gate"<<std::endl;};

std::tuple<std::complex<double>, std::complex<double>> ZGate::accion( const char flag, std::complex<double> prob1 ){
  if( flag=='0' ){
    return {prob1, 0.0};
  };
  return {-prob1, 0.0};
};

std::map<std::string, std::complex<double>> ZGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };
  };
  return new_probs;
};



//
//
//Y GATE
//
//
YGate::YGate( const int indice ): OneQubit(indice){};

YGate::~YGate(){std::cout<<"Destructor Z gate"<<std::endl;};

std::tuple<std::complex<double>, std::complex<double>> YGate::accion( const char flag, std::complex<double> prob1 ){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return {0.0, i*prob1};
  };
  return {0.0, -i*prob1};
};

std::map<std::string, std::complex<double>> YGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
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
    };
  };
  return new_probs;
};



//
//
//CNOT GATE
//
//
CnotGate::CnotGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};

CnotGate::~CnotGate(){std::cout<<"Destructor Cnot gate"<<std::endl;};

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

std::map<std::string, std::complex<double>> CnotGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice_1;
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
//CZ GATE
//
//
CZGate::CZGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};

CZGate::~CZGate(){std::cout<<"Destructor CZ gate"<<std::endl;};

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

std::map<std::string, std::complex<double>> CZGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice_1;
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
//CY GATE
//
//
CYGate::CYGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};

CYGate::~CYGate(){std::cout<<"Destructor CY gate"<<std::endl;};

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

std::map<std::string, std::complex<double>> CYGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice_1;
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
//CH GATE
//
//
CHGate::CHGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};

CHGate::~CHGate(){std::cout<<"Destructor CY gate"<<std::endl;};

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


std::map<std::string, std::complex<double>> CHGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice_1;
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
//CRX GATE
//
//
CRXGate::CRXGate(const int indice1, const int indice2, const double angle): TwoQubit(indice1, indice2){
  this->angle = angle;
};

CRXGate::~CRXGate(){std::cout<<"Destructor CY gate"<<std::endl;};

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

std::map<std::string, std::complex<double>> CRXGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){
  //iterar sobre estados
  //tomar los 4 estados que representan 00 01 10 11 junto a sus probabilidades
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion_1 = TwoQubit::indice_1;
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











