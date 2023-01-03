#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <conio.h>

using namespace std;

class Elemento{
	
	public:
	int elemento;
	Elemento *aba;
};

class Index{
	
	public:
	int index;
	Index *izq;
	Index *der;
	Elemento *aba;
};

Index *raiz;

class Arbol{
	
	//atributos
	
	public:
		int tam;
		double tiempo;
		ofstream arbol;
		
	Arbol(){
		
	}	
	
	public:
		
		void cargar_archivo(){
			
			ifstream index_a, elementos_a;
			string temporal; 
			string temporal2;
			
			int num;
			int n;
			vector<int> datos;
			
			index_a.open("Index.txt", ios::in);
			elementos_a.open("Lista.txt", ios::in);
			
			if(raiz!=NULL){
				liberarMemoria(raiz);
				raiz = NULL;
			}
			
			//primer archivo
			while(getline(index_a,temporal)){
				
				stringstream stream(temporal);
				string dato;
					
				while(getline(stream, dato,','))
				{
					num = atoi(dato.c_str());
					
					//segundo archivo
					getline(elementos_a,temporal2);
					
					stringstream stream2(temporal2);
					string dato2;
					
					while(getline(stream2, dato2,',')){
						
						datos.push_back(atoi(dato2.c_str()));

					}
					tam = datos.size();
								
					for(int i=0; i<tam; i++)
					
						insertar(num,datos[i]);  
					
						
					for(int i=1; i<tam; i++)
					
						datos.erase(datos.begin()+1);
					
					
					datos.erase(datos.begin());
				}
			}
			
			index_a.close();
			elementos_a.close();
			//cout<<"Se han cargado todos los datos."<<endl;
		
			//recorrer();
		}
		
		void insertar(int ind, int lis){
		
			Index *aux3 = busqueda(ind);
	
			Elemento *auxL = new Elemento();
			auxL->elemento = lis;
			auxL->aba = NULL;

				if(raiz==NULL){	
		
					Index *aux = new Index();
					aux-> index = ind;
					aux-> der = NULL;
					aux-> izq = NULL;
				
					raiz = aux;
					aux->aba = auxL;
				}
				else if((raiz!=NULL)&&(aux3==NULL)){
		
					//si ya existe un  elemento
			
					Index *aux=new Index();
					aux->index=ind;
					aux->der=NULL;
					aux->izq=NULL;
			
					Index *aux2=raiz;
					bool bandera = false;
			
					while(bandera==false){
						
						if(ind > aux2->index){
							
							if(aux2->der!=NULL){
								
								aux2=aux2->der; //salta a derecha
							}
							else{
								
								aux2->der = aux;
								aux->aba = auxL;
								bandera=true;
							}
						}
						else{
							
							if(ind < aux2->index){
								
								if(aux2->izq!=NULL){
									
									aux2 = aux2->izq; //salto a la izquierda
								}
								else{
									
									aux2->izq = aux;
									aux->aba = auxL;
									bandera=true;
								}
							}
						}
					}
				}
				else if(aux3!=NULL){
					
					Elemento *aux4 = aux3->aba;
			
					while(aux4->aba != NULL){
						
						aux4 = aux4->aba;
					}
			
					aux4->aba = auxL;
				}	
		}
		
		void liberar(){
			
			liberarMemoria(raiz);
			
		}
		
		int liberarMemoria(Index *aux){
			
			//se recorre la raiz primero
			Elemento *aux4 = aux->aba;
			Elemento *aux5;
			Index *aux2;
			
			while(aux4!=NULL){
				
				aux5 = aux4;
				aux4 = aux4->aba;
				delete(aux5);
			}
			
			aux->aba = NULL;
			aux2 = aux;
			
			//subarbol izquierdo
			if(aux->izq!=NULL)
			
				liberarMemoria(aux->izq); 
			
			//subarbol derecho
			if(aux->der!=NULL)
					
				liberarMemoria(aux->der);
			
			delete(aux2);
			
			return 0;
		}
		
