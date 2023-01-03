#include <iostream>
#include <fstream>

using namespace std;
int op;

class nodo
{
	public:
	int num;
	nodo *arri;
	nodo *aba;
	nodo *izq;
	nodo *der;
	
};

nodo *inicio;

class Matriz{
	
	public:
		//constructor
		Matriz(){
			
		}
		
     
//metodos
	public:   
		
void mostrar()
{
	int f = 1;			//fila inicia en 1
	nodo *aux10 = inicio;
	nodo *aux20 = aux10->aba;
	
	while(aux20!=NULL)
	{
		nodo *aux3F = aux20->der;
		cout<<"Fila "<<f<<": "<<aux20->num<<" -> ";
		while(aux3F!=NULL)
		{
			cout<<aux3F->num<<" -> ";
			aux3F = aux3F->der;
		}
		cout<<endl;
		f++;
		aux20 = aux20->aba;
	}
}

void mostrarC() //mostrar por columna
{
	int c = 0;
	nodo *aux1 = inicio;
	nodo *ant = aux1;
	nodo *aux2 = aux1->der;
	
	while(ant!=NULL)
	{
		nodo *aux3c = ant->aba;
		cout<<"C "<<c<<": "<<ant->num<<"->";
		while(aux3c!=NULL)
		{
			cout<<aux3c->num<<"->";
			aux3c = aux3c->aba;
		}
		cout<<endl;
		c++;
		ant = ant->der;
	}
}

nodo * busquedad(int c)
{
	nodo *aux=inicio;
	bool encontrado=false;
	while (aux!=NULL && !encontrado)
	{
		if (aux->num==c)
			encontrado=true;
		else
			aux=aux->der;
	}
	if (encontrado)
		return aux;
	else
		return NULL;
}

void insercion(int col, int d)
{
	nodo *auxC = busquedad(col); //llamamos metodo para verificar que exista
	
	
	if(inicio == NULL) //comparamos incio con null
	{
		nodo *ins1 = new nodo(); //creamos nuevo aux
		ins1->num = col; //recibe el numero de columna
		ins1->arri = NULL;
		ins1->der = NULL; //iniciamos en null
		ins1->izq = NULL;
		inicio = ins1; //inicio es igual a nuestro aux
		
		nodo *ins2 = new nodo(); //creamos un nuevo aux para insertar datos en fila
		ins2->num = d; //en su parte num sera igual a b (dato que recibe)
		ins1->aba = ins2; //columna en su parte abajo es fila (dato que ingresamos)
		ins2->aba = NULL;
		ins2->der = NULL; //iniciamos en null
		ins2->izq = NULL;
		ins2->arri = ins1;// fila en su parte arriba es columna
		
	}
	else if(auxC == NULL) //auxC es el que llama a verificar que exista columna
	{
		nodo *aux3C=inicio; //nuevo aux3 y se situa en inicio
		nodo *antC=inicio; //nuevo aux anterior que guardara la posicion del incio cuando este salte
		nodo *aux4 = inicio->aba; 
		nodo *aux5 = inicio->aba;//creamos nuevos aux para la parte abajo del inicio
		bool colocado = false; //levantamos bandera de busqueda
		while (colocado!=true) // sino ha sido encontrado
		{
			if (col > aux3C->num) //columna > incio en su parte numero y se ordenan las columnas mayores
			{
				if (aux3C->der!=NULL) //inicio en su parte derecha no esta vacio
				{
					antC=aux3C; //anterior guarda la posicion de aux3C (inicio)
					aux3C=aux3C->der; //Aux3C avanza a la derecha
					aux5 = aux4; //aux5 es igual a aux4 
					aux4 = aux4->der; //aux4 avanza a la derecha
				}
				else
				{
					nodo *nC=new nodo(); //creamos un nuevo aux nc (numero columna)
					nC->num=col; //toma el numero ingresado en a
			
					nodo *nF2=new nodo(); //creamos un nuevoa ux nf (dato de fila)
					nF2->num=d;//toma el numero ingresado en b
			
					nC->aba=nF2; //numero de columna en su parte abajo tiene a numero de fila
					nC->arri = NULL; 
					nC->der = NULL; //iniciamos en null
					nC->izq = aux3C; //numero de columna en su parte izquierda recibe aux3C (trae columna)
					
					nF2->aba = NULL;// iniciamos en null
					nF2->arri = nC; //numero de fila en su parte arriba es numero de columna
					nF2->izq = aux4;//numero de fila en su parte izquierda sera aux4 (similar a anterior)
					nF2->der = NULL; //iniciamos en null
					
					aux3C->der = nC; // aux3C en su parte derecha es numero de columna
					aux4->der = nF2; //aux4 en su parte derecha es dato de fila
					colocado=true; //ha sido encontrado
				}
			}
			else
			{
				nodo *nuevoC = new nodo(); //creamos un nuevo aux
				nuevoC->num = col;//nuevo aucx en su parte numero es igual a la a (numero que recibe la columna)
				
				nodo *nC2 = new nodo(); //creamos un nuevo aux
				nC2->num = d; //nuevo aucx en su parte numero es igual a, b (dato que recibe en la fila)
				
				if(col < inicio->num) ////columna < incio en su parte numero
				{
					nuevoC->der = aux3C;//el nuevo aux en su parte derecha es igual al aux3c (inicio)
					nuevoC->izq = NULL;
					nuevoC->arri = NULL;//iniciamos en null
					nuevoC->aba = nC2; //el nuevo aux en su parte abajo es igual a numero de columna
					aux3C->izq = nuevoC;//aux3c (inicio) en su parte izquierda es igual al nuevo
					inicio = nuevoC; //inicio es igual a nuevo
					
					nC2->aba = NULL; //inicia en null
					nC2->arri = nuevoC;//nc2 en su parte arriba se iguala a nuevoC (inicio)
					nC2->der = aux4; //nc2 en su parte derecha es igual a aux4
					nC2->izq = NULL;//inicia en null
					
					aux4->izq = nC2; //aux4 en su parte izquierda es nc2 (inicio)
				}
				else
				{
					nuevoC->der= aux3C; 
					nuevoC->izq = antC;
					nuevoC->arri = NULL;
					nuevoC->aba = nC2;
					antC->der = nuevoC;
					aux3C->izq = nuevoC;
			
					nC2->aba = NULL;
					nC2->arri = nuevoC;
					nC2->der = aux4;
					nC2->izq = aux5;
					aux4->izq = nC2;
					aux5->der = nC2;
				} 
				colocado=true;
			}
		}
	}
	else if(auxC != NULL) //comprobacion que ya existe columna
	{
		int cont = 0, cont2 = 0, cont3 = 0;
		nodo *aux2 = inicio;
		nodo *antC = inicio;
		nodo *aux3 = inicio->aba;
		nodo *aux4 = inicio->aba;
		
		nodo *nuevo = new nodo();
		nuevo->num = d;
		
		if(auxC == inicio) //verifica que exista al inicio y coloca el dato abajo
		{
			while(aux3->aba!=NULL)		//ahora partimos que el nodo existente en su parte abajo apunta a NULL
				aux3 = aux3->aba;		// se iguala a el mismo apuntando hacia abajo (para agregar un nuevo nodo)
			
			aux3->aba = nuevo;			//el nuevo se iguala al existente
			nuevo->aba = NULL;			//el nuevo apunta a null hacia abajo
			nuevo->izq = NULL;			//de igual forma a la izquier toamndo el lugar del anterior
			nuevo->arri = aux3;			//ahora el nuevo apunta hacia arriba que es el anterior
			
			aux3 = auxC->aba;			//es como un enter ALV
			while(aux3->aba!=NULL)		
			{
				aux3 = aux3->aba;
				cont++;					
			}
			aux2 = aux2->der;			
			while(aux2!=NULL)
			{
				aux4 = aux2->aba;
				while(aux4->aba!=NULL)
				{
					aux4 = aux4->aba;
					cont2++;
				}
				if(cont == cont2)
					break;
				cont2 = 0;	
				aux2 = aux2->der;
			}
			
			if(aux2==NULL)
				nuevo->der= NULL;
			else if(aux2!=NULL)
			{
				nuevo->der = aux4;
				aux4->izq = nuevo;
			}
			cont = 0;
		}
		else
		{
			aux2 = auxC->der;
			antC = auxC->izq;
			
			if(aux2!=NULL)
				aux3 = aux2->aba;
			if(antC!=NULL)
				aux4 = antC->aba;
			
			nodo *aux5 = auxC->aba;
			
			while(aux5->aba != NULL)
				aux5 = aux5->aba;
			
			aux5->aba = nuevo;
			nuevo->arri = aux5;
			nuevo->aba = NULL;
			
			aux5 = auxC;
			aux5 = aux5->aba;
			while(aux5->aba != NULL)
			{
				aux5 = aux5->aba;
				cont++;
			}

			while(aux2!=NULL)
			{
				aux3 = aux2->aba;
				while(aux3->aba!=NULL)
				{
					aux3 = aux3->aba;
					cont2++;
				}
				if(cont == cont2)
					break;
				aux2 = aux2->der;
			}
			
			if(aux2==NULL)
				nuevo->der = NULL;
			else if(aux2!=NULL)
			{
				nuevo->der= aux3;
				aux3->izq = nuevo;
			}
			
			while(antC!=NULL)
			{
				aux4 = antC->aba;
				while(aux4->aba!=NULL)
				{
					aux4 = aux4->aba;
					cont3++;
				}
				if(cont == cont3)
					break;
				antC = antC->izq;
			}
			
			if(antC==NULL)
				nuevo->izq = NULL;
			else if(antC!=NULL)
			{
				nuevo->izq= aux4;
				aux4->der= nuevo;
			}
		}
	}
}

void graficacion()
{
	ofstream s1;
	s1.open("serieI.dot", ios::out);
	s1<<"digraph G{"<<endl;
	s1<<"label=\"SERIE I\""<<endl;
	s1<<"labelloc=\"t\""<<endl;
	s1<<"node [shape=rectangle]"<<endl;
	
	nodo* aux = inicio;
	nodo* ant;
	
	s1<<"rank= same{";
	
	while(aux!=NULL)
	{
		s1<<aux->num;
		
		if(aux->der!=NULL)
			s1<<"->";
		
		ant = aux;
		aux= aux->der;

	}
	s1<<"}"<<endl;
	
	s1<<"rank= same{";
	
	while(ant!=NULL)
	{
		s1<<ant->num;
		
		if(ant->izq!=NULL)
			s1<<"->";
			
		ant = ant->izq;

	}
	s1<<"}"<<endl;
	
	aux = inicio;
	while(aux != NULL)
	{
		s1<<aux->num<<"->";
		nodo *aux2 = aux->aba;
		while(aux2 != NULL)
		{
			s1<<aux2->num;
			if(aux2->aba!=NULL)
				s1<<"->";
			aux2 = aux2->aba;
		}
		s1<<";"<<endl;
		ant= aux;
		aux = aux->der;
	}
	s1<<endl;
	
	while(ant != NULL)
	{
		nodo *aux2 = ant->aba;
		nodo *aux3;
		while(aux2 != NULL)
		{
			aux3 = aux2;
			aux2 = aux2->aba;
		}
		
		aux2 = aux3;
		
		while(aux2!=NULL)
		{
			s1<<aux2->num;
			
			if(aux2->arri!=NULL)
				s1<<"->";
				
			aux2 = aux2->arri;
		}
		s1<<";"<<endl;
		
		ant = ant->izq;
	}
	s1<<endl;
	aux = inicio;
	aux = aux->aba;
	nodo *ant2;
	while(aux!=NULL)
	{
		ant = aux;
		s1<<"rank= same{";
		while(ant!=NULL)
		{
			s1<<ant->num;
			if(ant->der != NULL)
				s1<<"->";
			ant2 = ant;
			ant = ant->der;
		}
		s1<<"}"<<endl;
		ant= ant2;
		s1<<"rank= same{";
		
		while(ant!=NULL)
		{
			s1<<ant->num;
			if(ant->izq != NULL)
				s1<<"->";
			ant = ant->izq;
		}
		s1<<"}"<<endl;
		aux = aux->aba;
	}
	
	s1<<"}"<<endl;
	s1.close();
	system("dot -Tpng serieI.dot > serieI.png ");
	system("serieI.png");
}
};


