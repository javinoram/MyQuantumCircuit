#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>
#include <vector>
#include <complex>
#include <map>


class Operator{
  public:
    Operator();
    virtual ~Operator();
    //retorna el resultado de aplicar el operador sobre el estado y su probabilidad
    virtual std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs )=0;
};


//Clases abstractas para numero de qubits fijos
class OneQubit: public Operator{
  protected:
    int indice;
  public:
    OneQubit( const int indice );
    virtual ~OneQubit();
    virtual std::complex<double> accion( const char flag, std::complex<double> prob1, std::complex<double> prob2 )=0;
    virtual std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs )=0;
};


class TwoQubit: public Operator{
  protected:
    int indice_1;
    int indice_2;
  public:
    TwoQubit( const int indice1, const int indice2 );
    virtual ~TwoQubit();
    virtual std::string accion( std::string estado, std::complex<double> prob )=0;
    virtual std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs )=0; 
};



//Compuertas de un qubit 
class RxGate: public OneQubit{
  private:
    double angle;
  public:
    RxGate( const int indice, const double angle );
    ~RxGate();
    std::complex<double> accion( const char flag, std::complex<double> prob1, std::complex<double> prob2 ) final;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;

  
};

class RyGate: public OneQubit{
  private:
    double angle;
  public:
    RyGate( const int indice, const double angle );
    ~RyGate();
    std::complex<double> accion(const char flag, std::complex<double> prob1, std::complex<double> prob2) final;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;

};

class RzGate: public OneQubit{
  private:
    double angle;
  public:
    RzGate( const int indice, const double angle );
    ~RzGate();
    std::complex<double> accion(const char flag, std::complex<double> prob1, std::complex<double> prob2) final;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;
};

class HGate: public OneQubit{
  public:
    HGate( const int indice );
    ~HGate();
    std::complex<double> accion(const char flag, std::complex<double> prob1, std::complex<double> prob2) final;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;
};


//Compuerta condicionales
class CnotGate: public TwoQubit{
  public:
   CnotGate( const int indice1, const int indice2 );
    ~CnotGate();
    std::string accion( std::string estado, std::complex<double> prob ) final;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;
};
#endif
