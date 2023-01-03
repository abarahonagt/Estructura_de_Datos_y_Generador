#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;



class ElementoL{
	
	public:
	int elemento;
	ElementoL *abajo;
};

class IndexL{
	
	public:
	int index;
	IndexL *siguiente;
	ElementoL *abajo;
};

	IndexL *inicio;
	IndexL *posicion;
	
class Lista{
	
	public:
	int numero;						//este valor debe relacionarse a la cantidad de datos generados		
	//atributos

		int contadorL=0;
		int contadorI=0;
		int tam;	
	
	//constructor
	Lista(){
	
	}
	
	//metodos
	public:
		
	void cargar_index(){
	
		ifstream archivo;
		string temporal;
		int arreglo[numero];
		int cont = 0;
		int n;
	
			archivo.open("Index.txt", ios::in);

		if(archivo.fail()){
			
			cout<<"\n\n\t\tAl parecer ocurrio un error al abrir el archivo,"<<endl<<
				  "\t\tse iniciara el generador para agregar datos al archivo."<<endl<<endl;
			getch();	  
			system("Menu.exe");
			exit(1);
		}
		else{
			
			while(getline(archivo, temporal)){
				
				stringstream stream(temporal);
				string dato;
				
				//cout<<"Se encontro la siguiente informacion en el Archivo:"<<endl<<endl;
				
				while(getline(stream, dato, ',')){
					
					arreglo[cont] = atoi(dato.c_str());
					//cout<<"["<<dato<<"] ->"<<endl;
					cont++;
				}
			}
			//ordenar indices
			
			for(int a =0; a < numero; a++){
				
				for(int b=0, c=1; c < numero; b++, c++){
					
					if(arreglo[b] > arreglo[c]){
						
						int aux = arreglo[c];
						arreglo[c] = arreglo [b];
						arreglo[b] = aux; 
					}
				}
			}
			
			//despues de ordenar se inserta al nodo
			
			for( int d = 0;d<numero;d++){
				
				n=arreglo[d];
				insertar_index(n);
			}
			
			contadorI=1;
			cout<<endl;
		}
		archivo.close();
	}
	
	void insertar_index(int n){

		IndexL *aux = new IndexL;
	
		//se inicializa los valores del nodo en cada una de sus partes
		aux->index = n;
		aux->siguiente = NULL;
		aux->abajo = NULL;
	
		if(inicio==NULL){
			
			inicio=aux;
			posicion=inicio;
		}
		else{
			
			IndexL *aux2 = inicio;
			
			while (aux2->siguiente != NULL)
				
				aux2=aux2->siguiente;
			
			aux2->siguiente=aux;
		}
	

	}
	
	void cargar_lista(){
	
		ifstream archivo2;
	
		archivo2.open("Lista.txt", ios::in);
	
		int n;
		int i;
		string temporal;
		vector<int> datos;
	
		while(getline(archivo2,temporal)){
		
			stringstream stream(temporal);
			string dato;
		
			while(getline(stream, dato, ',')){
			
				datos.push_back(atoi(dato.c_str()));
			}
		
			tam = datos.size();
		
			for(i=0; i<tam; i++)
				insertar_lista(datos[i]);
			
			for(i=1; i<tam; i++)
				datos.erase(datos.begin()+1);
			
			datos.erase(datos.begin());
	}
	
	//archivo2.close();
	}
	
	void insertar_lista(int e){
	
		ElementoL *aux = new ElementoL;
	
		//inicializamos valores
		aux->elemento = e;
		aux->abajo = NULL;
	
			if((posicion==inicio) && (contadorL != tam)){
			
				ElementoL *aux2 = posicion->abajo;
			
				if(aux2 == NULL)
				
					posicion->abajo= aux;
			
				else{
				
					while(aux2->abajo != NULL)
						
						aux2 = aux2->abajo;
						
					aux2->abajo = aux;
				}
			
				contadorL++;
			}
		
			if((posicion != inicio) && (posicion != NULL)){
			
				ElementoL *aux2 = posicion->abajo;
				
				if(aux2 == NULL)
			
					posicion->abajo = aux;
			
				else{
				
					while(aux2->abajo != NULL){
						aux2 = aux2->abajo;
					}
				
					aux2->abajo = aux;
				}
				contadorL++;
			}
		
			if(contadorL == tam){
			
				posicion = posicion->siguiente;
				contadorL = 0;
			}
	}
	
