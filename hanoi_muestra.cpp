//hanoi_muestra.cpp - Miguel Angel Rojas Herrera - 11941201
#include <iostream>
#include <string>
#include <ncurses.h>
#include <vector>
#include "Disco.h"
using namespace std;

void impresiones_ventana();
void creacion_discos(int,int);
void movimiento_discos(int,int,int);
void hanoi(int,int,int,int);
void imprimir_aguja();

WINDOW *ventana_principal;
int contador_movimientos = 0, maximo_x, maximo_y, salir = 0;
vector<Disco*> lista_discos_origen;
vector<Disco*> lista_discos_auxiliar;
vector<Disco*> lista_discos_destino;

int main(){
    initscr();
    noecho();
    int numero_discos = 0;
    cout << "Ingrese numero de discos: ";
    cin >> numero_discos;

    //Crear vector de Discos
    getmaxyx(stdscr, maximo_y, maximo_x);
    //Inicializar Ventana
    ventana_principal = newwin(maximo_y,maximo_x, 0, 0);
    start_color();
    box(ventana_principal,0,0);
    refresh();
    wrefresh(ventana_principal);
    //Colores
    init_pair(1,COLOR_BLACK, COLOR_WHITE);//Blanco
    init_pair(2,COLOR_BLACK, COLOR_GREEN);//Verde
    init_pair(3,COLOR_BLACK,COLOR_YELLOW);//Amarillo
    init_pair(4,COLOR_BLACK,COLOR_CYAN);//Cyan
    init_pair(5,COLOR_BLACK,COLOR_BLUE);//Blue
    init_pair(6,COLOR_BLACK, COLOR_RED);//Rojo
    init_pair(7,COLOR_BLACK, COLOR_MAGENTA);//Magenta
    int aguja_origen = (maximo_x / 2) - 21;
    int aguja_auxiliar = maximo_x / 2 - 1;
    int aguja_destino = maximo_x / 2 + 19;
    creacion_discos(numero_discos, aguja_origen);
    int posicion_fila_aux_des = maximo_y - 8;
    for (int i = 0; i < numero_discos; i++){
        lista_discos_auxiliar.push_back(new Disco(8,0,posicion_fila_aux_des, aguja_auxiliar,i + 1 ,'a', "Empty"));
        lista_discos_destino.push_back(new Disco(8,0,posicion_fila_aux_des, aguja_destino, i + 1,'d', "Empty"));
        posicion_fila_aux_des--;
    }
    impresiones_ventana();
    movimiento_discos(numero_discos,1,3);
    contador_movimientos++;
    hanoi(numero_discos,1,2,3);
    salir = getch();
    
    endwin();
    return 0;
}

void hanoi(int numero_discos, int aguja_origen, int aguja_auxiliar, int aguja_destino){

    if (numero_discos == 1){
        salir = getch();
        if(salir == 27){
            endwin();
        }
        contador_movimientos++;
        impresiones_ventana();
        movimiento_discos(numero_discos,aguja_origen,aguja_destino);
    }else{
        hanoi(numero_discos - 1, aguja_origen, aguja_destino, aguja_auxiliar);
        salir = getch();
        if(salir == 27){
            endwin();
        }
        contador_movimientos++;
        impresiones_ventana();
        //movimiento_discos(numero_discos,aguja_origen,aguja_destino);
        hanoi(numero_discos - 1, aguja_auxiliar, aguja_origen, aguja_destino);

    }
}

void movimiento_discos(int numero_discos, int aguja_origen, int aguja_destino){

    int columna_origen, columna_destino;
    vector<Disco*> lista_origen_temp, lista_destino_temp;
    //Conseguir posicion de columna inicial
    if(aguja_origen == 1){
        columna_origen = (maximo_x / 2) - 21;//Aguja 1 (Origen)
        lista_origen_temp = lista_discos_origen;
    } else if(aguja_origen == 2){ 
        columna_origen = (maximo_x / 2) - 1;//Aguja 2(Auxiliar)
        lista_origen_temp = lista_discos_auxiliar;
    } else {
        columna_origen = (maximo_x / 2) + 19;//Aguja 3 (destino)
        lista_origen_temp = lista_discos_destino;
    }
    //Conseguir posicion de columno a mover
    if(aguja_destino == 3){
        columna_destino = (maximo_x / 2) + 19;//Aguja 3
        lista_destino_temp = lista_discos_destino;
    } else if(aguja_destino == 2){
        columna_destino = (maximo_x / 2) - 1;//Aguja 2
        lista_destino_temp = lista_discos_auxiliar;
    } else {
        columna_destino = (maximo_x / 2) - 21;//Aguja 1
        lista_destino_temp = lista_discos_origen;
    }
    refresh();
    
    int contador_fila = 0;
    int posicion_fila_origen = 0;
    //Buscar el disco mas pequeño en la aguja origen
    while(contador_fila < lista_origen_temp.size() ){
        if(lista_origen_temp.at(contador_fila)->get_indicador_lleno() == "Full"){
            posicion_fila_origen = contador_fila;
        }
        contador_fila++;
    }

    //Buscar si hay un disco en el destino
    //Buscar posicion disponible en aguja destino
    contador_fila = 0;
    int posicion_fila_destino;
    while(contador_fila < lista_destino_temp.size()){
        if(lista_destino_temp.at(contador_fila)->get_indicador_lleno() == "Empty"){
            posicion_fila_destino = contador_fila;
            break;
        }
        contador_fila++;
    }
}

