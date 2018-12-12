#include <fft.h>
#include <stdlib.h>
#include <stdio.h>
#include <welch.h>

#define PRINT(x) printf("%f\n",x);

#define N_SAMPLES 1024
#define AMPLITUDE 1.0

void write_csv(complex_t[], int, char *);
void copy_signal(complex_t[], complex_t[], int);

	