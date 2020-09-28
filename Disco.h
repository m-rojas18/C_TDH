
#ifndef DISCO_H
#define DISCO_H
#include <string>
using namespace std;
class Disco {

    private:
        char indicador_aguja;
        int color;
        int tamano_disco;
        int posicion_x;
        int posicion_y;
        int fila;
        string indicador_lleno_vacio;
    public:
        Disco();
        Disco(int,int,int,int, int,char,string);
        char get_indicador_aguja();
        int get_fila();
        int get_posicionX();
        int get_posicionY();
        string get_indicador_lleno();
        int get_color();
        int get_tamando_disco();
        void set_posicionY(int);
        void set_PosicionX(int);
        void set_fila(int);
        ~Disco();
};
#endif