#include <iostream>
#include "usb.h"
#include "wifi.h"
#include "bt.h"
using namespace std;

#ifndef TRANSFERIRARCHIVO_H
#define TRANSFERIRARCHIVO_H

class TransferirArchivo{
  private: //Atributos, se separa memoria para los objetos de los distintos tipos de envio.
    Usb* usb = new Usb();
    Wifi* wifi = new Wifi();
    Bluetooth* bt = new Bluetooth();
  public: //Metodos
    ~TransferirArchivo(); //Destructor
    //Metodos de envio
    void EnviarArchivoDirecto(string archivo);
    void EnviarArchivoViaUsb(string archivo);
    void EnviarArchivoViaBluetooth(string archivo);
    void EnviarArchivoViaWifi(string archivo);
};

#endif

TransferirArchivo::~TransferirArchivo(){ //Liberamos la memoria de los objetos.
  delete usb;
  delete wifi;
  delete bt;
}

//EnviarArchivoDirecto-> Envia el archivo sin indicar la via, la via disponible sera la elegida para enviar el archivo.
void TransferirArchivo::EnviarArchivoDirecto(string archivo){
  if (usb->Disponible()){
    usb->Conectar();
    usb->Enviar(archivo);
  }
  else if(bt->Disponible()){
    bt->Conectar();
    bt->Autenticar();
    bt->Enviar(archivo);
  }
  else if(wifi->Disponible()){
    wifi->Conectar();
    wifi->Autenticar();
    wifi->Enviar(archivo);
  }
  else{
    cout<<"El archivo no se pudo enviar."<<endl;
  }
}

//Envia el archivo via Usb
void TransferirArchivo::EnviarArchivoViaUsb(string archivo){
  if (usb->Disponible()){
    usb->Conectar();
    usb->Enviar(archivo);
  }
  else{
    cout<<"El archivo no se pudo enviar."<<endl;
  }
}

//Envia el archivo via Bluetooth
void TransferirArchivo::EnviarArchivoViaBluetooth(string archivo){
  if(bt->Disponible()){
    bt->Conectar();
    bt->Autenticar();
    bt->Enviar(archivo);
  }
  else{
    cout<<"El archivo no se pudo enviar."<<endl;
  }
}

//Envia el archivo via Wifi
void TransferirArchivo::EnviarArchivoViaWifi(string archivo){
  if(wifi->Disponible()){
    wifi->Conectar();
    wifi->Autenticar();
    wifi->Enviar(archivo);
  }
  else{
    cout<<"El archivo no se pudo enviar."<<endl;
  }
}
