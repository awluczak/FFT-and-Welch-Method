#include <main.h>


int main() {


	complex_t signal[N_SAMPLES];
	complex_t signal_fft[N_SAMPLES];
	complex_t signal_noise_fft[N_SAMPLES];

	//set signal as sum of sine-cosine wave s
	for (int i = 0; i < N_SAMPLES; i++) {
		signal[i].real = AMPLITUDE*(sin(i*PI/128));
	}

	//write signal without noise to file
	write_csv(signal, N_SAMPLES, "C:\\Users\\Luczak\\Desktop\\FFT\\signal.csv");

	//calulate signal without noise FFT and write magnitude to file
	copy_signal(signal, signal_fft, N_SAMPLES);
	fft(signal_fft, N_SAMPLES);
    magnitude(signal_fft, N_SAMPLES);
	write_csv(signal_fft, N_SAMPLES, "C:\\Users\\Luczak\\Desktop\\FFT\\signal_fft.csv");


	//add noise to signal and write to file
	noise(signal, N_SAMPLES, AMPLITUDE*0.75);
	write_csv(signal, N_SAMPLES, "C:\\Users\\Luczak\\Desktop\\FFT\\signal_noise.csv");


	//calculate fft of signal with noise and write magnitude to file
	copy_signal(signal, signal_noise_fft, N_SAMPLES);
	fft(signal_noise_fft, N_SAMPLES);
	magnitude(signal_noise_fft, N_SAMPLES);
	write_csv(signal_noise_fft, N_SAMPLES, "C:\\Users\\Luczak\\Desktop\\FFT\\signal_noise_fft.csv");

	//estimate intial signal spectrograph using Welch's method
	welch(signal, N_SAMPLES, N_WELCH);
	write_csv(signal, N_WELCH, "C:\\Users\\Luczak\\Desktop\\FFT\\signal_welch_fft.csv");

	printf("Execution done.\n");
	return 0;
}


void write_csv(complex_t signal[], int n_samples, char *filename) {

	FILE * fhandle;
	fopen_s(&fhandle, filename,"w");

	fprintf(fhandle, "sample; value");

	for (int i = 0; i < n_samples; i++) {
		fprintf(fhandle, "\n%i; %i", i, (int)(signal[i].real*1000));
	}

	fclose(fhandle);
	return;
}

void copy_signal(complex_t source[], complex_t target[], int n) {

	for (int i = 0; i < n; i++)
		target[i] = source[i];

	return;
}
