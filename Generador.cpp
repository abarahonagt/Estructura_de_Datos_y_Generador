#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

class Generador{
	
	public:
		//atributos
		ofstream archivo;
		ofstream archivo2;
		//int tam=0;
		int nodosAleatorios=1;
		int numeroAleatorio=0;
		
	
	public:
		//metodos
	
	int obtenerNumero(){
       
    	int aleatorio = rand()%200000;
       
    	return aleatorio;
	}

	int obtenerNumero_(){
       
    	int aleatorio = (rand()%100)+1;
       
    	return aleatorio;
	}

	int rango(){
      
    	int aleatorio = rand()%25;
       
   		return aleatorio;
	}

	void cabeceras(int tam){
	
		int i=0;
		
		for(i; i<tam;i++){
			
			int numeroAleatorio=0;
			numeroAleatorio = obtenerNumero();
			cout<<"["<<numeroAleatorio<<"]";
			
			cout<<" ";
			
			nodos(rango());
			
			cout<<endl;
		}
		
	}

	void nodos(int tam_){
	
		int i=0;

		for(i; i<tam_;i++){
			
			//nodos
			nodosAleatorios = obtenerNumero_();
			cout<<nodosAleatorios<<" ";
			
		}
	
	}

	void crear_nodosArchivo(int tam_){
	
		int i=0;

		for(i; i<tam_;i++){
			
			//nodos
			nodosAleatorios = obtenerNumero_();
			archivo2<<nodosAleatorios+1<<",";
			
		}
	
	}
	
	void crear_lista(int tam){
		
		int i = 0;
		
		archivo2.open("Lista.txt");
		
			for(i; i<tam; i++){
				
//				int numeroAleatorio=0;
//				numeroAleatorio = obtenerNumero_();
//				archivo2<<numeroAleatorio<<",";
				crear_nodosArchivo(rango()+1);
				archivo2<<endl;
			}
		
		archivo2.close();
	}

	void crear_cabeceraArchivo(int tam){
	
		int i=0;
		
		archivo.open("Index.txt");
			for(i; i<tam;i++){
			
				int numeroAleatorio=0;
				numeroAleatorio = obtenerNumero();
				archivo<<numeroAleatorio<<",";
			
				archivo<<endl;
			}
		archivo.close();
	}
		
	
};


//int main(){
//
//	Generador g;
//    
//	
//	int tam=0;
//		cout<<"Ingrese la cantidad de datos que desea generar: ";
//		cin>>tam;
//			
//	g.cabeceras(tam);
//	g.crear_cabeceraArchivo(tam);
//	g.crear_lista(tam);
//	getch();
//	system("Lista.txt");	
//	
//
//	return 0;
//}
