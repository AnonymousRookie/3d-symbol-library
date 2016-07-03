/************************************************************************/
/*  最小二乘曲线拟合                                                        */
/************************************************************************/


#include "stdafx.h"
#include "LeastSquares.h"


CLeastSquares::CLeastSquares(void) {
    // Empty
}


CLeastSquares::~CLeastSquares(void) {
    // Empty
}

float  CLeastSquares::pow_n(float a, int32 n) {
    int32 i;
    if (n == 0)
        return (1);
    float res = a;
    for (i = 1; i < n; i++) {
        res *= a;
    }
    return (res);
}

void CLeastSquares::mutiple(float a[][L_N], float b[][L_T + 1], float c[][L_T + 1]) {
    float res = 0;
    int32 i, j, k;
    for (i = 0; i < L_T + 1; i++)
        for (j = 0; j < L_T + 1; j++) {
            res = 0;
            for (k = 0; k < L_N; k++) {
                res += a[i][k] * b[k][j];
                c[i][j] = res;
            }
        }
}

void CLeastSquares::matrix_trans(float a[][L_T + 1], float b[][L_N]) {
    int32 i, j;
    for (i = 0; i < L_N; i++) {
        for (j = 0; j < L_T + 1; j++) {
            b[j][i] = a[i][j];
        }
    }
}

void CLeastSquares::init(float x_y[][2], int32 n) {
    int32 i;
    printf("请输入%d个已知点：\n", L_N);
    for (i = 0; i < n; i++) {
        printf("(x%d y%d):", i, i);
        scanf("%f   %f", &x_y[i][0], &x_y[i][1]);
    }
}

void CLeastSquares::get_A(float matrix_A[][L_T + 1], float x_y[][2], int32 n) {
    int32 i, j;
    for (i = 0; i < L_N; i++) {
        for (j = 0; j < L_T + 1; j++) {
            matrix_A[i][j] = L_W * pow_n(x_y[i][0], j);
        }
    }
}

void CLeastSquares::print_array(float array[][L_T + 1], int32 n) {
    int32 i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < L_T + 1; j++) {
            printf("%-g      ", array[i][j]);
        }
        printf("\n");
    }
}

void CLeastSquares::convert(float argu[][L_T + 2], int32 n) {
    int32 i, j, k, p, t;
    float rate, temp;
    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            if (argu[i - 1][i - 1] == 0) {
                for (p = i; p < n; p++) {
                    if (argu[p][i - 1] != 0)break;
                }
                if (p == n) {
                    printf("方程组无解!\n");
                    exit(0);
                }
                for (t = 0; t < n + 1; t++) {
                    temp = argu[i - 1][t];
                    argu[i - 1][t] = argu[p][t];
                    argu[p][t] = temp;
                }
            }
            rate = argu[j][i - 1] / argu[i - 1][i - 1];
            for (k = i - 1; k < n + 1; k++) {
                argu[j][k] -= argu[i - 1][k] * rate;
                if (fabs(argu[j][k]) <= L_PRECISION)
                    argu[j][k] = 0;
            }
        }
    }
}

void CLeastSquares::compute(float argu[][L_T + 2], int32 n, float root[]) {
    int32 i, j;
    float temp;
    for (i = n - 1; i >= 0; i--) {
        temp = argu[i][n];
        for (j = n - 1; j > i; j--) {
            temp -= argu[i][j] * root[j];
        }
        root[i] = temp / argu[i][i];
    }
}

void CLeastSquares::get_y(float trans_A[][L_N], float x_y[][2], float y[], int32 n) {
    int32 i, j;
    float temp;
    for (i = 0; i < n; i++) {
        temp = 0;
        for (j = 0; j < L_N; j++) {
            temp += trans_A[i][j] * x_y[j][1];
        }
        y[i] = temp;
    }
}

void CLeastSquares::cons_formula(float coef_A[][L_T + 1], float y[], float coef_form[][L_T + 2]) {
    int32 i, j;
    for (i = 0; i < L_T + 1; i++) {
        for (j = 0; j < L_T + 2; j++) {
            if (j == L_T + 1)
                coef_form[i][j] = y[i];
            else
                coef_form[i][j] = coef_A[i][j];
        }
    }
}

void CLeastSquares::print_root(float a[], int32 n) {
    int32 i, j;
    printf("%d个点的%d次拟合的多项式系数为:\n", L_N, L_T);
    for (i = 0; i < n; i++) {
        printf("a[%d]=%g,", i + 1, a[i]);
    }
    printf("\n");
    printf("拟合曲线方程为:\ny(x)=%g", a[0]);
    for (i = 1; i < n; i++) {
        printf(" + %g", a[i]);
        for (j = 0; j < i; j++) {
            printf("*X");
        }
    }
    printf("\n");
}

void CLeastSquares::process(float (*input_points)[2], float* a) {
    float
    matrix_A[L_N][L_T + 1],
             trans_A[L_T + 1][L_N],
             coef_A[L_T + 1][L_T + 1],
             coef_formu[L_T + 1][L_T + 2],
             y[L_T + 1];
    get_A(matrix_A, input_points, L_N);
    matrix_trans(matrix_A, trans_A);
    mutiple(trans_A, matrix_A, coef_A);
    get_y(trans_A, input_points, y, L_T + 1);
    cons_formula(coef_A, y, coef_formu);
    convert(coef_formu, L_T + 1);
    compute(coef_formu, L_T + 1, a);
}

