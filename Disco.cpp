#include "Disco.h"

Disco::Disco(){}
Disco::Disco(int color, int tamano_disco, int posicion_x, int posicion_y, int fila, char indicador,string indicador_vacio){
    this->color = color;
    this->tamano_disco = tamano_disco;
    this->posicion_x = posicion_x;
    this->posicion_y= posicion_y;
    this->fila = fila;
    this->indicador_aguja = indicador;
    this->indicador_lleno_vacio = indicador_vacio;
}

int Disco::get_color(){
    return color;
}

string Disco::get_indicador_lleno(){
    return indicador_lleno_vacio;
}
void Disco::set_posicionY(int new_y){
    this->posicion_y = new_y;
}
int Disco::get_posicionY(){
    return posicion_y;
}
int Disco::get_fila(){
    return fila;
}
int Disco::get_tamando_disco(){
    return tamano_disco;
}

char Disco::get_indicador_aguja(){
    return indicador_aguja;
}
Disco::~Disco(){}