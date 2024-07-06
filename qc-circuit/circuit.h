#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include <iostream>
#include <complex>
#include <map>
#include "operators.h"

class Circuit {
  private:
    //Variables del circuito privadas
    int numero_qubits;
    std::map< std::string, std::complex<double> > base_computacional;
    std::vector < std::shared_ptr<Operator>> queue_operadores;
    //Metodos privados para facilitar trabajo de las funciones publicas
  public:
    //Metodos publicos para manipular el circuito
    Circuit( const int numero_qubits );
    void ejecutar_circuito();
    std::vector< std::complex<double> > obtener_estado();
    void aplicar_operador( std::shared_ptr<Operator> op );
    void eliminar_operador( const int indice );
    void set_estado_inicial( const std::vector< std::complex<double> > vector_estado );
    void mostrar_circuito();
};

#endif
