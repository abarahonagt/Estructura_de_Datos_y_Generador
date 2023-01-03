#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "Matriz.cpp"

using namespace std;

#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 13

class SerieI{
	
	public:

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
      	system("color 85");
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

void menu_principal(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
   	const char *titulo = "I I I   P A R C I A L ,  S E R I E  I";
   	const char *opciones[] = {"Insertar", "Ver filas","Ver Columnas","Graficar", "Salir"};
   	const char ayuda[]=">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<";
   	int n = 5;  // Numero de opciones
   	
   	Matriz m;
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
 	   		  
	    switch (opcion) {
	    	
	    	int columna, dato;
	    	
			case 1: system("cls");
					cuadro();
					gotoxy(23,4); 	cout<<"-  I N S E R T A R   D A T O S  -";
					gotoxy(23,5); 	cout<<"---------------------------------";
					gotoxy(18,7); 	cout<<"Ingrese la columna donde insertara el dato: ";
									cin>>columna;
					gotoxy(18,9); 	cout<<"Ingrese el dato que insertara en la columna: ";
									cin>>dato;
								
									m.insercion(columna, dato);
								
					gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
									getch();
									menu_principal();
            		break;
 
 
         	case 2:	system("cls");
					cuadro();
					gotoxy(23,4); 	cout<<"- V I S U A L I Z A R  F I L A S -";
					gotoxy(23,5); 	cout<<"----------------------------------";
					gotoxy(18,7); 	cout<<"A continuacion se visualizara el contenido que";
					gotoxy(18,8); 	cout<<"se ha almacenado en las filas.";
									getch();
									
									system("cls");
									m.mostrar();
									getch();
									system("cls");
									
					gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
									getch();
									menu_principal();
       				
            		break;
            		
            case 3:	system("cls");
					cuadro();
					gotoxy(18,4); 	cout<<"- V I S U A L I Z A R  C O L U M N A S -";
					gotoxy(18,5); 	cout<<"----------------------------------------";
					gotoxy(18,7); 	cout<<"A continuacion se visualizara el contenido que";
					gotoxy(18,8); 	cout<<"se ha almacenado en las columnas.";
									getch();
									
									system("cls");
									m.mostrarC();
									getch();
									system("cls");
									
					gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
									getch();
									menu_principal();
       				
            		break;
 
 			case 4: system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" G R A F I C A C I O N   P O R   M E D I O   D  E  G R A P H V I Z";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------------";
    
            		gotoxy(16,8); 	cout<<"A continuacion se creara un archivo formato PNG ";
            		gotoxy(10,9); 	cout<<"de los datos (serieI.png) que se cargaron a la estructura";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						m.graficacion();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
       				
            		break;
 
       		case 5:
       				system("cls");
       				system("color 58");
       				cuadro();
            		gotoxy(11,3); 	cout<<" E S T E   P R O G R A M A   F U E   C R A D O   P O R";
            		gotoxy(11,4); 	cout<<" -----------------------------------------------------";
            		gotoxy(20,6); 	cout<<" ABNER NOE HAROSET - GOIM LOPEZ BARAHONA";
            		gotoxy(26,7); 	cout<<" JASON JOSE SOSA MONTENEGRO";
            		getch();
            		system("cls");
            		           		
            		
      				repite = false;
					system("pause>null");
					exit(1);
            		break;
      	}
 
   } while(repite); 
  
}
	
	
};

main(){
	
	SerieI s;
	
	s.menu_principal();
}