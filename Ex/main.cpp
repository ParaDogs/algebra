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

bool checkPrimitive(vector<matrix> F, matrix m){
    int j = 1;
    while((j < F.size()) && !(F[1] == (m^j))) j++;
    if(j == F.size() - 1) return true;
    return false;
}

struct polynom{ //Полином, характеризующийся своей сопровождающей матрицей
    int deg;
    matrix* mat;
    polynom(int d, ...){
        int i(d-1); int* p = &d;
        this->deg = d;
        this->mat = new matrix(d, N);
        while(i >= 0){
            this->mat->table[i][i-1] = 1;
            this->mat->table[i--][d-1] = negative<N>(*(++p));
        }
    }
};

struct field{ //Поле остатков по модулю простого числа
    int deg;
    field(int _deg){
        deg = _deg;
    }
};

vector<matrix> expansion(field F, polynom P){ //Расширение поля F с помощью полинома P
    vector<matrix> result;
    matrix E(P.deg, P.mat->mod);
    for(int i = 0; i < P.deg; i++) E.table[i][i] = 1;
    matrix Pt1 = *(P.mat);
    matrix Pt2 = (*(P.mat))^2;
    int d = F.deg;

    for(int i = 0; i < (int)pow(d, P.deg) + 1; i++)
        result.push_back(E*(i%d) + Pt1*((i/d)%d) + Pt2*((i/(d*d))%d));

    return result;
}


int main(){
    field F5(N); //Изначальное поле
    polynom A(D, 2, 0, 3); //Сопр. матрица неприводимого полинома 3 степени над F5. Сюда просто вписываем последние 3 коэф. вашего полинома
    vector<matrix> exF5 = expansion(F5, A);

    int c(0);
    for(int i = 0; i < 125; i++){
        bool p = checkPrimitive(exF5, exF5[i]);
        //exF5[i].print();
        printf("%s\n", (p ? "true" : "false"));
        if(p) c++;
    }
    printf("%d\n", c);
    printf("Polinomial root is primitive? %s\n", (checkPrimitive(exF5, *(A.mat)) ? "true" : "false"));
    return 0;
}
