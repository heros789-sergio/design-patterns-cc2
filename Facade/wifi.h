
#include <iostream>
using namespace std;

#ifndef WIFI_H
#define WIFI_H

class Wifi{
  public:
    bool Disponible();
    void Conectar();
    void Autenticar();
    void Enviar(string archivo);
};

bool Wifi::Disponible(){
  return true;
}

void Wifi::Conectar(){
  cout<<"\nConectando via Wifi."<<endl;
}

void Wifi::Autenticar(){
  cout<<" Autenticando Wifi."<<endl;
}

void Wifi::Enviar(string archivo){
  cout<<" Archivo: "<<archivo<<". Enviado con exito."<<endl;
}

#endif

