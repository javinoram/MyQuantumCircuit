#include "qc-circuit/circuit.h"
#include "qc-circuit/operators.h"

//In this example we will create a 3 bell state
int main(){

  //Create a empty circuit
  Circuit myqc( 3 );
  
  //Create the three operatos that I will use
  std::shared_ptr<Operator> ptr1 ( new HGate(0) );
  std::shared_ptr<Operator> ptr2 ( new CnotGate(0,1) );
  std::shared_ptr<Operator> ptr3 ( new CnotGate(1,2) );

  
  //We add the operators to the circuit
  myqc.aplicar_operador( ptr1 );
  myqc.aplicar_operador( ptr2 );
  myqc.aplicar_operador( ptr3 );

  myqc.ejecutar_circuito();
  myqc.mostrar_circuito();
  myqc.mostrar_estado();

  return 0;
};
