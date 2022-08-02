#include <iostream>
#include <string>
using namespace std;

class Almacen_tienda{
public:
	virtual void accept(class Visitor *)=0;
	//declaramos un metodo virtual acceptar que tomara como argumento
	//la interfaz base del visitante
};


class Bebidas:public Almacen_tienda{
public:
	void accept(Visitor *);
	//Cada componente concreto debe implementar el metodo accept de tal 
	// modo llame al metodo visitante correspondiente con la clase del 
	//componente
	void adquirir(){
		cout<<"SE INGRESO UNA BEBIDA AL SISTEMA\n";
	}
	void vender(){
		cout<<"SE HA VENDIDO UNA BEBIDA \n";
	}
	void dar_baja(){
		cout<<"SE HA DADO DE BAJA UNA BEBIDA\n ";
	}
	//Los componentes concretos pueden tener métodos especiales 
	//que no existen en su clase base o interfaz.
	//El Visitante aún puede usar estos métodos ya que
	//es consciente de la clase concreta del componente.
};

class Comida:public Almacen_tienda{
public:
	void accept(Visitor *);
	void adquirir(){
		cout<<"SE INGRESO UNA COMIDA AL SISTEMA\n";
	}
	void vender(){
		cout<<"SE HA VENDIDO UNA COMIDA \n";
	}
	void dar_baja(){
		cout<<"SE HA DADO DE BAJA UNA COMIDA\n ";
	}
};

class Objeto:public Almacen_tienda{
public:
	void accept(Visitor *);
	void adquirir(){
		cout<<"SE INGRESO UN OBJETO AL SISTEMA\n";
	}
	void vender(){
		cout<<"SE HA VENDIDO UN OBJETO\n ";
	}
	void dar_baja(){
		cout<<"SE HA DADO DE BAJA UN OBJETO\n ";
	}
};

class Visitor{
public:
	virtual void visit(Bebidas *)=0;
	virtual void visit(Comida *)=0;	
	virtual void visit(Objeto *)=0;
	
	static int cant_bebi,cant_comi,cant_ob;
	void total_almacen(){
		cout<<"\t\t----ALMACEN DE TIENDA---"<<endl;
		cout<<"BEBIDAS: "<<cant_bebi<<endl;
		cout<<"COMIDAS: "<<cant_comi<<endl;
		cout<<"OBJETOS: "<<cant_ob<<endl;
	}
};

int Visitor::cant_bebi = 0;
int Visitor::cant_comi = 0;
int Visitor::cant_ob = 0;

class adquirir: public Visitor{
public:
	adquirir(){//constructor
		cant_bebi=cant_comi=cant_ob=0;
	}
	void visit(Bebidas *a){
		++cant_bebi;
		a->adquirir();
	}
	void visit(Comida *b){
		++cant_comi;
		b->adquirir();
	}
	void visit(Objeto *c){
		++cant_ob;
		c->adquirir();
	}
};

class dar_baja: public Visitor{
public:
	dar_baja(){//constructor
		cant_bebi=cant_comi=cant_ob=0;
	}
	void visit(Bebidas *d){
		if(cant_bebi<=0){
			cout<<"NO HAY STOCK"<<endl;
		}
		else{
			--cant_bebi;
			d->dar_baja();
		}
	}
	void visit(Comida *e){
		if(cant_comi<=0){
			cout<<"NO HAY STOCK"<<endl;
		}
		else{
			--cant_comi;
			e->dar_baja();
		}
	}
	void visit(Objeto *f){
		if(cant_ob<=0){
			cout<<"NO HAY STOCK"<<endl;
		}
		else{
			--cant_ob;
			f->dar_baja();
		}
		
	}
};

class vender: public Visitor{
public:
	vender(){//constructor
		cant_bebi=cant_comi=cant_ob=0;
	}
	void visit(Bebidas *g){
		--cant_bebi;
		g->vender();
		cout<<"\n- LA COMPRA DE SU BEBIDA OBTENDRA EL 50% DE DESCUENTO "<<endl;
	}
	void visit(Comida *h){
		--cant_comi;
		h->vender();
		cout<<"\n- LA COMPRA DE SU COMIDA OBTENDRA EL 20% DE DESCUENTO "<<endl;
	}
	void visit(Objeto *i){
		--cant_ob;
		i->vender();
		cout<<"\n- LA COMPRA DE SU BEBIDA OBTENDRA EL 10% DE DESCUENTO "<<endl;
	}
};


void Bebidas::accept(Visitor *v){
	v->visit(this);
}
void Comida::accept(Visitor *v){
	v->visit(this);
}
void Objeto::accept(Visitor *v){
	v->visit(this);
}

string menu_seleccion(){
	string opcion2;
	cout<<"\n1.BEBIDAS"<<endl;
	cout<<"2.COMIDAS"<<endl;
	cout<<"3.OBJETO"<<endl;
	cout<<"4.SALIR"<<endl;
	cin>>opcion2;
	return opcion2;
}

int main(){
	Almacen_tienda *set[] = { new Bebidas, new Comida, new Objeto,0};
	string opcion,opcion2;
	int cantidad;
	adquirir ad_visitor;
	vender ve_visitor;
	dar_baja ba_visitor;
	while (true){
		cout<<"\t\t----------MENU----------"<<endl;
		cout<<"1.AGREGAR PRODUCTO"<<endl;
		cout<<"2.VENDER PRODUCTO"<<endl;
		cout<<"3.DAR DE BAJA PRODUCTO"<<endl;
		cout<<"4.MOSTRAR CANTIDAD DE PRODUCTOS"<<endl;
		cout<<"5.SALIR"<<endl;
		cin>>opcion;
		if(opcion=="1"){
			opcion2=menu_seleccion();
			if(opcion2=="1"){
				set[0]->accept(&ad_visitor);
			}
			else if(opcion2=="2"){
				set[1]->accept(&ad_visitor);
			}
			else if(opcion2=="3"){
				set[2]->accept(&ad_visitor);
			}	
			else if(opcion2=="4"){
				break;
			}
			else{
				cout<<"OPCION INCORRECTA"<<endl;
			}
		}
		else if(opcion=="2"){
			opcion2=menu_seleccion();
			if(opcion2=="1"){
				set[0]->accept(&ve_visitor);
			}
			else if(opcion2=="2"){
				set[1]->accept(&ve_visitor);
			}
			else if(opcion2=="3"){
				set[2]->accept(&ve_visitor);
			}	
			else if(opcion2=="4"){
				break;
			}
			else{
				cout<<"OPCION INCORRECTA"<<endl;
			}
		
		
		}
		else if(opcion=="3"){
			opcion2=menu_seleccion();
			if(opcion2=="1"){
				set[0]->accept(&ba_visitor);
			}
			else if(opcion2=="2"){
				set[1]->accept(&ba_visitor);
			}
			else if(opcion2=="3"){
				set[2]->accept(&ba_visitor);
			}	
			else if(opcion2=="4"){
				break;
			}
			else{
				cout<<"OPCION INCORRECTA"<<endl;
			}
		}
		else if(opcion=="4"){
			ba_visitor.total_almacen();
		}
		else if(opcion=="5"){
			break;
		}
		else{
			cout<<"OPCION INCORRECTA"<<endl;
		}
	}
}
