#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "Generador.cpp"

#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 13

using namespace std;

void menu_principal();

Generador g;

void OcultaCursor(){
    CONSOLE_CURSOR_INFO cci = {100, FALSE};

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 
 char getch2 ()
{
   char c=0;
   DWORD modo, contador;
   HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
 
   // Desactivamos escritura en terminal
   SetConsoleMode (ih, modo & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
 
   ReadConsoleA (ih, &c, 1, &contador, NULL);
 
   if (c == 0) {
      ReadConsoleA (ih, &c, 1, &contador, NULL);
   }
 
   SetConsoleMode (ih, modo); // Devolvemos control normal
 
   return c;
}

void cuadro()
{
	//lineas horizontales
	
	for(int i=1;i<78;i++)
	{
		gotoxy(i,1); printf("%c",205); //lineas de arriba
		gotoxy(i,22); printf("%c",205); //lineas de abajo
	}
	
	//lineas verticales
	
		for(int i=2;i<22;i++)
	{
		gotoxy(1,i); printf("%c",186); //lineas de arriba
		gotoxy(78,i); printf("%c",186); //lineas de abajo
	}
	
	//esquinas 
		gotoxy(1,1); printf("%c",201);
		gotoxy(1,22); printf("%c",200);
		gotoxy(78,1); printf("%c",187);		
		gotoxy(78,22); printf("%c",188);
}

int menu(const char titulo[], const char *opciones[], const char ayuda[], int n)
{
   int opcionSeleccionada = 1;  // Indica la opcionSeleccionada
 
   int tecla;
   
   OcultaCursor();
 
   bool repite = true; // controla el bucle para regresar a la rutina que lo llamo, al presionar ENTER
 
   do {
      	system("cls");
      	system("color 80");
      	cuadro();
      	gotoxy(30, 9 + opcionSeleccionada); cout << ">" << endl;
 
      	// Imprime el título del menú
      	gotoxy(23, 4); cout << titulo;
      	
      	//Imprime barra de ayuda
      	gotoxy(9,23);	cout<<ayuda;
 
      	// Imprime las opciones del menú
      	for (int i = 0; i < n; ++i) {
        	gotoxy(32, 10 + i); cout<<"["<<i + 1<<"] "<< opciones[i];
      	}
 
      	// Solo permite que se ingrese ARRIBA, ABAJO o ENTER
 
      	do {
         	tecla = getch2();
         	// gotoxy(15, 15); cout << "tecla presionada: " << (char)tecla << " = " << tecla;
      	} while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
 
      	switch (tecla) {
 
         	case ARRIBA:   // En caso que se presione ARRIBA
 
            			opcionSeleccionada--;
 
            			if (opcionSeleccionada < 1) {
               				opcionSeleccionada = n;
            			}
 						break;
 
         	case ABAJO:
            			opcionSeleccionada++;
 
            			if (opcionSeleccionada > n) {
               				opcionSeleccionada = 1;
            			}
 
            			break;
 
         	case ENTER:
            			repite = false;
            			break;
      	}			
 
   	} while (repite);
 
   	return opcionSeleccionada;
}

void menu_generar(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
   	const char *titulo = "G E N E R A D O R   D E   D A T O S";
   	const char *opciones[] = {"Generar datos", "Crear Archivo", "Regresar"};
   	const char ayuda[]= {">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<"};
   	int n = 3;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int tam=0;
      	
	    switch (opcion) {
    		case 1:
    				srand((unsigned) time(0));
    				system("cls");
    				cuadro();
            		gotoxy(10,4); 	cout<<" G E N E R A D O R   D E   D A T O S   E N   C O N S O L A";
            		gotoxy(10,5); 	cout<<" ---------------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa la cantidad de datos a generar: ";
            		 			  	cin>>tam;
            		gotoxy(18,10); 	cout<<" Presiona cualquier tecla para continuar.";
            						getch();
            						
            						system("cls");
            						g.cabeceras(tam);
            						cout<<"\n\nSe genero con exito la cantidad de "<<tam<<" datos de forma aleatoria."<<endl<<endl;
            						cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_generar();
            		break;
 
         	case 2:
       				srand((unsigned) time(0));
    				system("cls");
    				cuadro();
            		gotoxy(15,4); 	cout<<" G E N E R A R   A R C H I V O   C O N   D A T O S";
            		gotoxy(15,5); 	cout<<" -------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa la cantidad de datos a generar: ";
            		 			  	cin>>tam;
            		gotoxy(15,9); 	cout<<"A continuacion de crearan dos archivos con formato txt";
            		gotoxy(15,10); 	cout<<"Presiona cualquier tecla para comenzar.";
					gotoxy(12,14); 	cout<<"Los archivos se abriran automaticamente despues de crearse.";
            		
            						getch();
            						g.crear_cabeceraArchivo(tam);
            						g.crear_lista(tam);
            						system("Lista.txt");
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_generar();
            		break;
 
       		case 3:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

void documentacion(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
   	const char *titulo = "G E N E R A D O R   D E   D A T O S";
   	const char *opciones[] = {"Leer la documentacion", "Regresar", "Salir"};
   	const char ayuda[]=">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<";
   	int n = 3;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int tam=0;
      	
	    switch (opcion) {
    		case 1:
    				srand((unsigned) time(0));
    				system("cls");
    				cuadro();
            		gotoxy(14,3); 	cout<<" D O C U M E N T A C I O N   D E L   P R O G R A M A";
            		gotoxy(14,4); 	cout<<" ---------------------------------------------------";
            		gotoxy(4,6); 	cout<<" Este programa esta disenado para generar una serie de datos aleatorios,";
            		gotoxy(4,7); 	cout<<" los cuales estan formados de la siguiente manera:";
            		gotoxy(25,9); 	cout<<" [ INDICE ] -> [ ELEMENTOS ]";
            		gotoxy(4,11); 	cout<<" Tanto el indice como los elementos estan compuestos por numeros enteros";
            		gotoxy(4,12); 	cout<<" El usuario puede introducir la cantidad de datos a generar (indices),";
            		gotoxy(4,13); 	cout<<" el programa decidira de forma aleatoria la cantidad de elementos que ";
            		gotoxy(4,14); 	cout<<" estaran adjuntos a los indices; esto en un rango de 0 a 25 elementos.";
            		gotoxy(4,15); 	cout<<" Una vez creado el conjunto de datos, se puede ir al apartado de crear";
            		gotoxy(4,16); 	cout<<" archivo, en donde se generaran dos archivo txt con nombre (Lista.txt)";
            		gotoxy(4,17); 	cout<<" y un archivo llamado (Index.txt). Los cuales se guardaran en la carpeta";
            		gotoxy(4,18); 	cout<<" donde se ubica el programa, asimismo, despues de crear los archivos, ";
            		gotoxy(4,19); 	cout<<" estos se abriran automaticamente el Bloc de notas para visualizarse.";
            		 			
            		gotoxy(8,21);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_principal();
            		break;
 
         	case 2:
       				menu_principal();
            		break;
 
       		case 3:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

void menu_principal(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
   	const char *titulo = "G E N E R A D O R   D E   D A T O S";
   	const char *opciones[] = {"Generar datos", "Documentacion", "Salir"};
   	const char ayuda[]=">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<";
   	int n = 3;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
 	   		  
	    switch (opcion) {
    		case 1:
            		menu_generar();
            		break;
 
 
         	case 2:
       				documentacion();
            		break;
 
       		case 3:
       				system("cls");
       				cuadro();
            		gotoxy(11,3); 	cout<<" E S T E   P R O G R A M A   F U E   C R A D O   P O R";
            		gotoxy(11,4); 	cout<<" -----------------------------------------------------";
            		gotoxy(20,6); 	cout<<" ABNER NOE HAROSET - GOIM LOPEZ BARAHONA";
            		gotoxy(26,7); 	cout<<" JASON JOSE SOSA MONTENEGRO";
            		getch();
            		system("cls");
            		           		
            		
      				repite = false;
					system("pause>null");
            		break;
      	}
      	
      	
 
   } while(repite); 

	    
}
 
 int main(){
 	
 	menu_principal();
 	return 0;
 }
