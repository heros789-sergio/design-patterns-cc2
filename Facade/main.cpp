//Este es un ejemplo simple del uso del patron de diseño facade para entender su funcionamiento.

#include <iostream>
#include "TransferirArchivo.h" //Incluimos nuestra clase fachada(facade).
using namespace std;

int main(){

  TransferirArchivo* TA = new TransferirArchivo(); // Creamos un objeto Fachada.
  string archivo = "Archivo 1"; //El archivo a transferir.
 
  TA->EnviarArchivoDirecto(archivo); //Metodo para enviar archivo sin especificar una via.
  
  //Esta es la nueva forma de enviar un archivo via wifi.
  //--Esta linea equivale--
  TA->EnviarArchivoViaWifi(archivo);

  //Antes de usar una clase fachada se tenian que crear el objeto de la via por la cual
  //queriamos enviar el archivo y llamar a sus metodos y asi recien poder enviar el archivo.
  //--A estas otras lineas--
  //Wifi* wifi = new Wifi();
  //if(wifi->Disponible()){
  //  wifi->Conectar();
  //  wifi->Autenticar();
  //  wifi->Enviar(archivo);
  //}
  //else{
  //  cout<<"El archivo no se pudo enviar."<<endl;
  //}
  
  return 0;
}
