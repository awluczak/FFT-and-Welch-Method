#include <complex.h>

/* Complex multiply */
complex_t complex_mul(complex_t z1, complex_t z2) {
	complex_t result;
	result.real = z1.real*z2.real - z1.imag*z2.imag;
	result.imag = z1.real*z2.imag + z1.imag*z2.real;
	return result;
}

/* Complex add */
complex_t complex_add(complex_t z1, complex_t z2) {
	complex_t result;
	result.real = z1.real + z2.real;
	result.imag = z1.imag + z2.imag;
	return result;
}

/* Complex substract */
complex_t complex_sub(complex_t z1, complex_t z2) {
	complex_t result;
	result.real = z1.real - z2.real;
	result.imag = z1.imag - z2.imag;
	return result;
}

/* Complex conjugate */
complex_t conjugate(complex_t z) {

	z.imag = -(z.imag);
	return z;
}
