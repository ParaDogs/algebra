#include <stdio.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include "matrix_lib.h"

matrix::matrix(int n, int m){
    rows = n; cols = m;
    table = new int*[rows];
    for (int i = 0; i < rows; i++)
        table[i] = new int[cols];
    this->fill(0, 1);
}

matrix::matrix(int n){
    rows = n; cols = n;
    table = new int*[rows];
    for (int i = 0; i < rows; i++)
        table[i] = new int[cols];
    this->fill(0, 1);
}

void matrix::fill(int a, int b){
    srand(time(NULL));
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            this->table[i][j] = a + rand()%b;
}

void matrix::print(){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++)
            printf("%d\t", this->table[i][j]);
        printf("\n");
    }
    printf("\n");
}

matrix operator + (matrix m1, matrix m2){
    if((m1.cols != m2.cols)||(m1.rows != m2.rows)) throw -1;
    else{
        matrix result(m1.rows, m1.cols);
        for(int i = 0; i < result.rows; i++)
            for(int j = 0; j < result.cols; j++)
                result.table[i][j] = m1.table[i][j] + m2.table[i][j];
        return result;
    }
}

matrix operator * (matrix m1, matrix m2){
    if(m1.cols != m2.rows) throw -1;
    else{
        matrix result(m1.rows, m2.cols);
        result.fill(0, 1);
        for(int i = 0; i < result.rows; i++)
            for(int j = 0; j < result.cols; j++)
                for(int k = 0; k < m1.cols; k++)
                    result.table[i][j] += m1.table[i][k] * m2.table[k][j];
        return result;
    }
}

matrix operator * (matrix m1, int a){
    matrix result(m1.rows, m1.cols);
    for(int i = 0; i < result.rows; i++)
        for(int j = 0; j < result.cols; j++)
            result.table[i][j] = m1.table[i][j] * a;
    return result;
}

matrix operator ^ (matrix m1, int a){
    matrix result(m1.rows);
    result = m1;
    if(a == 0){
        matrix E(m1.rows);
        for(int i = 0; i < m1.rows; i++) E.table[i][i] = 1;
        return E;
    }
    for(int i = 0; i < a; i++){
        result = result * m1;
    }
    return result;
}

float matrix::det(){
    if(this->rows != this->cols) throw -1;
    else if(this->cols != 1){
        int result(0);
        for(int i = 0; i < this->rows; i+=2)
            result += this->table[0][i] * this->minor(0, i).det();
        for(int i = 1; i < this->rows; i+=2)
            result -= this->table[0][i] * this->minor(0, i).det();
        return result;
    }else return this->table[0][0];
}

matrix matrix::minor(int l, int k){
    if((l > this->rows-1)||(k > this->cols-1)) throw -1;
    else{
        matrix result(this->rows-1, this->cols-1);
        for(int i = 0; i < l; i++){
            for(int j = 0; j < k; j++)
                result.table[i][j] = this->table[i][j];
            for(int j = k + 1; j < this->cols; j++)
                result.table[i][j-1] = this->table[i][j];
        }
        for(int i = l + 1; i < this->rows; i++){
            for(int j = 0; j < k; j++)
                result.table[i-1][j] = this->table[i][j];
            for(int j = k + 1; j < this->cols; j++)
                result.table[i-1][j-1] = this->table[i][j];
        }
        return result;
    }
}

matrix matrix::uni(){
    matrix result(this->rows, this->cols);
    for(int i = 0; i < result.rows; i++)
        for(int j = 0; j < result.cols; j++)
            result.table[i][j] = this->minor(i, j).det() * pow(-1, i + j);
    return result;
}

matrix matrix::trans(){
    matrix result(this->cols, this->rows);
    for(int i = 0; i < result.rows; i++)
        for(int j = 0; j < result.cols; j++)
            result.table[i][j] = this->table[j][i];
    return result;
}

matrix matrix::invert(){
    if(this->det() == 0) throw -1;
    else return this->uni().trans() * (1/this->det());
}