	void recorrer(){
		IndexL *auxI = inicio;
		while (auxI!=NULL)
		{
			cout<<"["<<auxI->index<<"] ";
			ElementoL *auxL=auxI->abajo;
			while (auxL!=NULL)
			{
				cout<<auxL->elemento<<"-> ";
				auxL=auxL->abajo;
			}
			cout<<endl;
			auxI=auxI->siguiente;
		}
		getch();
	}
	
	void cargar_archivos(){
		
		system("cls");
	
		cargar_index();
		cargar_lista();
	
		recorrer();
	}
	
	void liberar_Memoria(){
		
    	IndexL *auxC = inicio;
    	IndexL *ant;
    	
		while (auxC!=NULL){
        
        	ElementoL *auxL=auxC->abajo;
        	ElementoL *antL;
        	
			while (auxL!=NULL){
            
				antL = auxL;
            	auxL=auxL->abajo;
            	delete(antL);
        	}
        	ant = auxC;
        	auxC=auxC->siguiente;//Salto 
        	delete(ant);
    	}
    	getch();
    
    	return;
	}
	
	
	void busqueda_doble(int indice, int elemento){
	
		bool indice_encontrado=false;
		bool elemento_encontrado=false;
	
		unsigned t, t2;
	
		//buscamos el indice
	
		IndexL *aux = inicio;
	
		t=clock();
	
		while(aux != NULL){
		
			if(indice == aux->index){
			
				ElementoL *aux2 = aux->abajo;
			
				//para buscar elemento;
			
				while(aux2 != NULL){
				
					if(aux2->elemento == elemento){
					
						elemento_encontrado=true;
					}
					aux2=aux2->abajo;
				}
				indice_encontrado=true;
				break;
			}
			aux=aux->siguiente;
		}
	
		t2=clock();
	
		double time = (double(t2-t)/CLOCKS_PER_SEC);
	
		if(indice_encontrado == true){
			
			cout<<"\n\n\tSe encontro el indice indicado."<<endl;
		
			if(elemento_encontrado == true)
				cout<<"\n\n\tSe encontro el elemento indicado"<<endl;
		
			else
				cout<<"\tEl elemento que busca no se encuentra"<<endl;
		
			cout<<"\tEl tiempo estimado de busqueda fue: "<<time<<"seg."<<endl;
		}
		else
			cout<<"\n\n\tEl indice que busca no se encuentra"<<endl;
	
	}
	
	bool buscar(int a){
		
		IndexL *aux = inicio;
	 	IndexL *ant;
	 	
	 	bool encontrado=false;
		
		//variables para uso de ctime
		unsigned t, t2;	 	
	 	
	 	if(inicio->index== a){
	 		
	 		//ant = aux;
	 		//aux = aux->siguiente;
	 		
	 		cout<<"\n\n\tEl indice indicado fue encontrado al inicio de la lista."<<endl;
	 		encontrado=true;
	 		return true;
		 }
	 	else{
	 		
	 		t=clock();
	 		
	 		while(aux !=NULL){
	 			
	 			ant = aux;
	 			
	 			
	 			if(a==ant->index){
	 				cout<<"\n\n\tEl indice indicado fue encontrado en la lista."<<endl;
	 				
	 				t2 = clock();
					double time = (double (t2-t)/CLOCKS_PER_SEC);
					cout<<"\tLa busqueda se realizo en un tiempo estimado de: "<<time<<"seg."<<endl;
					
					encontrado=true;
	 				return true;
	 				break;
				 }
				 
				 aux= aux->siguiente;
			 }
			 
		 }
		 
		 cout<<"\n\n\tEl numero no coincide con ningun indice."<<endl;
		 return false;
	}
	
