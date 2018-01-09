#include <stdio.h>
#include "matrix_lib.h"
//#include <cmath>
#include <vector>
#define N 5
#define D 3

using namespace std;

template <size_t T>
int negative(int a){
    return (T - a) % T;
}

bool checkPrimitive(vector<matrix> F, matrix m){
    int j;
    for(int i = 1; i < F.size(); i++){
        j = 1;
        while((j < F.size()) && !(F[i] == (m^j))) j++;
        if(j == F.size()) return false;
    }
    return true;
}

struct polynom{ //Полином, характеризующийся своей сопровождающей матрицей
    int deg;
    matrix* mat;
    polynom(int d, vector<int> v){
        this->deg = d;
        this->mat = new matrix(d, N);
        for (int i = d-1; i >= 0; --i) {
            if(i != 0) this->mat->table[i][i-1] = 1;
            this->mat->table[i][d-1] = negative<N>(v[d-i-1]);
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
    for(int i = 0; i < (int)pow(F.deg, P.deg); i++)
        result.push_back(E*(i%F.deg) + ((*(P.mat))*((int)(i/F.deg)%F.deg)) + (((*(P.mat))^2)*((int)(i/(F.deg*F.deg))%F.deg)));
        //Тут происходит формирование поля расширения как всевозможных комбинаций корня и элементов поля
        //В данном случае вот так: E + A + A^2 (каждое слагаемое с коэффициентом от 0 до 5. Итого 5^3 элементов в поле)
        //Нужен(чтобы было прикольнее) более общий случай: E + A + A^2 + .. + A^(n-1), где n -- степень полинома
    return result;
}


int main(){
    field F5(N); //Изначальное поле
    vector<int> v = {2, 0, 3};
    polynom A(D, v); //Сопр. матрица неприводимого полинома 3 степени над F5. Сюда просто вписываем последние 3 коэф. вашего полинома
    vector<matrix> exF5 = expansion(F5, A);

    int c = 0;
    for(int i = 0; i < 125; ++i){
        bool b = checkPrimitive(exF5, exF5[i]);
        cout << ( b ? "true" : "false" ) << endl;
        if (b) c++;
    }
    cout << c << endl;

    return 0;
}
