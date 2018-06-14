#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

struct nodo{
     int nro;
     struct nodo *izq, *der;
     nodo *padre;
};

typedef struct nodo *ABB;

nodo *crearNodo(int, nodo *);
void insertar(ABB &, int, nodo *, int);
void preOrden(ABB);
void inOrden(ABB);
void postOrden(ABB);
void verArbol(ABB, int);
int duplicado(ABB, int, int);
void ver(ABB, int);
void eliminar(ABB, int);
void eliminarNodo(nodo *);
nodo *Menor(nodo *);
void Cambiar(ABB, ABB);
void Destruir(ABB);

main()
{
    ABB arbol = NULL;

    int n=0, x=0, opc=0, dato;

	do{
		system("cls");
		
		cout<<"1. Ingresar Datos"<<endl;
		cout<<"2. Mostrar Preorden"<<endl;
		cout<<"3. Mostrar Inorden"<<endl;
		cout<<"4. Mostrar Postorden"<<endl;
		cout<<"5. Eliminar un Dato del Arbol"<<endl;
		cout<<endl;
		cout<<"elige opcion"<<endl;
		cin>>opc;
		
		switch(opc){
			
			case 1:
				n++;
			    cout<<" Valor del nodo "<<n<<": ";
			    cin>>x;
			    insertar(arbol, x, NULL, n);
				break;
			
			case 2:
				cout << "\n\n Preorden:  ";   preOrden(arbol);
				break;
			
			
				cout << "\n\n Inorden:  ";   inOrden(arbol);
				break;						
			
			
				cout << "\n\n Postorden::  ";   postOrden(arbol);
				break;
			
			
			case 5:
				cout << "\n\n Datos Ingresados:  ";
				verArbol(arbol, n);
				cout<<endl;
		        cout << "Ingrese el numero a eliminar " << '\n';
		        cin >> dato;
		        eliminar(arbol, dato);
		        cout << "Dato eliminado " << '\n';
		        break;
			
			default:
				cout<<"OPCION IN EXISTENTE"<<endl;
				getch();
				break;
		}
		if(opc>=2 && opc<=6){
			cout<<endl;
			cout<<endl;
			cout<<endl;
			ver(arbol, n);
			getch();
			
		}
	}
	while(opc!=7);
}

ABB crearNodo(int x, nodo *padre)
{
    ABB nuevoNodo = new(struct nodo);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    nuevoNodo->padre=padre;
	return nuevoNodo;
}

void insertar(ABB &arbol, int x, nodo *padre, int n)
{
	int d;
	d=duplicado(arbol, n, x);
	if(d==1){
		cout<<"No insertar datos iguales"<<endl;
		getch();
	}
	else{
		if(arbol==NULL)
	    {
	    	nodo *nuevoNodo = crearNodo(x, padre);
	    	arbol = crearNodo(x, padre);
	    }
	    else {
			if(x < arbol->nro)
		        insertar(arbol->izq, x, arbol, n);
		    else{
				if(x > arbol->nro, arbol)
		        	insertar(arbol->der, x, arbol, n);
		    	else{
		    		cout<<"No insertar datos iguales"<<endl;
		    	getch();
		    	}
			}
		}	
	}
}

void preOrden(ABB arbol)
{
    if(arbol!=NULL)
    {
        cout << arbol->nro <<" - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void inOrden(ABB arbol)
{
    if(arbol!=NULL)
    {
        inOrden(arbol->izq);
        cout << arbol->nro << " - ";
        inOrden(arbol->der);
    }
}

void postOrden(ABB arbol)
{
    if(arbol!=NULL)
    {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << arbol->nro << " - ";
    }
}

void verArbol(ABB arbol, int n)
{
    if(arbol==NULL)
        return;
    cout<< arbol->nro <<" - ";
	verArbol(arbol->der, n+1);
    verArbol(arbol->izq, n+1);
}

void ver(ABB arbol, int n)
{
 	
 	if(arbol==NULL)
        return;
    ver(arbol->der, n+1);

    for(int i=0; i<n; i++)
        cout<<"   ";

    cout<<"|"<< arbol->nro <<"|"<<endl;

    ver(arbol->izq, n+1);
}

void eliminar(ABB arbol, int n) {
	if (arbol == NULL) {
		return;
	}
	else{
		if (n < arbol -> nro) {
		    eliminar(arbol->izq, n);
		}
		else{
			if (n > arbol -> nro) {
		   		eliminar(arbol -> der, n);
		  	}
			else {
		    	eliminarNodo(arbol);
		  	}
		}
	}
}

void eliminarNodo(nodo *nodoEliminar) {
  	if (nodoEliminar -> izq && nodoEliminar -> der) {
	    nodo *menor = Menor(nodoEliminar -> der);
	    nodoEliminar -> nro = menor -> nro;
	    eliminarNodo(menor);
  	}
	else {
	  	if (nodoEliminar -> izq) {
		    Cambiar(nodoEliminar, nodoEliminar -> izq);
		    Destruir(nodoEliminar);
		}
	  	else {
		  	if (nodoEliminar -> der) {
			    Cambiar(nodoEliminar, nodoEliminar -> der);
			    Destruir(nodoEliminar);
	  		}
		  	else{
			    Cambiar(nodoEliminar, NULL);
			    Destruir(nodoEliminar);
		  	}
		}
	}
}

nodo *Menor(nodo *arbol){
  if (arbol == NULL) {
    return NULL;
  }
  if (arbol -> izq) {
    return Menor(arbol -> izq);
  }
  else{
    return arbol;
  }
}

void Destruir(nodo *nodo) {
  nodo -> izq = NULL;
  nodo -> der = NULL;

  delete nodo;
}


void Cambiar(nodo *arbol, nodo *nuevoNodo) {
  if (arbol->padre) {
    if (arbol -> nro == arbol -> padre -> izq -> nro) {
      arbol -> padre -> izq = nuevoNodo;
    }
	else{ 
		if (arbol -> nro == arbol -> padre -> der -> nro) {
			arbol -> padre -> der = nuevoNodo;
    	}
	}

  }
  if (nuevoNodo) {
    nuevoNodo -> padre = arbol -> padre;
  }
}

int duplicado(ABB arbol, int n, int d)
{
    int a=0;
	if(arbol==NULL)
        return a;
    if(arbol->nro==d){
		a=1;
		return a;
	}
	verArbol(arbol->der, n+1);
    verArbol(arbol->izq, n+1);
}
