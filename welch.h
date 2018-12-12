#include <time.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include <fft.h>

#define N_WELCH 64
#define PI 3.1415926536

void noise(complex_t[], int, double);
int welch(complex_t[], int, int);
void _welch_split(complex_t[], complex_t **, int, int);
void _welch_fft_average(complex_t **, complex_t[], int, int);
void _hamming(double[], int);