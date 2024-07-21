#include "circuit.h"
#include "operators.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <complex>


std::ostream & operator <<(std::ostream &os, const std::map<std::string, std::complex<double>> &m){
    for (const auto &p : m){
        os << p.first << ": " << p.second << std::endl;
    }
    return os;
}


std::string number_to_bits( long int numero, int numero_qubits ){
  long int tmp_var = numero;
  std::string tmp_string = std::string(numero_qubits, '0');
  for( long int i = 0; i<numero_qubits; i++ ){
    int exponente = std::pow( 2, numero_qubits - (i+1) );
    if( tmp_var >= exponente ){
      tmp_var -= exponente;
      tmp_string[i] = '1';
    };
  };
  return tmp_string;
};


Circuit::Circuit(int numero_qubits){
  this->numero_qubits = numero_qubits;
  for(long int i=0; i<std::pow(2,numero_qubits); i++){
    std::string str = number_to_bits(i, numero_qubits);
    if(i==0){
      (this->base_computacional)[str] = 1.0;
    }else{
      (this->base_computacional)[str] = 0.0;
    };
  };
};


void Circuit::set_estado_inicial(const std::vector< std::complex<double> > vector_estado){
  for( auto it=(this->base_computacional).begin(); it!=(this->base_computacional).end(); it++ ){
    int index = std::stoi( it->first, nullptr, 2 );
    (this->base_computacional)[it->first] = vector_estado.at(index);
  };
};

 
std::vector< std::complex<double> > Circuit::obtener_estado(){
  std::vector< std::complex<double> > vector_estado( std::pow(2, this->numero_qubits), 0.0);
  for( auto it=(this->base_computacional).begin(); it!=(this->base_computacional).end(); it++ ){
    int index = std::stoi( it->first, nullptr, 2 );
    vector_estado[index] = it->second;
  };
  return vector_estado;
};

void Circuit::mostrar_estado(){
  std::cout << this->base_computacional << std::endl;
}


//Toda la informacion de las wires y el operador esta el objeto
void Circuit::aplicar_operador( std::shared_ptr<Operator> op ){
  (this->queue_operadores).push_back(op);
};


void Circuit::eliminar_operador(const int indice){
  auto it = (this->queue_operadores).begin() + indice;
  (this->queue_operadores).erase(it);
};


void Circuit::mostrar_circuito(){
  std::vector<std::string> v_circuito ( this->numero_qubits, "-" );

  for( auto op: this->queue_operadores ){
    int indice = op->get_index();
    std::string base = std::string( (op->tag).length(), '-');
    for( int i = 0; i<v_circuito.size(); i++ ){
      if( i==indice ){
        v_circuito[i] = v_circuito[i] + (op->tag) + "-";
      }else{
        v_circuito[i] = v_circuito[i] + base + "-";
      };
    };
  };
  
  std::cout << "Circuit: " << std::endl;
  for( std::string wire: v_circuito ){
    std::cout << wire << std::endl;
  };
};

void Circuit::ejecutar_circuito(){
  //El operador se aplica a cada estado de la base computacional
  for( auto op: (this->queue_operadores) ){
    auto resultado = op->aplicar_operador( this->base_computacional );
    this->base_computacional = resultado;
  };
};

