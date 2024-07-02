#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include <iostream>
#include "operators.h"

class Circuit {
  private:
    //Variables del circuito privadas
    int numero_qubits;
    std::vector <std::string> estados;
    std::vector <double> amplitudes;
    std::vector <Operator> queue_operadores;
    //Metodos privados para facilitar trabajo de las funciones publicas
  public:
    //Metodos publicos para manipular el circuito
    Circuit(int numero_qubits);
    void ejecutar_circuit();
    std::vector<double> obtener_estado();
    void aplicar_operador(const Operator operador);
    void eliminar_operador(const int indice);
    void set_estado_inicial( const std::vector<double> vector_estado );
    void mostrar_circuito();
};

#endif
