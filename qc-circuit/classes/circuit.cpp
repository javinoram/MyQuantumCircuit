#include "circuit.h"
#include "operators.h"
#include <cmath>
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
    (this->estados).push_back(str);
    if(i==0){
      (this->amplitudes).push_back(1.0);  
    }else{
      (this->amplitudes).push_back(0.0);
    };
  };
};


void Circuit::set_estado_inicial(const std::vector< std::complex<double> > vector_estado){
  int aux = 0;
  for(auto string_estado: this->estados){
    int index = std::stoi(string_estado, nullptr, 2);
    (this->amplitudes)[aux] = vector_estado.at(index);
    aux = aux+1;
  };
};

 
std::vector< std::complex<double> > Circuit::obtener_estado(){
  //Crear estado de 2^n
  std::vector< std::complex<double> > vector_estado(this->numero_qubits, 0.0);

  //Iterar sobre los estados para obtener el indice y mover la probabilidad al estado
  for( auto string_estado: this->estados ){
    int index = std::stoi( string_estado, nullptr, 2 );
    vector_estado[index] = (this->amplitudes).at(index);
  };
  return vector_estado;
};


//Toda la informacion de las wires y el operador esta el objeto
void Circuit::aplicar_operador(const Operator operador){
  (this->queue_operadores).push_back(operador);
};


void Circuit::eliminar_operador(const int indice){
  std::vector<Operator>::iterator it = (this->queue_operadores).begin() + indice;
  (this->queue_operadores).erase(it);
};


void Circuit::mostrar_circuito(){
  std::cout << "wop" << std::endl;
};

void Circuit::ejecutar_circuit(){};

