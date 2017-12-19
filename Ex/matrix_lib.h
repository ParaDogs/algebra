#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <math.h>

class matrix{
    public:
        int rows, cols;
        int** table;
        matrix(int n, int m);
        matrix(int n);
        void fill(int a, int b);
        void print();
        friend matrix operator + (matrix m1, matrix m2);
        friend matrix operator * (matrix m1, matrix m2);
        friend matrix operator * (matrix m1, int a);
        float det();
        matrix minor(int l, int k);
        matrix uni();
        matrix trans();
        matrix invert();
};
#endif

