#include<iostream>
#include<cstdlib>
#include<ctime>
#include <conio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include <sstream>
#include <vector>

using namespace std;

#define MAX 4
#define MIN 2

class B {
	public:
    int valor[MAX + 1], cont;
    B *link[MAX + 1];
};


void cargar();

class arbolb{
	public:
	B *raiz;
			
	int tam;
				
	//constructor
	arbolb(){
		
	}

// Creando el nodo
B *Crear(int val, B *aux) {
    B *nuevo = new B;
    nuevo->valor[1] = val;
    nuevo->cont = 1;
    nuevo->link[0] = raiz;
    nuevo->link[1] = aux;
    return nuevo;
}


//metodos
 	public:
 		
// Colocando Nodo en su posicion correcta
void Posicion(int val, int pos, B *aux1, B *aux2) {
    int j = aux1->cont;
    while (j > pos) {
        aux1->valor[j + 1] = aux1->valor[j];
        aux1->link[j + 1] = aux1->link[j];
        j--;
    }
    aux1->valor[j + 1] = val;
    aux1->link[j + 1] = aux2;
    aux1->cont++;
}

// dividiendo nodos
void division(int val, int *pval, int pos, B *aux, B *aux2, B **nuevo) {
    int median, j;
 
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;
 
    *nuevo = new B;
    j = median + 1;
    while (j <= MAX) {
        (*nuevo)->valor[j - median] = aux->valor[j];
        (*nuevo)->link[j - median] = aux->link[j];
        j++;
    }
    aux->cont = median;
    (*nuevo)->cont = MAX - median;
 
    if (pos <= MIN) {
        Posicion(val, pos, aux, aux2);
    }
    else {
        Posicion(val, pos - median, *nuevo, aux2);
    }
    *pval = aux->valor[aux->cont];
    (*nuevo)->link[0] = aux->link[aux->cont];
    aux->cont--;
}

// Estableciendo el valor al nodo
int valorn(int val, int *pval, B *aux, B **aux2) {
 
    int pos;
    if (!aux) {
        *pval = val;
        *aux2 = NULL;
        return 1;
    }
 
    if (val < aux->valor[1]) {
        pos = 0;
    }
    else {
        for (pos = aux->cont;
            (val < aux->valor[pos] && pos > 1); pos--);
        if (val == aux->valor[pos]) {
            cout<<"Este dato ya existe"<<endl;
            return 0;
        }
    }
    if (valorn(val, pval, aux->link[pos], aux2)) {
        if (aux->cont < MAX) {
            Posicion(*pval, pos, aux, *aux2);
        }
        else {
            division(*pval, pval, pos, aux, *aux2, aux2);
            return 1;
        }
    }
    return 0;
}

//insertar Nodos al arbol B
void insercion(int val) {
    int flag, i;
    B *aux;
 
    flag = valorn(val, &i, raiz, &aux);
    if (flag)
        raiz = Crear(i, aux);
}

// Copiando el sucesor del borrado
void copiar(B *aux, int pos) {
    B *aux2;
    aux2 = aux->link[pos];
 
    for (; aux2->link[0] != NULL;)
        aux2 = aux2->link[0];
    aux->valor[pos] = aux2->valor[1];
 
}

// Elimina el nodo y ajusta los valores
void eliminaval(B *aux, int pos) {
    int i = pos + 1;
    while (i <= aux->cont) {
        aux->valor[i - 1] = aux->valor[i];
        aux->link[i - 1] = aux->link[i];
        i++;
    }
    aux->cont--;
}

// Cambia del padre al hijo derecho
void PHD(B *aux, int pos) {
    B *x = aux->link[pos];
    int j = x->cont;
 
    while (j > 0) {
        x->valor[j + 1] = x->valor[j];
        x->link[j + 1] = x->link[j];
    }
    x->valor[1] = aux->valor[pos];
    x->link[1] = x->link[0];
    x->cont++;
 
    x = aux->link[pos - 1];
    aux->valor[pos] = x->valor[x->cont];
    aux->link[pos] = x->link[x->cont];
    x->cont--;
    return;
}

/* Cambia valor del padre al hijo izquierdo */
void PHI(B *aux, int pos) {
    int j = 1;
    B *x = aux->link[pos - 1];
 
    x->cont++;
    x->valor[x->cont] = aux->valor[pos];
    x->link[x->cont] = aux->link[pos]->link[0];
 
    x = aux->link[pos];
    aux->valor[pos] = x->valor[1];
    x->link[0] = x->link[1];
    x->cont--;
 
    while (j <= x->cont) {
        x->valor[j] = x->valor[j + 1];
        x->link[j] = x->link[j + 1];
        j++;
    }
    return;
}

// union de nodos
void unionN(B *aux, int pos) {
    int j = 1;
    B *x1 = aux->link[pos], *x2 = aux->link[pos - 1];
 
    x2->cont++;
    x2->valor[x2->cont] = aux->valor[pos];
    x2->link[x2->cont] = aux->link[0];
 
    while (j <= x1->cont) {
        x2->cont++;
        x2->valor[x2->cont] = x1->valor[j];
        x2->link[x2->cont] = x1->link[j];
        j++;
    }
 
    j = pos;
    while (j < aux->cont) {
        aux->valor[j] = aux->valor[j + 1];
        aux->link[j] = aux->link[j + 1];
        j++;
    }
    aux->cont--;
    delete(x1);
}

// ajustar nodo actual 
void acomodar(B *aux, int pos) {
    if (!pos) {
        if (aux->link[1]->cont > MIN) {
            PHI(aux, 1);
        }
        else {
            unionN(aux, 1);
        }
    }
    else {
        if (aux->cont!= pos) {
            if (aux->link[pos - 1]->cont > MIN) {
                PHD(aux, pos);
            }
            else {
                if (aux->link[pos + 1]->cont > MIN) {
                    PHI(aux, pos + 1);
                }
                else {
                    unionN(aux, pos);
                }
            }
        }
        else {
            if (aux->link[pos - 1]->cont > MIN)
                PHD(aux, pos);
            else
                unionN(aux, pos);
        }
    }
}

/* Eiminar Nodo */
int eliminaruno(int val, B *aux) {
    int pos, flag = 0;
    if (aux) {
        if (val < aux->valor[1]) {
            pos = 0;
            flag = 0;
        }
        else {
            for (pos = aux->cont;
                (val < aux->valor[pos] && pos > 1); pos--);
            if (val == aux->valor[pos]) {
                flag = 1;
            }
            else {
                flag = 0;
            }
        }
        if (flag) {
            if (aux->link[pos - 1]) {
                copiar(aux, pos);
                flag = eliminaruno(aux->valor[pos], aux->link[pos]);
                if (flag == 0) {
                    cout<<"Vacio."<<endl;
                }
            }
            else {
                eliminaval(aux, pos);
            }
        }
        else {
            flag = eliminaruno(val, aux->link[pos]);
        }
        if (aux->link[pos]) {
            if (aux->link[pos]->cont < MIN)
                acomodar(aux, pos);
        }
    }
    return flag;
}

// Borrado valor del arbol B
void borrar(int val,B *aux) {
    B *tmp;
    if (!eliminaruno(val, aux)) {
        cout<<"No existe el numero indicado."<<endl;
        return;
    }
    else {
        if (aux->cont == 0) {
            tmp = aux;
            aux = aux->link[0];
            delete(tmp);
        }
    }
    raiz = aux;
    return;
}

//Buscando valor en el arbol B
void buscar(int val, int *pos, B *aux) {
    if (!aux) {
        return;
    }
 
    if (val < aux->valor[1]) {
        *pos = 0;
    }
    else {
        for (*pos = aux->cont;
            (val < aux->valor[*pos] && *pos > 1); (*pos)--);
        if (val == aux->valor[*pos]) {
            cout << "Se encontro el dato."<<endl;
            return;
        }
    }
    buscar(val, pos, aux->link[*pos]);
    return;
}

//Recorrer arbol B
void recorrer(B *aux) {
    int i;
    if (aux) {
        for (i = 0; i < aux->cont; i++) {
            recorrer(aux->link[i]);
            cout<< aux->valor[i + 1]<<" ";
        }
        cout<<endl;
        recorrer(aux->link[i]);
    }
}

void cargar()
{
	ifstream arbolBN, arbolBNum;
	string texto3, texto4;
	int nume,n;
	vector<int> vec2;
	
	arbolBN.open("Index.txt", ios::in);
	arbolBNum.open("Lista.txt", ios::in);
	
	//cout<<"\t\t\t\t\t\t\t> > INICIO < < \n"<<endl;
	while(getline(arbolBN,texto3))
	{
		stringstream stream(texto3);
		string valor;		
		while(getline(stream, valor,','))
		{
			nume = atoi(valor.c_str());
			
			//segundo archivo
			getline(arbolBNum,texto4);
			
			stringstream stream2(texto4);
			string valor2;
			
			while(getline(stream2, valor2,','))
			{
				vec2.push_back(atoi(valor2.c_str()));
			}
			tam = vec2.size();

			insercion(nume);
			for(int i=0; i<tam; i++)
			{
				//insercionB(nume);
				//cout<<vec2[i]<<"-";
			}
			//cout<<endl;
			for(int i=1; i<tam; i++)
			{
				vec2.erase(vec2.begin()+1);
			}
			vec2.erase(vec2.begin());

			
		}
		//cout<<"fin de linea\n";
	}
	arbolBN.close();
	arbolBNum.close();
	recorrer(raiz);

}

};



