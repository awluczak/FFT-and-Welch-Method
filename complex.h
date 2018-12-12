#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <stdlib.h>

typedef struct {
	double real;
	double imag;
} complex_t;


complex_t complex_mul(complex_t, complex_t);
complex_t complex_add(complex_t, complex_t);
complex_t complex_sub(complex_t, complex_t);
complex_t conjugate(complex_t);

#endif