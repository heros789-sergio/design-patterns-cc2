#include <iostream>
#include <string>
#include <unordered_map> //internamente se implementa utilizando Tablas de Hash
#include <initializer_list>
// intrinsic state = datos inmutables duplicados en muchos objetos
// extrinsic state = unico de cada objeto
/*
Permite colocar más objetos en la cantidad disponible de RAM al compartir 
partes comunes del estado entre varios objetos, en lugar de mantener todos 
los datos en cada objeto.
*/

struct SharedState { //objeto compartido
    std::string marca;
    std::string modelo;
    std::string color;

    SharedState(const std::string &marca, const std::string &modelo, const std::string &color){
        this->marca = marca;
        this->modelo = modelo;
        this->color = color;
    }
    friend std::ostream &operator<<(std::ostream &os, const SharedState &ss){
        return os<<"[ "<<ss.marca<<" - "<<ss.modelo<<" - "<<ss.color<<" ]";
    }
};
struct UniqueState { //objeto no compartido
    std::string duenio;
    std::string placa;
    UniqueState(const std::string &duenio, const std::string &placa){
        this->duenio = duenio;
        this->placa = placa;
    }
    friend std::ostream &operator<<(std::ostream &os, const UniqueState &us){
        return os<<"[ "<<us.duenio<<" , "<<us.placa<<" ]";
    }
};

// Contiene la porcion del objeto original que se puede compartir entre varios objetos
// El estado almacenado dentro de un Flyweight se llama intrínseco. 
// El estado que se pasa a los métodos del Flyweight se llama extrínseco.
class Flyweight { 
    private:
        SharedState* shared_state_;
    public:
        Flyweight(const SharedState* shared_state) {
            this->shared_state_ = new SharedState(*shared_state);
        }
        Flyweight(const Flyweight& other) { //constructor copia
            this->shared_state_ = new SharedState(*other.shared_state_);
        }
        ~Flyweight() {
            delete shared_state_;
        }
        SharedState* shared_state() const {
            return shared_state_;
        }
        void Operacion(const UniqueState &unique_state) const {
            std::cout<<"Flyweight: Displaying shared ("<<*shared_state_<< ") and unique ("<<unique_state<<") state\n";
        }
};
// La clase Contexto contiene el estado extrínseco, único en todos los objetos originales.
// Cuando un contexto se empareja con uno de los objetos flyweight, representa el estado completo del objeto original.

class FlyweightFactory {
    private:
        std::unordered_map<std::string, Flyweight> flyweights_; // clave(str) , valor(flyweight)
        std::string GetKey(const SharedState &ss) const{ // retorna key = (marca_modelo_color)
            return ss.marca + "_" + ss.modelo + "_" + ss.color;
        }
    public:
        FlyweightFactory(std::initializer_list<SharedState> share_states){
            for (const SharedState &ss : share_states){
                this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
            }
        }
        Flyweight GetFlyweight(const SharedState &shared_state){
            std::string key = this->GetKey(shared_state);
            if (this->flyweights_.find(key) == this->flyweights_.end()) { //unordered_map.find(key); //Se usa para buscar una clave específica
                std::cout << "FlyweightFactory: No se puede encontrar un flyweight. Creando uno nuevo...\n";
                this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
            }
            else {
                std::cout << "FlyweightFactory: Reutilizacion de flyweight existente\n";
            }
            return this->flyweights_.at(key); //retorna la referencia al valor mapeado del elemento con un valor clave equivalente
        }
        void ListFlyweights() const{
            size_t count = this->flyweights_.size();
            std::cout << "\nFlyweightFactory: Tengo "<<count<<" flyweights:\n";
            for (std::pair<std::string, Flyweight> pair : this->flyweights_) {
                std::cout << pair.first << "\n";
            }
        }
};

void AgregarAutomovilADatabaseDeLaPolicia(
    FlyweightFactory &ff, const std::string &placas, const std::string &duenio,
    const std::string &marca, const std::string &modelo, const std::string &color) {

        std::cout<<"\nCliente: Aniadiendo un coche a la base de datos.\n";
        const Flyweight &flyweight = ff.GetFlyweight({marca, modelo, color});
        //El código del cliente almacena o calcula el extrinsic state y lo pasa a los métodos de flyweight.
        flyweight.Operacion({duenio, placas});
}

int main(){
    FlyweightFactory *factory = new FlyweightFactory({
                                                        {"Chevrolet", "Camaro2018", "pink"}, 
                                                        {"Mercedes Benz", "C300", "black"}, 
                                                        {"Mercedes Benz", "C500", "red"}, 
                                                        {"BMW", "M5", "red"}, 
                                                        {"BMW", "X6", "white"}}
                                                    );
    factory->ListFlyweights();
    std::cout<<"--------------------------------------------------------------------------"<<std::endl;
    //Se intentan agregar 2 nuevos
    AgregarAutomovilADatabaseDeLaPolicia(*factory, "CL234IR", "James Doe", "BMW", "M5", "red"); //Reutiliza flyweight existente
    AgregarAutomovilADatabaseDeLaPolicia(*factory, "CL234IR", "James Doe", "BMW", "X1", "red"); //Crea un flyweight nuevo
    factory->ListFlyweights();
    delete factory;
    return 0;
}

