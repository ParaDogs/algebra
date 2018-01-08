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

//bool checkPrime

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
    int* elements;
    field(int _deg){
        deg = _deg;
    }
};

vector<matrix> expansion(field F, polynom P){ //Расширение поля F с помощью полинома P
    vector<matrix> result;
    matrix E(P.deg, P.mat->mod);
    for(int i = 0; i < P.deg; i++) E.table[i][i] = 1;
    for(int i = 0; i < (int)pow(F.deg, P.deg) + 1; i++)
        result.push_back(E*(i%F.deg) + ((*(P.mat))*((int)(i/F.deg)%F.deg)) + (((*(P.mat))^2)*((int)(i/(F.deg*F.deg))%F.deg)));
        //Тут происходит формирование поля расширения как всевозможных комбинаций корня и элементов поля
        //В данном случае вот так: E + A + A^2 (каждое слагаемое с коэффициентом от 0 до 5. Итого 5^3 элементов в поле)
        //Нужен(чтобы было прикольнее) более общий случай: E + A + A^2 + .. + A^(n-1), где n -- степень полинома
    return result;
}


int main(){
    field F5(N); //Изначальное поле
    polynom A(D, 2, 0, 3); //Сопр. матрица неприводимого полинома 3 степени над F5. Сюда просто вписываем последние 3 коэф. вашего полинома
    vector<matrix> exF5 = expansion(F5, A);

    for(int i = 0; i < (int)pow(F5.deg, A.deg)+1; i++){
        printf("%d - %d %d %d\n", i, i%F5.deg, (int)(i/F5.deg)%F5.deg, (int)(i/(F5.deg*F5.deg))%F5.deg);
        exF5[i].print();
    }


    return 0;
}
