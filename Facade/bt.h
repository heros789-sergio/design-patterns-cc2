#include <iostream>
using namespace std;

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

class Bluetooth{
  public:
    bool Disponible();
    void Conectar();
    void Autenticar();
    void Enviar(string archivo);
};

bool Bluetooth::Disponible(){
  return true;
}

void Bluetooth::Conectar(){
  cout<<"\nConectando via Bluetooth."<<endl;
}

void Bluetooth::Autenticar(){
  cout<<" Autenticando Bluetooth."<<endl;
}

void Bluetooth::Enviar(string archivo){
  cout<<" Archivo: "<<archivo<<". Enviado con exito."<<endl;
}

#endif

