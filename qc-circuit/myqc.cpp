#include "circuit.h"
#include "operators.h"
int main(){


  Circuit myqc(2);
  //myqc.mostrar_circuito();
  
  //std::shared_ptr<Operator> ptr1 (new RxGate(0, 12.3) );
  //myqc.aplicar_operador( ptr1 );
  //ptr1=nullptr;
  //myqc.eliminar_operador(0);

  std::shared_ptr<Operator> ptr3 (new XGate(0) );
  std::shared_ptr<Operator> ptr5 (new XGate(1) );

  std::shared_ptr<Operator> ptr4 (new CYGate(0,1) );

  //std::shared_ptr<Operator> ptr4 (new RxGate(1, 12.3) );
  myqc.aplicar_operador(ptr3);
  myqc.aplicar_operador(ptr5);
  myqc.aplicar_operador(ptr4);
  myqc.ejecutar_circuito();
  myqc.mostrar_circuito();
  return 0;
};
