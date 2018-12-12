#include <welch.h>

void noise(complex_t signal[], int n, double amplitude){

	double * noise = malloc(n * sizeof(double));
	double max = 0.0;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++) {
		noise[i] = (double)((rand() % 2000) - 1000)*amplitude/1000.0;
		signal[i].real = signal[i].real + noise[i];
	}

	return;
}

int welch(complex_t signal[], int n, int n_welch) {

	//segments count 
	int count;

	//check if singal can be divided into odd or even number of segments
	if (n % n_welch == 0)
		count = (2 * n / n_welch) - 1;
	else if (n % n_welch == n_welch / 2)
		count = (2 * (int)floor(n / n_welch));
	else
		return 1;

	//allocate 2d array containing each segment
	complex_t ** segment = malloc(count * sizeof(complex_t *));
	for (int i = 0; i < count; i++) {
		segment[i] = malloc(n_welch * sizeof(complex_t));
	}

	//split signal into segment array
	_welch_split(signal, segment, n_welch, count);
	
	//calulate fft for each segment and average spectrograms
	_welch_fft_average(segment, signal, n_welch, count);

	//cleanup
	for (int i = 0; i < count; i++) {
		free(segment[i]);
	}
	free(segment);
	return 0;
}

void _welch_split(complex_t signal[], complex_t ** segment, int n_welch, int count) {

	//assign each value in segment array
	for (int i = 0; i < count; i++) {
		if (!i % 2) {
			for (int j = 0; j < n_welch; j++)
				segment[i][j] = signal[n_welch*i / 2 + j];
		}
		else {
			for (int j = 0; j < n_welch; j++)
				segment[i][j] = signal[n_welch*i / 2 + j];
		}
	}
	return;
}

void _welch_fft_average(complex_t ** segment, complex_t result[], int n_welch, int count) {

	//clear signal table
	for (int i = 0; i < n_welch; i++)
		result[i].real = 0;


	//create hamming window 
	double * window = malloc(n_welch * sizeof(double));
	_hamming(window, n_welch);

	for (int i = 0; i < count; i++) {

		//use window function on every overlapping segment
		for (int j = 0; j < n_welch; j++) {
			segment[i][j].real = segment[i][j].real * window[j];
			segment[i][j].imag = segment[i][j].imag * window[j];
		}

		//perform fast fourier transform and calulate magnitude
		fft(segment[i], n_welch);
		magnitude(segment[i], n_welch);


		//append result for further averaging (imaginary is always 0)
		for (int j = 0; j < n_welch; j++) {
			result[j].real = result[j].real + segment[i][j].real;
		}
	}

	//average calculated spectrograms magnitude (imaginary is always 0)
	for (int i = 0; i < n_welch; i++)
		result[i].real = result[i].real / n_welch;

	//cleanup
	free(window);
	return;
}

void _hamming(double window[], int n) {

	//calulate hamming window a0 - a1*cos(2PI*k/(n-1))
	for (int i = 0; i < n; i++) {
		window[i] = 0.54 - 0.46*cos(2*PI*i/(n-1));
	}
	return;
}