	void eliminar(int a){
		
	 	IndexL *aux = inicio;
	 	IndexL *ant;
	 	IndexL *eliminar;
	 	
	 	bool encontrado = false;
	 	
	 	if(inicio->index== a){
	 		
	 		ant = aux;
	 		aux = aux->siguiente;
	 		
	 		encontrado=true;
		 }
	 	else{
	 		
	 		while(aux !=NULL){
	 			
	 			ant = aux;
	 			aux= aux->siguiente;
	 			
	 			if(a==aux->index){
	 				
	 				encontrado=true;
	 				break;
				 }
			 }
		 }
		
	 	if( buscar(a) == true){
		
	 		if(ant == inicio){
	 			
	 			inicio = aux;
	 			ElementoL *el = ant->abajo;
	 			ElementoL *el2;
	 			
	 			while(el!=NULL){
	 				
	 				el2 = el;
	 				el = el->abajo;
	 				delete(el2);
				 }
				 
				 delete(ant);
			 }
			 else{
			 	
			 	eliminar = aux;
			 	aux = aux->siguiente;
			 	ant->siguiente = aux;
			 	
			 	ElementoL *el = eliminar->abajo;
			 	ElementoL *el2;
			 	
			 	while(el!=NULL){
			 		
			 		el2 = el;
			 		el = el->abajo;
			 		delete(el2);
			 		
				 }
				 
				 aux=inicio;
				 
				 delete(eliminar);
			 	
			 }
	 		cout<<"\n\n\tSe elimino el indice indicado."<<endl<<endl;
		 }
		 else
		 	cout<<"\n\n\tEl numero no coincide con ningun indice.";
		 	
	}
	
	void modificar(int a){
		
		bool encontrado = false;
    
    
    	IndexL *aux = inicio;
    
    	while(aux != NULL){
	
	        if(a == aux->index){
            
			encontrado = true;
            break;
        	}
        aux = aux->siguiente;
    	}
    
    	if(encontrado == true){
    		
        	cout<<"\n\n\tEl indice indicado fue encontrado en la lista."<<endl<<endl;
        	cout<<"\n\tIngrese el nuevo numero: ";
        	cin>>aux->index;
    	}
    	else
        	cout<<"\n\tEl numero no coincide con ningun indice."<<endl;
		
		cout<<"\n\n";
		recorrer();
	}
	
	void Graficar(){
		
		int c = 0;
		
	    ofstream archivo;
	    archivo.open("Lista.dot", ios::out);
	    
		IndexL *aux = inicio;
	    
	    if(archivo.fail())
	    {
	        cout<<"Ocurrio un error al abrir el archivo";
	        exit(1); 
	    }
	    
	    archivo<<"digraph {"<<endl;
	    
	    while(aux!=NULL)
	    {
	        archivo<<" "<<aux->index;
	        
	        if(aux->siguiente!=NULL)
	        {
	            if(c==100000)
	            {
	                archivo<<";"<<endl;
	                c = 0;
	            }
	            else
	                archivo<<"->";
	        }
	            
	        else
	            archivo<<";";
	        
	        aux = aux->siguiente;
	        c++;
	    }
	    archivo<<endl;
	    archivo<<"}"; 
	    
	    archivo.close();
	    
	    system("dot -Tpng Lista.dot > Lista.png");
	    system("Lista.png");
	    system("pause");
	}
	
	
};

//main(){
//	Lista l;
//	inicio=NULL;
//	
//	int dim;
//	cout<<"cantidad datos: ";
//	cin>>dim;
//	
//	l.numero=dim;
//
//	l.cargar_archivos();
//	
//	getch();
//	system("cls");
//	
//	int a;
//	int b;
//	
//	cout<<"Indice: ";
//	cin>>a;
//	
//	//cout<<"ElementoL: ";
//	//cin>>b;
//	
//	//l.busqueda_doble(a,b);
//	l.buscar(a);
//	
//	getch();
//	system("cls");
//	
//	cout<<"Indice eliminar: ";
//	cin>>a;
//	
//	//l.eliminar(a);
//	l.modificar(a);
//	
//	l.Graficar();
//	
//	getch();
//	l.liberar_Memoria(); 
//}
