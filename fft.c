#include <fft.h>

void _fft(complex_t signal[], complex_t out[], double sin_table[], double cos_table[], int n, int step)
{
	if (step < n) {
		_fft(out, signal, sin_table, cos_table, n, step * 2);
		_fft(out + step, signal + step, sin_table, cos_table, n, step * 2);

		for (int i = 0; i < n; i += 2 * step) {
			complex_t c;
			c.real = cos_table[i];
			c.imag = sin_table[i];
			complex_t t = complex_mul(c,out[i + step]);
			signal[i / 2] = complex_add(out[i],t);
			signal[(i + n) / 2] = complex_sub(out[i],t);
		}
	}
}

void fft(complex_t signal[], int n)
{
	complex_t * out = malloc(n * sizeof(complex_t));
	for (int i = 0; i < n; i++) out[i] = signal[i];

	double * sin_table = malloc(n * sizeof(double));
	double * cos_table = malloc(n * sizeof(double));

	for (int i = 0; i < n; i++) {
		sin_table[i] = sin(-PI * i / n);
		cos_table[i] = cos(-PI * i / n);
	}

	_fft(signal, out, sin_table, cos_table, n, 1);
	free(out);
}

void ifft(complex_t buf[], int n) {

	for (int i = 0; i < n; i++)
		buf[i] = conjugate(buf[i]);

	fft(buf, n);

	for (int i = 0; i < n; i++) {
		buf[i] = conjugate(buf[i]);
		buf[i].real = buf[i].real / n;
		buf[i].imag = buf[i].imag / n;
	}
}

void magnitude(complex_t fft[], int n) {

	for (int i = 0; i < n; i++) {

		fft[i].real = sqrt(pow(fft[i].real, 2) + pow(fft[i].imag, 2));
		fft[i].imag = 0.0;

	}
	return;
}