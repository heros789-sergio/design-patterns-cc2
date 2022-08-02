#include <iostream>
using namespace std;

#ifndef USB_H
#define USB_H

class Usb{
  public:
    bool Disponible();
    void Conectar();
    void Enviar(string archivo);
};

bool Usb::Disponible(){
  return false;
}

void Usb::Conectar(){
  cout<<" \nConectando via Usb."<<endl;
}

void Usb::Enviar(string archivo){
  cout<<" Archivo: "<<archivo<<". Enviado con exito."<<endl;
}

#endif

