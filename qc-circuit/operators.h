#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>
#include <vector>
#include <complex>


class Operator{
  public:
    Operator();
    virtual ~Operator();
    //retorna el resultado de aplicar el operador sobre el estado y su probabilidad
    virtual std::tuple<std::string, std::complex<double>> aplicar_operador( std::string estado, std::complex<double> prob )=0;
};


//Clases abstractas para numero de qubits fijos
class OneQubit: public Operator{
  protected:
    int indice;
  public:
    OneQubit( const int indice );
    ~OneQubit();
    virtual std::complex<double> accion( std::string estado, std::complex<double> prob )=0;
    std::tuple<std::string, std::complex<double>> aplicar_operador( std::string estado, std::complex<double> prob ) final;
};


class TwoQubit: public Operator{
  protected:
    int indice_1;
    int indice_2;
  public:
    TwoQubit( const int indice1, const int indice2 );
    ~TwoQubit();
    virtual std::string accion( std::string estado, std::complex<double> prob )=0;
    std::tuple<std::string, std::complex<double>> aplicar_operador( std::string estado, std::complex<double> prob ) final; 
};



//Compuertas de un qubit 
class RxGate: public OneQubit{
  private:
    double angle;
  public:
    RxGate( const int indice, const double angle );
    ~RxGate();
    std::complex<double> accion( std::string estado, std::complex<double> prob ) final;
  
};

class RyGate: public OneQubit{
  private:
    double angle;
  public:
    RyGate( const int indice, const double angle );
    ~RyGate();
    std::complex<double> accion( std::string estado, std::complex<double> prob ) final;
};

class RzGate: public OneQubit{
  private:
    double angle;
  public:
    RzGate( const int indice, const double angle );
    ~RzGate();
    std::complex<double> accion( std::string estado, std::complex<double> prob ) final;
};

class HGate: public OneQubit{
  public:
    HGate( const int indice );
    ~HGate();
    std::complex<double> accion(std::string estado, std::complex<double> prob) final;
};


//Compuerta condicionales
class CnotGate: public TwoQubit{
  public:
   CnotGate( const int indice1, const int indice2 );
    ~CnotGate();
    std::string accion( std::string estado, std::complex<double> prob ) override;
};
#endif
