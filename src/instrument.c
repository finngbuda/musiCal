#include "instrument.h"
#include <stdlib.h>
#include <math.h>


// internal func declarations
float calculate_len(unsigned int amp, int amp_func, float amp_coef){

	switch(amp_func){
	
		case LINEAR:
			return (1 / amp_coef);

		case QUADRATIC:
			return sqrt(1 / amp_coef);

		case EXPONENTIAL:
			return (5 / amp_coef); // exp decay is asymptotic, so just use e to the -5

		default:
			return 0;
		}

}

// does actual loop to calculate both frequencies for each sample
uint16_t * calculate_freqs(unsigned int base, int func, float coef, float len){

	uint16_t * frequencies = malloc((int)(len * 44100) * sizeof(uint16_t)); //allocate space for each sample

	switch(func){
	
		case NOFUNC:
			for(int i = 0; i < (int)(len); i++){
				frequencies[i] = (uint16_t)base; // set all to base if no freq decay
			}

		case LINEAR:
			for(int i = 0; i < (int)(len); i++){
				frequencies[i] = (uint16_t)LINEAR_DECAY(i, coef, base); // set all to base if no freq decay
			}

		case QUADRATIC:
			for(int i = 0; i < (int)(len); i++){
				frequencies[i] = (uint16_t)QUADRATIC_DECAY(i, coef, base);  // set all to base if no freq decay
			}

		case EXPONENTIAL:
			for(int i = 0; i < (int)(len); i++){
				frequencies[i] =(uint16_t)EXP_DECAY(i, coef, base);  // set all to base if no freq decay
			}

	}

	return frequencies;

}


// does actual loop to calculate both frequencies for each sample
uint16_t * calculate_vals(unsigned int base, int func, float coef, float len, uint16_t * freqs){

	uint16_t * vals = malloc((int)(len * 44100) * sizeof(uint16_t)); //allocate space for each sample

	switch(func){
	
		case NOFUNC:
			for(int i = 0; i < (int)(len); i++){
				vals[i] = (uint16_t)base * sin(freqs[i] * i); // set all to base if no freq decay
			}

		case LINEAR:
			for(int i = 0; i < (int)(len); i++){
				vals[i] = (uint16_t)LINEAR_DECAY(i, coef, base) * sin(freqs[i] * i); // set all to base if no freq decay
			}

		case QUADRATIC:
			for(int i = 0; i < (int)(len); i++){
				vals[i] = (uint16_t)QUADRATIC_DECAY(i, coef, base) * sin(freqs[i] * i);  // set all to base if no freq decay
			}

		case EXPONENTIAL:
			for(int i = 0; i < (int)(len); i++){
				vals[i] =(uint16_t)EXP_DECAY(i, coef, base) * sin(freqs[i] * i);  // set all to base if no freq decay
			}

	}

	return vals;

}



// declaring instrument
// returns an instrument struct which the user can add to the track at their choosing

struct transient_sample * init_transient_sample(unsigned int base_freq, unsigned int amp, int amp_decay_func,float amp_decay_coef, int freq_decay_func, float freq_decay_coef){
	
	struct transient_sample * ts = malloc(sizeof(struct transient_sample));

	ts->base_freq = base_freq;
	ts->amp = amp;
	ts->amp_decay_func = amp_decay_func;
	ts->amp_decay_coef = amp_decay_coef / 44100; //so the user can think in seconds
	ts->freq_decay_func = freq_decay_func;
	ts->freq_decay_coef = amp_decay_coef / 44100;

	return ts;

}

uint16_t * render_transient(struct transient_sample * ts, unsigned int * sample_len){

	*sample_len = calculate_len(ts->amp, ts->amp_decay_func, ts->amp_decay_coef);

	uint16_t * outbuf = malloc(*sample_len * 2); // 2 bytes per sample
	uint16_t * freqs = malloc(*sample_len * 2); // one pass for frequencies, one for output

	freqs = calculate_freqs(ts->base_freq, ts->freq_decay_func, ts->freq_decay_coef, *sample_len);

	return calculate_vals(ts->amp, ts->amp_decay_func, ts->amp_decay_coef, *sample_len, freqs);

}

