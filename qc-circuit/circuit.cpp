#include "circuit.h"
#include "operators.h"
#include <cmath>
#include <memory>
#include <string>
#include <vector>


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
  std::vector< std::complex<double> > vector_estado(this->numero_qubits, 0.0);
  
  for( auto it=(this->base_computacional).begin(); it!=(this->base_computacional).end(); it++ ){
    int index = std::stoi( it->first, nullptr, 2 );
    vector_estado[index] = it->second;
  };
  return vector_estado;
};


//Toda la informacion de las wires y el operador esta el objeto
void Circuit::aplicar_operador( std::shared_ptr<Operator> op ){
  (this->queue_operadores).push_back(op);
};


void Circuit::eliminar_operador(const int indice){
  auto it = (this->queue_operadores).begin() + indice;
  (this->queue_operadores).erase(it);
};


void Circuit::mostrar_circuito(){
  std::cout << "wop" << std::endl;
};

void Circuit::ejecutar_circuito(){
  //El operador se aplica a cada estado de la base computacional
  for( auto op: (this->queue_operadores) ){
     
    for( auto it=(this->base_computacional).begin(); it!=(this->base_computacional).end(); it++ ){
      auto resultado = op->aplicar_operador( it->first, it->second );
    };
  }
};

