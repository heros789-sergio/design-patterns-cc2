//Nelzon
#include <iostream>
/**
 * La interfaz "Subject" declara operaciones comunes tanto para "RealSubject" como para el
 * "Proxy". Mientras el cliente trabaje con "RealSubject" utilizando esta interfaz,
 * podrás pasarle un "proxy" en lugar de un "RealSubject".
*/
//-----------------------SUBJECT----------------------------
class Subject
{
public:
    virtual void Solicitud() const = 0;//método virtual puro, clase abstracta Subject
    /*
    -   Una función virtual pura es una función miembro de la clase base 
        cuya única declaración se proporciona en la clase base y debe 
        definirse en la clase derivada; de lo contrario, la clase derivada 
        también se vuelve abstracta.
    -   La clase base que tiene una función virtual pura se vuelve abstracta, 
        es decir, no se puede instanciar.
    */
};
//---------------------------------------------------------

/**
 * El "RealSubject" contiene cierta lógica comercial central. Por lo general, "RealSubjects" son
 * capaz de hacer algún trabajo útil que también puede ser muy lento o sensible -
 * p.ej. corregir los datos de entrada. Un "Proxy" puede resolver estos problemas sin ningún
 * cambio en el código de "RealSubject".
*/
//-----------------------REALSUBJECT----------------------------
class RealSubject : public Subject
{
    public:
        void Solicitud() const override//misma funcion, pero modificada,por el virtual
        {
            std::cout << "RealSubject: Solicitud de tramitacion realizada.\n";//Mensaje del Real Subject
        }
};
//---------------------------------------------------------

/**
 * El "Proxy" tiene una interfaz idéntica a "RealSubject".
*/
//-----------------------PROXY----------------------------
class Proxy : public Subject
{
    /**
     * @var "RealSubject", al igual que este anterior
    */
    private:
        RealSubject *real_subject_;//puntero de tipo RealSubject, que apuntara a este tipo de dato
        bool ComprobarAcceso() const
        {
            // Comprobamos el acceso, antes de ir a lo otro
            std::cout << "Proxy: Comprobacion del acceso antes de disparar una solicitud real.\n";
            return true;
        }
        void AccesoRegistro() const
        {
            //una vez ya se haya accedido
            std::cout << "Proxy: Se ha Registrado la hora de la solicitud hecha.\n";
        }

        /**
            - lazy-loaded (carga diferida)
         La carga diferida es un patrón de diseño comúnmente usado en la programación informática 
         que consiste en "retrasar la carga o inicialización de un objeto" hasta el mismo momento de 
         su utilización. Esto contribuye a la eficiencia de los programas, evitando la precarga de 
         objetos que podrían no llegar a utilizarse.
        */
        /**
         * El "Proxy" mantiene una referencia a un objeto de la clase "RealSubject". Eso
         * puede ser cargado de forma diferida(lazy-loaded) o pasado al 
         * "Proxy" por el cliente.
        */
    public:
        //constructor
        Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)){}
        /*
            this->real_subject_=new RealSubject(*real_subject);
        */
        ~Proxy()//destructor
        {
            delete real_subject_;
        }
        /**
         * Las aplicaciones más comunes del patrón "Proxy" son la carga diferida,
         * almacenamiento en caché, control de acceso, registro, etc. Un "Proxy" puede realizar una de
         * estas cosas y luego, dependiendo del resultado, pasar la ejecución al
         * mismo método en un objeto "RealSubject" vinculado.
        */
        void Solicitud() const override{ //override nos da a conocer que esta función ya no será virtual
            if (this->ComprobarAcceso())
            {
                this->real_subject_->Solicitud();
                this->AccesoRegistro();
            }
        }
};
//---------------------------------------------------------


/**
 * Se supone que el código del cliente funciona con todos los objetos (tanto Subjects como
 * Proxies) a través de la interfaz "Subject" para admitir tanto "RealSubjects" como
 * Proxies. Sin embargo, en la vida real, los clientes trabajan principalmente con sus "RealSubject".
 * directamente. En este caso, para implementar el patrón más fácilmente, puede extender
 * su "Proxy" de la clase del "RealSubject".
*/
void ClientCode(const Subject &subject)
{
    // ...
    subject.Solicitud();
    // ...
}

int main()
{
    std::cout << "Client: Ejecutar el codigo del cliente con un real subject:\n";///sin el proxy
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);

    std::cout << "\n";
    std::cout << "Client: Ejecutar el mismo codigo de cliente con un proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}