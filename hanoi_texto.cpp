//hanoi_texto.cpp - Miguel Rojas - 11941201
#include <iostream>
using namespace std;

void metodo_hanoi(int, int, int, int);

int main(){
    int numero_discos;
    cout << "Numero de discos: ";
    cin >> numero_discos;
    metodo_hanoi(numero_discos,1,2,3);
    return 0;
}

void metodo_hanoi(int numero_discos, int aguja_principal, int aguja_temporal, int aguja_destino){

    if (numero_discos == 1){
        cout << aguja_principal << " → " << aguja_destino << endl;
    }else{
        metodo_hanoi(numero_discos - 1, aguja_principal, aguja_destino, aguja_temporal);
        cout << aguja_principal << " → " << aguja_destino << endl;
        metodo_hanoi(numero_discos - 1, aguja_temporal, aguja_principal, aguja_destino);
    }
}