#include <iostream>
#include <unordered_map>
#include <string>
#include <list>

class DataCompartida{ // [ SharedState = Estado Intrinseco]
public:
    std::string nombre;
    std::string color;
    std::string textura;

    DataCompartida(const std::string &nombre, const std::string &color, const std::string &textura){
        this->nombre = nombre;
        this->color = color;
        this->textura = textura;
    }
    friend std::ostream &operator<<(std::ostream &os, const DataCompartida &dc){
        return os<<"[ "<<dc.nombre<<" - "<<dc.color<<" - "<<dc.textura<<" ]";
    }
};
class DataUnica{ // [UniqueState = Estado Extrinseco]
public:
    int x;
    int y;
    DataUnica(const int &x, const int &y){
        this->x = x;
        this->y = y;
    }
    friend std::ostream &operator<<(std::ostream &os, const DataUnica &du){
        return os<<"[ Ubicacion ("<<du.x<<" , "<<du.y<<") ]";
    }
};
class Flyweight{
private:
    DataCompartida* data_compartida;
public:
    Flyweight(const DataCompartida* data_compartida) {
        this->data_compartida = new DataCompartida(*data_compartida);
    }
    Flyweight(const Flyweight& other) { //constructor copia
        this->data_compartida = new DataCompartida(*other.data_compartida);
    }
    ~Flyweight() {
        delete data_compartida;
    }
    DataCompartida* getDataCompartida() const {
        return data_compartida;
    }
    void MostrarInfo(const DataUnica &data_unica) const {
        std::cout<<"Flyweight:\nEstado Intrinseco(DataCompartida) => ("<<*data_compartida<< ")\n";
        std::cout<<"Estado Extrinseco(DataUnica) => ("<<data_unica<<")\n";
    }
    void DibujarArbol(const DataUnica &data_unica) const{
        std::cout<<"Dibujando Arbol ("<<*data_compartida<<") en las coordenadas: "<<data_unica<<std::endl;
    }
};

using namespace std;
class ArbolFactory{ //FlyweightFactory
private:
    // clave(string),valor(flyweight)
    unordered_map <string, Flyweight> flyweights_; // Almacena todos los flyweights del programa
    std::string GetKey(const DataCompartida &ss) const{ // retorna key = (marca-modelo-color)
        return ss.nombre + "-" + ss.color + "-" + ss.textura; 
    }
public:
    ArbolFactory(std::initializer_list<DataCompartida> share_states){ //parametro: lista de share_states
        //Insertamos flyweights. Ya que esta vacio nuestro map no es necesario comprobar si hay memoria reutilizable
        for (const DataCompartida &dc : share_states){ 
            this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(dc), Flyweight(&dc)));
        }
    }
    Flyweight GetFlyweight(const DataCompartida &shared_state){
        std::string key = this->GetKey(shared_state);
        if (this->flyweights_.find(key) == this->flyweights_.end()) { //unordered_map.find(key); //Se usa para buscar una clave específica
            std::cout << "ArbolFactory: No se puede encontrar un flyweight. Creando uno nuevo...\n";
            this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
        }
        else {
            std::cout << "ArbolFactory: Reutilizacion de flyweight existente\n";
        }
        return this->flyweights_.at(key); //retorna la referencia al valor mapeado del elemento con un valor clave equivalente
    }
    void ListFlyweights() const{ //Muestra los flyweights por consola
        size_t numFlywights = this->flyweights_.size(); //numero de elementos del unordered_map
        std::cout << "\nFlyweightFactory: Tengo "<<numFlywights<<" flyweights:\n";
        for (std::pair<std::string, Flyweight> pair : this->flyweights_) {
            std::cout<<pair.first<< "\n";
        }
    }
};
//CrearNuevoArbol(factory,x,y,nombre,color,textura)
void CrearNuevoArbol(
    ArbolFactory &ff,const int &x, const int &y, 
    const std::string &nombre, const std::string &color, const std::string &textura) {

        std::cout<<"\nCliente: Aniadiendo un coche a la base de datos.\n";
        const Flyweight &flyweight = ff.GetFlyweight({nombre, color, textura});
        //El código del cliente almacena o calcula el extrinsic state y lo pasa a los métodos de flyweight.
        //flyweight.MostrarInfo({x,y});
        flyweight.DibujarArbol({x,y});
}

int main() {
    ArbolFactory *factory = new ArbolFactory({
                                                {"Pino", "Marron", "Lisa"}, 
                                                {"Acacia", "Marron", "Lisa"}, 
                                                {"Roble", "Marron Oscuro", "Aspera"}, 
                                                {"Roble", "Marron Oscuro", "Brillosa"}, 
                                                {"Abedul", "Crema", "Aspera"}
                                            });
    factory->ListFlyweights();
    std::cout<<"--------------------------------------------------------------------------"<<std::endl;
    //Se intentan agregar 2 nuevos
    CrearNuevoArbol(*factory, 58, 10, "Abedul", "Crema", "Aspera"); //Reutiliza flyweight existente
    CrearNuevoArbol(*factory, 45, 22, "Roble", "Marron Oscuro","Lisa"); //Crea un flyweight nuevo
    factory->ListFlyweights();
    delete factory;
    return 0;
}