		Index *busqueda(int n){
			
			Index *aux = raiz;
			bool encontrado=false;
			
			unsigned t, t2;
			
			t=clock();
			
			while (aux!=NULL && !encontrado){
				
				if(aux->index== n)
			
					encontrado = true;
				
				else if(n > aux->index)
				{
					if(aux->der==NULL)
					
						return NULL;
					
					else
						aux=aux->der;
				}
				else
				{
					if(n < aux->index)
					{
						
						if(aux->izq== NULL)
							
							return NULL;
							
						else
							aux=aux->izq;
						
					}	
				}			
			}
			
			t2 = clock();
			
			tiempo = (double(t2-t)/CLOCKS_PER_SEC);
			
			if(encontrado)
				return aux;
				
			else 
				return NULL;
		}
		
		int preOrder(Index *aux){
			
			//se recorre la raiz primero
			cout<<aux->index<<"->";
			
			Elemento *aux4 = aux->aba;
			
			while(aux4!=NULL){
				
				cout<<aux4->elemento<<"-";
				aux4 = aux4->aba;
			}
			
			cout<<endl;
			
			//subarbol izquierdo
			if(aux->izq != NULL)
			
				preOrder(aux->izq);
			
			
			//subarbol derecho
			if(aux->der!=NULL)
			
				preOrder(aux->der);
			
			return 0;
		}
		
		void recorrer(){
			
			cout<<"\nRecorrido en Pre-order:\n\n";
			preOrder(raiz);
		}
		
		void buscar(int a){
			
			Index *aux = busqueda(a);
			
			if(aux!=NULL)
		
				cout<<"\tIndice encontrado en: "<<tiempo<<"seg."<<endl;
			else
			
				cout<<"\tNumero no coicide con ningun indice."<<endl;
			
		}
		
		void busquedaDoble(int a, int b){
			
			bool encontrado=false;

			
			Index *aux = busqueda(a);
			
			if(aux!=NULL){
				
				cout<<"\tSe encontro el indice buscado."<<endl<<endl;
				
				
				Elemento *aux2 = aux->aba;
				
				while(aux2!=NULL){
					
					if(aux2->elemento == b){
						
						encontrado = true;
						break;
					}
					aux2 = aux2->aba;
				}
				
				if(encontrado == true){
					
						cout<<"\tSe encontro el elemnto en la lista.\n\n";
						cout<<"\tTiempo aproximado de busqueda: "<<tiempo<<"seg."<<endl;	
				}	
				
				else
					cout<<"\tNo existen coincidencias entre los elementos."<<endl;
			}
			else
			
				cout<<"\tNo existen coincidencias entre los indices."<<endl;
			
		}
		
		int Lado_izquierdo(Index *aux){
			
			if(aux->izq!=NULL){
				
				arbol<<aux->index;
				arbol<<" -> ";
				Lado_izquierdo(aux->izq); 
			}
			else{
				
				arbol<<aux->index;
				arbol<<";"<<endl;
			}
			
			//subarbol derecho
			if(aux->der!=NULL)
			{
			
				Lado_izquierdo(aux->der);
			}
			
			arbol<<endl;
			return 0;
		}
		
		int Lado_derecho(Index *aux){
			
			if(aux->der==NULL){
				
				arbol<<aux->index;
				arbol<<";"<<endl;
			}
			
			if(aux->der!=NULL){
				
				arbol<<aux->index;
				arbol<<" -> ";
				Lado_derecho(aux->der); 		
			}
			
			//subarbol derecho
			if(aux->izq!=NULL){
	
				Lado_derecho(aux->izq);
			}
			
			arbol<<endl;
			return 0;
		}
		
		void Graphviz()
		{
			arbol.open("arbol.dot", ios::out);
			
			if(arbol.fail())
			{
				cout<<"Ocurrio un error al abrir el fichero";
			}
			arbol<<"digraph G {"<<endl;
			arbol<<"	node [shape=doublecircle]"<<endl;
		
			Lado_izquierdo(raiz);
			Lado_derecho(raiz);
			
			arbol<<endl;
			arbol<<"}";
			
			arbol.close();
			
			system("dot -Tpng arbol.dot > arbol.png");
			system("arbol.png");
		}
	
};

//main(){
	
//	Arbol a;
//	
//	int n;
//	int m;
//	cout<<"Indice:";
//	cin>>n;
//	
//	a.cargar_archivo();
//	
//	system("cls");
//	a.buscar(n);
//	getch();
//	
//	system("cls");
//	
//	cout<<"Indice:";
//	cin>>n;
//	
//	cout<<"Elemento:";
//	cin>>m;
//	
//	a.busquedaDoble(n,m);
//	getch();
//	
//	system("cls");
//	a.Graphviz();
//}
