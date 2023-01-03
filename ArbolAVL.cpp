#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include <sstream>
#include <vector>

using namespace std;

int tam;
double tiempo;
ofstream AAVL;

class avl2
{
	public:
	int num2;
	avl2 *abajo2;
};

class avl
{ 
	public:
	int num;
	int arriba;
	
	avl *izquierda;
	avl *derecha;
	avl2 *abajo;
};




class arbolavl{
	public:
		
	avl *raiz;
		
	//constructor
	arbolavl(){
		
	}
	
	//metodos
	public:

int altura(avl *aux)
{
    return aux == NULL ? -1 : aux->arriba;
}

int max(int l, int r)
{
    return l > r ? l : r;
}

avl *rsi(avl *aux2)
{
    avl *aux1 = aux2->izquierda;
    aux2->izquierda = aux1->derecha;
    aux1->derecha = aux2;
    aux2->arriba = max(altura(aux2->izquierda), altura(aux2->derecha)) + 1;
    aux1->arriba = max(altura(aux1->izquierda), aux2->arriba) + 1;
    return aux1;
}
 
avl *rsd(avl *aux1)
{
    avl *aux2 = aux1->derecha;
    aux1->derecha = aux2->izquierda;
    aux2->izquierda = aux1;
    aux1->arriba = max(altura(aux1->izquierda), altura(aux1->derecha)) + 1;
    aux2->arriba = max(altura(aux2->derecha), aux1->arriba) + 1;
    return aux2;
}

avl *rdi(avl *aux3)
{
    aux3->izquierda = rsd(aux3->izquierda);
    return rsi(aux3);
}

avl *rdd(avl *aux1)
{
    aux1->derecha = rsi(aux1->derecha);
    return rsd(aux1);
}

avl *buscar(avl *r, int val)
{
    bool found = false;
    while ((r != NULL) && !found)
    {
        int rval = r->num;
        
        if (val < rval)
            r = r->izquierda;
            
        else if (val > rval)
            r = r->derecha;
            
        else
        {
            found = true;
            break;
        }
        found = buscar(r, val);
    }
	
    return r;
}

avl *insertarr(int x, avl *tb)
{
	if (tb == NULL)
    {
    	tb = new avl();
        tb->num = x;
        tb->arriba = 0;
        tb->derecha = NULL;
        tb->izquierda = NULL;
	}
        
    else if (x < tb->num)
    { 
        tb->izquierda = insertarr(x, tb->izquierda);
        if (altura(tb->izquierda) - altura(tb->derecha) == 2)
           	if (x < tb->izquierda->num)
                tb = rsi(tb);
            else
                tb = rdi(tb);
    }
    else if (x > tb->num)
    {
       	tb->derecha = insertarr(x, tb->derecha);
        if (altura(tb->derecha) - altura(tb->izquierda) == 2)
            if (x > tb->derecha->num)
                tb = rsd(tb);
            else
                tb = rdd(tb);
    }
    tb->arriba = max(altura(tb->izquierda), altura(tb->derecha)) + 1;
    return tb;	
}

avl *buscarr(int n){
	avl *aux = raiz;
	bool encontrado=false;
	unsigned tb5, tb6;
	tb5=clock();
	while (aux!=NULL && !encontrado){
		
		if(aux->num== n)
		{
			encontrado = true;
		}
		else if(n> aux->num)
		{
			if(aux->derecha==NULL)
			{
				return NULL;
			}
			else
				aux=aux->derecha;
		}
		else
		{
			if(n<aux->num)
			{
				
				if(aux->izquierda== NULL)
				{
					
					return NULL;
					
				}
				else
					aux=aux->izquierda;
				
			}	
		}			
	}
	tb6 = clock();
	tiempo = (double(tb6-tb5)/CLOCKS_PER_SEC);
	if(encontrado)
		return aux;
		
	else 
		return NULL;
}

void insertar2(int a, int d)
{
	avl *aux = buscarr(a);
	
	if(aux->abajo == NULL)
	{
		avl2 *aux3 = new avl2();
		aux3->num2 = d;
	
		aux->abajo = aux3;
		aux3->abajo2 = NULL;
	}
	else
	{
		avl2 *auxN = aux->abajo;
		avl2 *aux3 = new avl2();
		aux3->num2 = d;
		
		while(auxN->abajo2!=NULL)
		{
			auxN = auxN->abajo2;
		}
		
		auxN->abajo2 = aux3;
		aux3->abajo2 = NULL;
	}
	
	
}

void insertar(int d)
{
    raiz = insertarr(d, raiz);
}

void cargar()
{
	ifstream arbolAvlN, arbolAvlNum;
	string txt3, txt4;
	int nume,n,nume2;
	vector<int> vc;
	
	arbolAvlN.open("Index.txt", ios::in);
	arbolAvlNum.open("Lista.txt", ios::in);
	
	//cout<<"\t\t\t\t\t\t\t> > INICIO < < \n"<<endl;
	while(getline(arbolAvlN,txt3))
	{
		stringstream stream(txt3);
		string valor;		
		while(getline(stream, valor,','))
		{
			nume = atoi(valor.c_str());
			nume2 = nume;
			insertar(nume);
			
			//segundo archivo
			getline(arbolAvlNum,txt4);
			
			stringstream stream2(txt4);
			string valor2;
			while(getline(stream2, valor2,','))
			{
				vc.push_back(atoi(valor2.c_str()));
			}
			tam = vc.size();

			for(int i=0; i<tam; i++)
			{
				insertar2(nume2,vc[i]); 
			}
			//cout<<endl;
			for(int i=1; i<tam; i++)
			{
				vc.erase(vc.begin()+1);
			}
			vc.erase(vc.begin());
				
		}

	}
	
	
	arbolAvlN.close();
	arbolAvlNum.close();

	Preorden();
		//cout<<"\n\t\t\t\t\t\t\t> > FIN < < \n"<<endl;
}

int preOrden(avl *aux)
{
	//se recorre la raiz primero
	
	cout<<aux->num<<"->";
	
	avl2 *aux4 = aux->abajo;
	
	while(aux4!=NULL)
	{
		cout<<aux4->num2<<"-";
		aux4 = aux4->abajo2;
	}
	cout<<endl;
	//subarbol izquierdo
	
	if(aux->izquierda!=NULL)
	{
		preOrden(aux->izquierda); //recursividad
	}
	
	//subarbol derecho
	if(aux->derecha!=NULL)
	{
		preOrden(aux->derecha);
	}
	return 0;
}

void Preorden()
{
	cout<<endl<<"Recorrido en PreOrder "<<endl<<endl;
	preOrden(raiz);	
}

void busquedasimple(int b)
{
	
	avl *aux = buscarr(b);
	
	if(aux!=NULL)
		cout<<"Se encontro el indice en un tiempo aprox. de "<<tiempo<<"seg."<<endl;
	else
		cout<<"No existen coicidencia en los indices"<<endl;
}

void busquedacombinada(int a, int b)
{
	bool e=false;
	
	avl *aux = buscarr(a);
	
	if(aux!=NULL)
	{
		cout<<"Indice encontrado."<<endl<<endl;
		
		avl2 *aux2 = aux->abajo;
		
		while(aux2!=NULL)
		{
			if(aux2->num2 == b)
			{
				e = true;
				break;
			}
			aux2 = aux2->abajo2;
		}
		
		if(e == true)
			cout<<"Elemento encontrado."<<tiempo<<endl;
		else
			cout<<"No existen coicidencias entre los elementos." <<endl;
	}
	else
	{
		cout<<"No existe coincidencia entre los indices."<<endl;
	}
}

void liberar(){
	
	liberarmemoria(raiz);
}

int liberarmemoria(avl *aux)
{
	//se recorre la raiz primero
	avl2 *aux4 = aux->abajo;
	avl2 *aux5;
	avl *aux2;
	
	while(aux4!=NULL)
	{
		aux5 = aux4;
		aux4 = aux4->abajo2;
		delete(aux5);
	}
	aux->abajo = NULL;
	aux2 = aux;
	//subarbol izquierdo
	
	if(aux->izquierda!=NULL)
	{
		
		liberarmemoria(aux->izquierda); //recursividad
	}
	
	//subarbol derecho
	if(aux->derecha!=NULL)
	{
		//aux2 = aux;
		liberarmemoria(aux->derecha);
	}
	delete(aux2);
	
	return 0;
}

int Graficar(avl *aux)
{
	if(aux->izquierda!=NULL)
	{
		AAVL<<aux->num;
		AAVL<<" -> ";
		Graficar(aux->izquierda); //recursividad
		
		//arbi<<aux->numero;
	}
	else
	{
		AAVL<<aux->num;
		AAVL<<";"<<endl;
	}
	
	//subarbol derecho
	if(aux->derecha!=NULL)
	{
		//arbi<<" -> ";
		Graficar(aux->derecha);
		//arbi<<aux->numero;
	}
	
	AAVL<<endl;
	return 0;
}

int Graficar2(avl *aux)
{	
	if(aux->derecha==NULL)
	{
		AAVL<<aux->num;
		AAVL<<";"<<endl;
	}
	if(aux->derecha!=NULL)
	{
		AAVL<<aux->num;
		AAVL<<" -> ";
		Graficar2(aux->derecha); //recursividad
		//arbi<<aux->numero;
	}
	
	//subarbol derecho
	if(aux->izquierda!=NULL)
	{
		//arbi<<" -> ";
		Graficar2(aux->izquierda);
		//arbi<<aux->numero;
	}
	
	AAVL<<endl;
	return 0;
}

void graficacion()
{
	AAVL.open("AVL.dot", ios::out);
	
	if(AAVL.fail())
	{
		cout<<"No se creo el archivo";
	}
	AAVL<<"digraph G {"<<endl;
	AAVL<<"	node [shape=circle]"<<endl;

	Graficar(raiz);
	Graficar2(raiz);
	
	AAVL<<endl;
	AAVL<<"}";
	
	AAVL.close();
	
	system("dot -Tpng AVL.dot > AVL.png");
	system("AVL.png");
}

};




