#include "instrument.h"
#include <stdlib.h>
#include <math.h>


// internal func declarations
unsigned int calculate_len(unsigned int amp, int amp_func, int amp_coef){

	switch(amp_func){
	
		case LINEAR:
			return (amp / amp_coef);

		case QUADRATIC:
			return sqrt(amp / amp_coef);

		case EXPONENTIAL:
			return (5 * amp / amp_coef); // exp decay is asymptotic, so just use e to the -5

		default:
			return 0;
	}

}


// declaring instrument
// returns an instrument struct which the user can add to the track at their choosing

struct transient_sample * init_transient_sample(unsigned int base_freq, unsigned int amp, int amp_decay_func,int amp_decay_coef, int freq_decay_func, int freq_decay_coef){
	
	struct transient_sample * ts = malloc(sizeof(struct transient_sample));

	ts->base_freq = base_freq;
	ts->amp = amp;
	ts->amp_decay_func = amp_decay_func;
	ts->amp_decay_coef = amp_decay_coef;
	ts->freq_decay_func = freq_decay_func;
	ts->freq_decay_coef = amp_decay_coef;

	return ts;

}

uint8_t * render_transient(struct transient_sample * ts, unsigned int * sample_len){

	*sample_len = calculate_len(ts->amp, ts->amp_decay_func, ts->amp_decay_coef) * 2;

	uint8_t * outbuf = malloc(*sample_len * 2); // 2 bytes per sample
	uint8_t * freqs = malloc(*sample_len * 2); // one pass for frequencies, one for output

	// implement calculation loops

	return outbuf;

}

