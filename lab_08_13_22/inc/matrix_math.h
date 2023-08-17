#include <stdlib.h>

#ifndef __MATRIX_MATH__

#define __MATRIX_MATH

void matrix_addition(double **arr1, double **arr2, double ***arr3, int height, int width);
void matrix_multiplication(double **arr1, double **arr2, double ***arr3, int height[], int width[]);
int calc_determinant(double **arr, size_t size, double *det);

#endif