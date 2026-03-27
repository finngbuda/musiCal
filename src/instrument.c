#include "instrument.h"
#include <stdlib.h>

// declaring instrument
// returns an instrument struct which the user can add to the track at their choosing

struct transient_sample * init_transient_sample(unsigned int base_freq, unsigned int amp, int amp_decay_func,int amp_decay_coef, int freq_decay_func, int freq_decay_coef){
	
	struct transient_sample * ts = malloc(sizeof(struct transient_sample));

	return ts;

}

