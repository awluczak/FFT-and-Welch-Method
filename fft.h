#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define PI 3.1415926536

void _fft(complex_t[], complex_t[], double[], double [], int, int);
void fft(complex_t[], int);
void ifft(complex_t[], int);
void magnitude(complex_t[], int);