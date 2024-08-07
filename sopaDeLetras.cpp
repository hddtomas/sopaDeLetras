#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cstring>
using namespace std;

struct sopas{
	string letra = "?";
	bool enUso = false;
};

sopas sopa[30][30];
string diccionario[7];
int opcion;
int x = 10;
int y = 10;

void configurar();
void generar();

int main(){
	do{
		system("cls");
		cout << "Bienvenido a la sopa de letras!\n\n";
		cout << "1. Crear sopa de letras\n";
		cout << "2. Configurar sopa de letras\n";
		cout << "3. Salir del programa\n\n";
		cout << "Introduzca su opcion: ";
		cin >> opcion;
		if (opcion == 1){
			if (diccionario[6] == ""){
				cout << "\nEl diccionario esta incompleto, por lo que no se puede continuar.\nVe a configuracion para agregar al menos siete palabras al diccionario.\n";
				system("pause");
				main();
			}
			else{
				generar();
			}
		}
		else if (opcion == 2){
			configurar();
		}
	}while (opcion!=3);
	system("cls");
	return 0;
}

void configurar(){
	do{
		system("cls");
		cout << "Menu de configuracion\n\n";
		cout << "1. Dimensiones\n";
		cout << "2. Diccionario\n";
		cout << "3. Volver al menu\n\n";
		cout << "Introduzca su opcion: ";
		cin >> opcion;
		if (opcion == 1){
			system("cls");
			cout << "Introduzca el valor horizontal (Minimo de 10 y maximo de 30): ";
			cin >> x;
			if (x < 10){
				x = 10;
				cout << "\nNo cumple con el requisito, por lo que se ha puesto como 10.";
			}
			else if (x > 30){
				x = 30;
				cout << "\nNo cumple con el requisito, por lo que se ha puesto como 30.";
			}
			cout << "\n\nAhora introduzca el valor vertical (Minimo de 10 y maximo de 30): ";
			cin >> y;
			if (y < 10){
				y = 10;
				cout << "\nNo cumple con el requisito, por lo que se ha puesto como 10.";
			}
			else if (y > 30){
				y = 30;
				cout << "\nNo cumple con el requisito, por lo que se ha puesto como 30.";
			}
			cout << "\n\n";
			system("pause");
			configurar();
		}
		else if(opcion == 2){
			system("cls");
			int contador;
			for (int i=0;i<7;i++){
				if (diccionario[i] != ""){
					contador++;
				}
			}
			if (contador < 7){
				cout << "El diccionario esta incompleto.";
			}
			else{
				cout << "El diccionaro esta completo.";
				cout << "\nDesea continuar? (si // no): ";
				string opcionS;
				cin >> opcionS;
				if (opcionS == "no"){
					configurar();
				}
		 	}
			for (int i=0;i<7;i++){
				cout << "\nIntroduzca la palabra numero " << i + 1 << " al diccionario: ";
				cin >> diccionario[i]; 
			}
		}
	}while(opcion !=3);
	main();
}

void generar(){
	// resetear
	for (int i=0;i<x;i++){
		for (int b=0;b<y;b++){
			char cch = 'a' + rand()%26;
			sopa[b][i].enUso = false;
			sopa[i][b].letra = cch;	
		}
		sopa[i][0].enUso = false;
	}
	// generar
	// TODO: arreglar superposicion
	int totalPalabras = 0;
	for (int i=0;i<x;i++){
		for (int b=0;b<y;b++){
			if (sopa[i][b].enUso == false){
				int N = ((rand() % 6));
				if (N == 1){
					int N = ((rand() % 2));
					if (N == 1){
						string palabra = diccionario[rand() % 6];
						int total = palabra.length();
						if ((i + total) <= y){
							bool safe = true;
							for (int c=0;c<total;c++){
								if (sopa[b][i + c].enUso == true){
									safe = false;
								}
							}
							if (safe == true){
								for (int c=0;c<total;c++){
									sopa[b][i + c].letra = palabra[c];
									sopa[b][i + c].enUso = true;
								}
								totalPalabras++;
							}
						}
					}
					else{
						string palabra = diccionario[rand() % 6];
						int total = palabra.length();
						// primero tenemos que chequear si hay espacio
						if ((b + total) <= x){
							bool safe = true;
							// luego tenemos que chequear si es "seguro" poner una palabra
							// si llega a haber algo malo, se va a considerar no seguro y se intentara en otro lado
							for (int c=0;c<total;c++){
								if (sopa[b + c][i].enUso == true){
									safe = false;
								}
							}
							if (safe == true){
								for (int c=0;c<total;c++){
									sopa[b + c][i].letra = palabra[c];
									sopa[b + c][i].enUso = true;
								}
								totalPalabras++;
							}
						}
					}
				}
			}
		}
	}
	cout << "\nTOTAL DE PALABRAS: " << totalPalabras;
	cout << "\n";
	for (int i=0;i<x;i++){
		for (int b=0;b<y;b++){
			cout << sopa[b][i].letra << " ";
		}
		cout << "\n";
	}
	system("pause");
}