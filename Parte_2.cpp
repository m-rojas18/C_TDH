//hanoii_ascii.cpp - Miguel Angel Rojas Herrera - 11941201
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void hanoi(int, int, int, int);
void creacion_discos(string **, int, int);
void movimiento_discos(string**,int,int);
void impresion_hanoi(string**);


string **matriz;
int filas, columnas;
int main(){

    int cantidad_discos;
    cout << "Numero de discos: ";
    cin >> cantidad_discos;
    //Crear matriz
    filas = cantidad_discos;
    columnas = ((filas * 2) - 1) * 3;
    int num_columna_cuadrante1 = (filas * 2) - 1;
    matriz = new string *[filas];
    for (int i = 0; i < filas; i++){
        matriz[i] = new string[columnas];
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = " ";
        }
        
    }
    creacion_discos(matriz, filas, num_columna_cuadrante1);
    impresion_hanoi(matriz);
    //Llamada a metodo hanoi
    hanoi(cantidad_discos,1,2,3);

    
    //Liberar Memoria
    for (int i = 0; i < filas; i++){
        matriz[i] = NULL;
        delete[] matriz[i];
    }
    delete[] matriz;
    return 0;
}

void movimiento_discos(string** matriz,int aguja_origen, int aguja_destino){
    int columna_aguja_origen, columna_aguja_destino;


    //Calcular posicion de la columna origen y destino
    if(aguja_origen == 1){
        columna_aguja_origen = ((filas * 2) - 1) / 2;
    } else  if(aguja_origen == 2){
        //Aguja Auxiliar
        columna_aguja_origen = columnas / 2;
    } else {
        //Aguja Destino es origen
        columna_aguja_origen = columnas  - ( ((filas * 2) - 1) / 2);
        columna_aguja_origen--;
    }

    if(aguja_destino == 2){
        //Aguja Auxilia
        columna_aguja_destino = columnas / 2;
    } else if(aguja_destino == 3){
        //Aguja Destino
        columna_aguja_destino = columnas  - ( ((filas * 2) - 1) / 2);
        columna_aguja_destino--;
    } else {
        //Aguja Origen es el destino
        columna_aguja_destino = ((filas * 2) - 1) / 2;
    }
    int posicion_fila_origen, temp_filas = filas - 1;

    //cout << "Columna Aguja Origen = " << columna_aguja_origen << " Columna Aguja Destino " << columna_aguja_destino << endl;
    //Encontrar objeto mas pequeño en la aguja origen
    while(temp_filas >= 0){
        if(matriz[temp_filas][columna_aguja_origen] == "\u2588"){
            posicion_fila_origen = temp_filas;
        }
        temp_filas--;
    }
    //Buscar si posicion en la aguja destino esta disponible
    temp_filas = filas - 1;
    int posicion__fila_destino;
    while(temp_filas >= 0){
        if(matriz[temp_filas][columna_aguja_destino] != "\u2588" && temp_filas == posicion_fila_origen){
            posicion__fila_destino = temp_filas;
        }
        temp_filas--;
    }

    int contador_espacios;
    int cuadrante_columnas_origen = (filas * 2) - 1;
    //Realizar Cambio en las posiciones
    if(aguja_origen == 1){
        for (int i = 0; i < cuadrante_columnas_origen; i++){
            if(matriz[posicion_fila_origen][i] == "\u2588"){
                matriz[posicion_fila_origen][i] = " ";
            }
        }
        
    } else if(aguja_origen == 2) {
        //Aguja origen es auxiliar
        //cout << "Posicion Fila " << posicion_fila << endl;
        for (int i = cuadrante_columnas_origen; i < cuadrante_columnas_origen * 2; i++){
            if(matriz[posicion_fila_origen][i] == "\u2588"){
                matriz[posicion_fila_origen][i] = " ";
            }
        }

    } else {
        //Aguja origen es la destino
        for (int i = cuadrante_columnas_origen * 2; i < columnas; i++){
            if(matriz[posicion_fila_origen][i] == "\u2588"){
                matriz[posicion_fila_origen][i] = " ";
            }
        }

    }

    //Cambio en el destino
    if(aguja_destino == 3){
        //Aguja  Destino
        for (int i = cuadrante_columnas_origen * 2; i < columnas; i++){
            if (i >= columna_aguja_destino && i <= columna_aguja_destino + posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            } else if (i <= columna_aguja_destino && i >= columna_aguja_destino- posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            }else{
                matriz[posicion_fila_origen][i] = " ";
            }
        }
    } else if(aguja_destino == 2){
        //Origen Auxiliar
        for (int i = cuadrante_columnas_origen; i < cuadrante_columnas_origen * 2; i++){
            if (i >= columna_aguja_destino && i <= columna_aguja_destino + posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            } else if (i <= columna_aguja_destino && i >= columna_aguja_destino - posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            }else{
                matriz[posicion_fila_origen][i] = " ";
            }
        }
    } else {
        //Destino es la aguja origen
        for (int i = 0; i < cuadrante_columnas_origen; i++){
            if (i >= columna_aguja_destino && i <= columna_aguja_destino + posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            } else if (i <= columna_aguja_destino && i >= columna_aguja_destino - posicion_fila_origen){
                matriz[posicion_fila_origen][i] = "\u2588";
            }else{
                matriz[posicion_fila_origen][i] = " ";
            }
        }
    }
    impresion_hanoi(matriz);
}


void creacion_discos(string **matriz, int filas, int columnas){
    //Llenar solo el primer cuadrante de la matriz con los discos
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (j >= (columnas / 2) && j <= (columnas / 2) + i){
                matriz[i][j] = "\u2588";
            } else if (j <= (columnas / 2) && j >= (columnas / 2) - i){
                matriz[i][j] = "\u2588";
            }else{
                matriz[i][j] = " ";
            }
        }
    }
}

void impresion_hanoi(string **matriz){
    int temp = (filas * 2) - 1;
    int impresion_letras = temp / 2;
    cout << setw(impresion_letras + 2) << "A:" << setw(columnas / 2 + 1) << "B:" << setw(columnas / 2 + 1)  << "C:"<< endl;

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if(j == columnas - 1){
                cout << matriz[i][j];
                cout << " |";
            } else {
                if(j == temp || j == temp * 2 || j == temp * 3){
                    cout  <<  " | " << matriz[i][j];
                } else {
                    cout << matriz[i][j];
                }
            }     
        }
        cout << endl;
    }
    for (int i = -2; i <= columnas / 2; i++)
        cout << "--";
    cout << "---";
    cout  << endl << endl;
}

//"\u2192"
void hanoi(int numero_discos, int aguja_origen, int aguja_auxiliar, int aguja_destino){

    if (numero_discos == 1){
        movimiento_discos(matriz, aguja_origen, aguja_destino);
    }else{
        hanoi(numero_discos - 1, aguja_origen, aguja_destino, aguja_auxiliar);
        movimiento_discos(matriz, aguja_origen, aguja_destino);
        hanoi(numero_discos - 1, aguja_auxiliar, aguja_origen, aguja_destino);
    }
}

