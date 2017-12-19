#include <stdio.h>
#include "matrix_lib.h"

struct field{
    int deg;
};

struct polynom{ //нормал, осталось только инты на элементы пол€ заменить. ј еще как-нибудь красивее сделать
    int deg;
    matrix* mat;
    polynom(int d, ...){
        int i(d); int* p = &d;
        this->deg = d;
        this->mat = new matrix(d + 1);
        while(i >= 0){
            this->mat->table[i][i-1] = 1;
            this->mat->table[i--][d] = -*(++p);
        }
    }
};

int main(){
    polynom A(3, 1, 2, 0, 3);
    A.mat->print();
    return 0;
}
