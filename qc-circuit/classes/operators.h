#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <complex>


class Operator{};


//Clases abstractas para numero de qubits fijos
class OneQubit: public Operator{
  protected:
    int indice;
  public:
    OneQubit( const int indice );
    ~OneQubit();
    virtual std::complex<double> accion_operador( std::string estado, std::complex<double> prob )=0;
};


class TwoQubit: public Operator{
  protected:
    int indice_1;
    int indice_2;
  public:
    TwoQubit( const int indice1, const int indice2 );
    ~TwoQubit();
    virtual std::string accion_operador( std::string estado )=0;
};



//Compuertas de rotación Rx, Ry, Rz
class RxGate: public OneQubit{
  private:
    double angle;
  public:
    RxGate( const int indice, const double angle );
    ~RxGate();
    std::complex<double> accion_operador( std::string estado, std::complex<double> prob ) override;
  
};

class RyGate: public OneQubit{
  private:
    double angle;
  public:
    RyGate( const int indice, const double angle );
    ~RyGate();
    std::complex<double> accion_operador( std::string estado, std::complex<double> prob ) override;
};

class RzGate: public OneQubit{
  private:
    double angle;
  public:
    RzGate( const int indice, const double angle );
    ~RzGate();
    std::complex<double> accion_operador( std::string estado, std::complex<double> prob ) override;
};

class HGate: public OneQubit{
  public:
    HGate( const int indice );
    ~HGate();
    std::complex<double> accion_operador(std::string estado, std::complex<double> prob) override;
};


//Compuerta condicionales
class CnotGate: public TwoQubit{
  private:
  public:
    CnotGate( const int indice1, const int indice2 );
    ~CnotGate();
    std::string accion_operador( std::string estado ) override;
};
#endif
