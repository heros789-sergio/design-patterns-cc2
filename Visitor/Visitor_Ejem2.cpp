#include <iostream>
#include <array>

class Punto; //ConcreteComponentA
class Circulo; //ConcreteComponentB

class Visitor {
  public:
    virtual void VisitPunto(const Punto *element) const = 0;
    virtual void VisitCirculo(const Circulo *element) const = 0;
};

class Forma { //Component
 public:
  virtual ~Forma() {}
  virtual void Accept(Visitor *visitor) const = 0;
};

class Punto : public Forma { //ConcreteComponentA
  public:
    void Accept(Visitor *visitor) const override {
      visitor->VisitPunto(this);
    }
    std::string DibujarPunto() const {
      return "Punto";
    }
};

class Circulo : public Forma { //ConcreteComponentB
  public:
    void Accept(Visitor *visitor) const override {
      visitor->VisitCirculo(this);
    }
    std::string DibujarCirculo() const {
      return "Circulo";
    }
};

class XMLExportVisitor : public Visitor { //ConcreteVisitor1
  public:
    void VisitPunto(const Punto *element) const override {
      std::cout << element->DibujarPunto() << " + XMLExportVisitor\n";
    }

    void VisitCirculo(const Circulo *element) const override {
      std::cout << element->DibujarCirculo() << " + XMLExportVisitor\n";
    }
};

class HTMLExportVisitor : public Visitor { //ConcreteVisitor2
  public:
    void VisitPunto(const Punto *element) const override {
      std::cout << element->DibujarPunto() << " + HTMLVisitor\n";
    }
    void VisitCirculo(const Circulo *element) const override {
      std::cout << element->DibujarCirculo() << " + HTMLVisitor\n";
    }
};

void ClientCode(std::array<const Forma*, 2> components, Visitor *visitor) {
  for (const Forma *comp : components) {
    comp->Accept(visitor);
  }
}

int main() {
  std::array<const Forma *, 2> components = {new Punto, new Circulo};
  std::cout << "The client code funciona con todos los visitors a traves de la interfaz del Visitor Base:\n";
  XMLExportVisitor *visitorXML = new XMLExportVisitor;
  ClientCode(components, visitorXML);
  std::cout << "\n";
  std::cout << "Permite que el mismo client code funcione con diferentes tipos de visitors:\n";
  HTMLExportVisitor *visitorHTML = new HTMLExportVisitor;
  ClientCode(components, visitorHTML);

  for (const Forma *comp : components) {
    delete comp;
  }
  delete visitorXML;
  delete visitorHTML;

  return 0;
}