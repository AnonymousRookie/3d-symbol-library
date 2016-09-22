/************************************************************************/
/*  最小二乘曲线拟合                                                        */
/************************************************************************/

#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include "../Base/ZTypes.h"


#define L_N 3   // N个点
#define L_T 2   // T次拟合
#define L_W 1   // 权函数
#define L_PRECISION 0.00001

class CLeastSquares {
  public:
    CLeastSquares(void);
    ~CLeastSquares(void);


  public:
    float pow_n(float a, int32 n);
    void mutiple(float a[][L_N], float b[][L_T + 1], float c[][L_T + 1]);
    void matrix_trans(float a[][L_T + 1], float b[][L_N]);
    void init(float x_y[][2], int32 n);
    void get_A(float matrix_A[][L_T + 1], float x_y[][2], int32 n);
    void print_array(float array[][L_T + 1], int32 n);
    void convert(float argu[][L_T + 2], int32 n);
    void compute(float argu[][L_T + 2], int32 n, float root[]);
    void get_y(float trans_A[][L_N], float x_y[][2], float y[], int32 n);
    void cons_formula(float coef_A[][L_T + 1], float y[], float coef_form[][L_T + 2]);
    void print_root(float a[], int32 n);
    void process(float (*input_points)[2], float* a);
};

#endif  // LEAST_SQUARES_H