void creacion_discos(int numero_disco, int aguja_origen){
    
    int contador_color = 2, contador_fila = 1, numero_cajas = 3, posicion_fila = maximo_y - 8;
    for (int i = 0; i < numero_disco; i++){
        if(i == 6){
            contador_color = 2;
        } 
        if(i > 0){
            numero_cajas = numero_cajas + 2;
        }
        Disco * temporal = new Disco(contador_color,numero_cajas,posicion_fila, aguja_origen, contador_fila, 'o', "Full");
        lista_discos_origen.push_back(temporal);
        contador_color++;
        contador_fila++;
        posicion_fila--;
    }
    attron(COLOR_PAIR(1));
    //Impresion de Agujas
    for (int i = maximo_y - 8; i  > maximo_y - 19; i--) {
        mvprintw(i, (maximo_x / 2) - 21, " ");//Aguja Origen
        mvprintw(i, maximo_x / 2 - 1, " ");//Aguja Auxiliar
        mvprintw(i, maximo_x / 2 + 19, " ");//Aguja Destino
    }
    attroff(COLOR_PAIR(1));

    int contador = 1, numero_rectangulos = (numero_disco * 2 ), contador_colores = 2;
    int posicion_columna = maximo_y - 8;
    //Impresion de Discos
    while(contador <= numero_disco){
        if(contador == 7)
            contador_colores = 2;
        //Impresion por fila
        attron(COLOR_PAIR(contador_colores));
        for (int i = 0; i <= numero_rectangulos / 2; i++){
            mvprintw(posicion_columna, aguja_origen + i, " ");//Imprimir Espacios a la derecha
            mvprintw(posicion_columna, aguja_origen - i, " ");//Imprimir Espacios a la izquierda
        } 
        attroff(COLOR_PAIR(contador_colores));
        numero_rectangulos = numero_rectangulos - 2;
        posicion_columna--;
        contador_colores++;
        contador++;
    }  
    refresh();
}
void impresiones_ventana(){
    //Impresiones en Duro
    mvprintw(0,(maximo_x / 2 ) - 32 / 2 ," T O R R E S   D E   H A N O I ");
    mvprintw(maximo_y - 1, (maximo_x / 2)  - 34/2 ," P R O G R A M A C I O N   I I I ");
    attron(COLOR_PAIR(1));
    mvprintw(2, (maximo_x / 2) - 24," MUESTRA DE MOVIMIENTOS NECESARIOS PASO A PASO");
    mvprintw( maximo_y - 4, (maximo_x / 2) - 32, " Presione cualquier tecla para continuar o ESC para finalizar ");
    attroff(COLOR_PAIR(1));
    mvprintw(maximo_y - 3, (maximo_x / 2) - 20, "Desarrollado por Miguel Rojas (11941201)");
    //Impresion de Aguja
    attron(COLOR_PAIR(1));
    mvprintw(maximo_y - 7, (maximo_x / 2) - 32 , "                                                               ");
    //Escribir numeros
    mvprintw(maximo_y - 7, (maximo_x / 2) - 21, "1");
    mvprintw(maximo_y - 7, (maximo_x / 2) - 1, "2");
    mvprintw(maximo_y - 7, (maximo_x / 2) + 19, "3");
    attroff(COLOR_PAIR(1));

    //Impresion de Contador
    string salida_string = "MOVIMIENTO # ";
    const char *salida_contador;
    if(contador_movimientos >= 10  &&  contador_movimientos < 100){
        salida_string = salida_string + "0" + to_string(contador_movimientos);
        salida_contador = salida_string.c_str();
        mvprintw(3, (maximo_x / 2) - 17/2, salida_contador);
    } else if(contador_movimientos >= 100){
        salida_string = salida_string + to_string(contador_movimientos);
        salida_contador = salida_string.c_str();
        mvprintw(3, (maximo_x / 2) - 17/2, salida_contador);
    } else {
        salida_string = salida_string + "00" + to_string(contador_movimientos);
        salida_contador = salida_string.c_str();
        mvprintw(3, (maximo_x / 2) - 17/2, salida_contador);
    }
    salida_string = " ";
    //Dibujar Rectangulo verde
    attron(COLOR_PAIR(2));
    mvprintw(maximo_y - 4,(maximo_x / 2) + 30, " ");
    attroff(COLOR_PAIR(2));
}