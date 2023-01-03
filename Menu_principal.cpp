#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "ArbolBinario.cpp"
#include "ArbolAVL.cpp"
#include "Arbol_B.cpp"
#include "ListaSimple.cpp"


#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 13

Lista l;
Arbol ab;
arbolavl AVL;
arbolb abb;

using namespace std;

void menu_principal();
void menu_lista();
void menu_arbol();
void menu_avl();
void menu_arbolB();

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

void menu_principal(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
   	const char *titulo = "E S T R U C T U R A S   D E   D A T O S";
   	const char *opciones[] = {"Lista simple", "Arbol binario","Arbol AVL", "Arbol b", "Salir"};
   	const char ayuda[]=">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<";
   	int n = 5;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
 	   		  
	    switch (opcion) {
    		case 1:
            		menu_lista();
            		break;
 
 
         	case 2:
       				menu_arbol();
            		break;
 
 			case 3:
       				menu_avl();
            		break;
            		
            case 4:
       				menu_arbolB();
            		break;		
 
 
       		case 5:
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

void menu_lista(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
	const char *titulo = "L I S T A   S I M P L E   D I N A M I C A";
   	const char *opciones[] = {"Cargar datos", "Busqueda Simple", "Busqueda combinada","Modificar","Eliminar nodo", "Eliminar todo","Graficar", "Regresar"};
   	const char ayuda[]= {">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<"};
   	int n = 8;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int tam=0;
      	int indice;
      	int elemento;
      	
	    switch (opcion) {
    		case 1:
    				system("cls");
    				cuadro();
            		gotoxy(10,4); 	cout<<" C A R G A R   D A T O S   D E S D E   U N   A R C H I V O";
            		gotoxy(10,5); 	cout<<" ---------------------------------------------------------";
            		gotoxy(12,7); 	cout<<" Ingresa la cantidad total de indices generador: ";
            		 			  	cin>>tam;
            		gotoxy(18,10); 	cout<<" Presiona cualquier tecla para continuar.";
            						getch();
            						
            						system("cls");
            						l.numero = tam;
            						l.cargar_archivos();
            						system("cls");
            		gotoxy(10,10);	cout<<">Se cargo con exito la cantidad de "<<tam<<" datos de forma correcta<"<<endl<<endl;
            		gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						//l.recorrer();
            						getch();
            						menu_lista();
            		break;
 
         	case 2:
    				system("cls");
    				cuadro();
    	
            		gotoxy(9,4); 	cout<<" B U S Q U E D A     S I M P L E   P O R   I N D I C E S ";
            		gotoxy(9,5); 	cout<<" --------------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(9,9); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,10); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						l.buscar(indice);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_lista();
            		break;

         	case 3:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" B U S Q U E D A  P O R  I N D I C E S  Y  E L E M E N T O S";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(15,9); 	cout<<" Ingresa el elemento que deseas buscar: ";
            		 			  	cin>>elemento;
            		gotoxy(9,11); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,12); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						l.busqueda_doble(indice,elemento);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_lista();
            		break;
            		
         	case 4:
    				system("cls");
    				cuadro();
    	
            		gotoxy(17,4); 	cout<<" M O D I F I C A C I O N   D E   U N   I N D I C E";
            		gotoxy(17,5); 	cout<<" -------------------------------------------------";
            		gotoxy(22,7); 	cout<<" Ingresa el indice a modificar: ";
            		 			  	cin>>indice;

					gotoxy(22,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						l.modificar(indice);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_lista();
            		break;            		
 
          	case 5:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" E L I M I N A C I O N   P O R   M E D I O  D E   I N D I C E";
            		gotoxy(7,5); 	cout<<" ------------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas eliminar: ";
            		 			  	cin>>indice;

					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						l.eliminar(indice);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_lista();
            		break;
            		
          	case 6:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<"  E L I M I N A R    T O D A     L A    E S T R U C T U R A  ";
            		gotoxy(7,5); 	cout<<" ------------------------------------------------------------";

            						l.liberar_Memoria();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_avl();
            		break;
            		
         	case 7:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" G R A F I C A C I O N   P O R   M E D I O   D  E  G R A P H V I Z";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------------";
    
            		gotoxy(16,8); 	cout<<"A continuacion se creara un archivo formato PNG ";
            		gotoxy(15,9); 	cout<<"de los datos (indices) que se cargaron a la lista";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						l.Graficar();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						//getch();
            						menu_lista();
            		break;
 
       		case 8:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

void menu_arbolB(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
	const char *titulo = "L I S T A   S I M P L E   D I N A M I C A";
   	const char *opciones[] = {"Cargar datos", "Busqueda Simple", "Busqueda combinada","Eliminar todo", "Graficar", "Regresar"};
   	const char ayuda[]= {">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<"};
   	int n = 6;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int tam=0;
      	int indice;
      	int elemento;
      	
	    switch (opcion) {
    		case 1:
    				system("cls");
    				cuadro();
            		gotoxy(10,4); 	cout<<" C A R G A R   D A T O S   D E S D E   U N   A R C H I V O";
            		gotoxy(10,5); 	cout<<" ---------------------------------------------------------";
            		gotoxy(12,7); 	cout<<" Ingresa la cantidad total de indices generador: ";
            		 			  	cin>>tam;
            		gotoxy(18,10); 	cout<<" Presiona cualquier tecla para continuar.";
            						getch();
            						
            						system("cls");
            						abb.cargar();
            						system("cls");
            						getch();
            		gotoxy(10,10);	cout<<">Se cargo con exito la cantidad de "<<tam<<" datos de forma correcta<"<<endl<<endl;
            		gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbolB();
            		break;
 
         	case 2:
    				system("cls");
    				cuadro();
    	
            		gotoxy(9,4); 	cout<<" B U S Q U E D A     S I M P L E   P O R   I N D I C E S ";
            		gotoxy(9,5); 	cout<<" --------------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(9,9); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,10); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						//abb.buscar()
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbolB();
            		break;

         	case 3:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" B U S Q U E D A  P O R  I N D I C E S  Y  E L E M E N T O S";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(15,9); 	cout<<" Ingresa el elemento que deseas buscar: ";
            		 			  	cin>>elemento;
            		gotoxy(9,11); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,12); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						l.busqueda_doble(indice,elemento);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbolB();
            		break;         		
 
          	case 4:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" E L I M I N A C I O N   P O R   M E D I O  D E   I N D I C E";
            		gotoxy(7,5); 	cout<<" ------------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas eliminar: ";
            		 			  	cin>>indice;

					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						//eliminar
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbolB();
            		break;
            		
         	case 5:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" G R A F I C A C I O N   P O R   M E D I O   D  E  G R A P H V I Z";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------------";

            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						//getch();
            						menu_arbolB();
            		break;
 
       		case 6:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

void menu_avl(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
	const char *titulo = "A R B O L   - A V L -   D I N A M I C O";
   	const char *opciones[] = {"Cargar datos", "Busqueda Simple", "Busqueda combinada","Eliminar todo", "Graficar", "Regresar"};
   	const char ayuda[]= {">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<"};
   	int n = 6;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int indice;
      	int elemento;
      	
	    switch (opcion) {
    		case 1:
    				system("cls");
    				cuadro();
            		gotoxy(10,4); 	cout<<" C A R G A R   D A T O S   D E S D E   U N   A R C H I V O";
            		gotoxy(10,5); 	cout<<" ---------------------------------------------------------";

            		gotoxy(18,10); 	cout<<" Presiona cualquier tecla para continuar.";
            						getch();
            						
            						system("cls");
            						AVL.cargar();
            						getch();
            						system("cls");
            		gotoxy(10,10);	cout<<">Se cargo con exito la cantidad de "<<tam<<" datos de forma correcta<"<<endl<<endl;
            		gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_avl();
            		break;
 
         	case 2:
    				system("cls");
    				cuadro();
    	
            		gotoxy(9,4); 	cout<<" B U S Q U E D A     S I M P L E   P O R   I N D I C E S ";
            		gotoxy(9,5); 	cout<<" --------------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(9,9); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,10); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						AVL.busquedasimple(indice);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_avl();
            		break;

         	case 3:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" B U S Q U E D A  P O R  I N D I C E S  Y  E L E M E N T O S";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(15,9); 	cout<<" Ingresa el elemento que deseas buscar: ";
            		 			  	cin>>elemento;
            		gotoxy(9,11); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,12); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						AVL.busquedacombinada(indice,elemento);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_avl();
            		break;           		
 
          	case 4:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<"  E L I M I N A R    T O D A     L A    E S T R U C T U R A  ";
            		gotoxy(7,5); 	cout<<" ------------------------------------------------------------";

            						AVL.liberar();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_avl();
            		break;
            		
         	case 5:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" G R A F I C A C I O N   P O R   M E D I O   D  E  G R A P H V I Z";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------------";
    
            		gotoxy(16,8); 	cout<<"A continuacion se creara un archivo formato PNG ";
            		gotoxy(15,9); 	cout<<"de los datos (indices) que se cargaron a la lista";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						AVL.graficacion();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						//getch();
            						menu_avl();
            		break;
 
       		case 6:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

void menu_arbol(){
	
	bool repite = true;
   	int opcion; 
	
	// Titulo del menú y nombres de las opciones
	const char *titulo = "A R B O L   B I N A R I O  D I N A M I C O";
   	const char *opciones[] = {"Cargar datos", "Busqueda Simple", "Busqueda combinada", "Eliminar todo", "Graficar", "Regresar"};
   	const char ayuda[]= {">> Utiliza [w] Arriba [s] Abajo [ ENTER ] Para seleccionar <<"};
   	int n = 6;  // Numero de opciones
 
   	do {
      	opcion = menu(titulo, opciones, ayuda, n);
      	int tam=0;
      	int indice;
      	int elemento;
      	
	    switch (opcion) {
    		case 1:
    				system("cls");
    				cuadro();
            		gotoxy(10,4); 	cout<<" C A R G A R   D A T O S   D E S D E   U N   A R C H I V O";
            		gotoxy(10,5); 	cout<<" ---------------------------------------------------------";
          
            		gotoxy(18,10); 	cout<<" Presiona cualquier tecla para continuar.";
            						getch();
            						
            						system("cls");
            						ab.cargar_archivo();
            						ab.recorrer();
            						getch();
            						system("cls");
            		gotoxy(10,10);	cout<<"          >Se cargo con exito toda la informacion.< "<<endl<<endl;
            		gotoxy(10,12);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbol();
            		break;
 
         	case 2:
    				system("cls");
    				cuadro();
    	
            		gotoxy(9,4); 	cout<<" B U S Q U E D A     S I M P L E   P O R   I N D I C E S ";
            		gotoxy(9,5); 	cout<<" --------------------------------------------------------";
            		gotoxy(18,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(9,9); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,10); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						ab.buscar(indice);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbol();
            		break;

         	case 3:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" B U S Q U E D A  P O R  I N D I C E S  Y  E L E M E N T O S";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------";
            		gotoxy(15,7); 	cout<<" Ingresa el indice que deseas buscar: ";
            		 			  	cin>>indice;
            		gotoxy(15,9); 	cout<<" Ingresa el elemento que deseas buscar: ";
            		 			  	cin>>elemento;
            		gotoxy(9,11); 	cout<<"A continuacion se presentan los resultados de la busqueda";
            		gotoxy(9,12); 	cout<<"asi como el tiempo aproximado en segundos.";
					gotoxy(17,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						cout<<"\n\n";
            						ab.busquedaDoble(indice,elemento);
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbol();
            		break;          		
 
          	case 4:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<"  E L I M I N A R    T O D A     L A    E S T R U C T U R A  ";
            		gotoxy(7,5); 	cout<<" ------------------------------------------------------------";

									ab.liberar();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						getch();
            						menu_arbol();
            		break;
            		
         	case 5:
    				system("cls");
    				cuadro();
    	
            		gotoxy(7,4); 	cout<<" G R A F I C A C I O N   P O R   M E D I O   D  E  G R A P H V I Z";
            		gotoxy(7,5); 	cout<<" -----------------------------------------------------------------";
    
            		gotoxy(16,8); 	cout<<"A continuacion se creara un archivo formato PNG ";
            		gotoxy(15,9); 	cout<<"de los datos (indices) que se cargaron a la lista";
					gotoxy(20,14); 	cout<<"Presiona cualquier tecla para comenzar.";
            		
            						getch();
            						
            						system("cls");
            						ab.Graphviz();
            						
            		gotoxy(8,19);	cout<<">> PRESIONA CUALQUIER TECLA PARA REGRESAR AL MENU ANTERIOR <<";
            						//getch();
            						menu_arbol();
            		break;
 
       		case 6:
            		menu_principal();
            		break;
      	}
 
   } while(repite);   
	    
}

main(){

	menu_principal();
}

