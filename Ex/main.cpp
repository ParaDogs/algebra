#include <stdio.h>
#include "matrix_lib.h"
#include <cmath>
#include <vector>
#define N 5
#define D 3

using namespace std;

template <size_t T>
int negative(int a){
    return (T - a) % T;
}

struct polynom{ //Полином, характеризующийся своей сопрофождающей матрицей
    int deg;
    matrix* mat;
    polynom(int d, ...){
        int i(d-1); int* p = &d;
        this->deg = d;
        this->mat = new matrix(d);
        while(i >= 0){
            this->mat->table[i][i-1] = 1;
            this->mat->table[i--][d-1] = negative<N>(*(++p));
        }
    }
};

struct field{ //Поле остатков по модулю простого числа
    int deg;
    int* elements;
    field(int _deg){
        deg = _deg;
        elements = new int[deg];
        for(int i = 0; i < deg; i++)
            elements[i] = i;
    }
};

vector<matrix> expansion(field F, polynom P){ //Расширение поля F с помощью полинома P
    vector<matrix> result;
    matrix E(P.deg);
    for(int i = 0; i < P.deg; i++) E.table[i][i] = 1;
    for(int i = 0; i < (int)pow(F.deg, P.deg); i++){
        //result.push_back( E + (P.mat * i % F.deg)
    }
}


int main(){
    field F5(N); //Изначальное поле
    polynom A(D, 2, 0, 3); //Сопр. матрица неприводимого полинома 3 степени над F5



    return 0;
}
